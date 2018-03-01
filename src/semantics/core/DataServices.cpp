#include <semantics/core/DataServices.hpp>

#include <persistence/SQLite/DAOFactory.hpp>
#include <functional>

namespace semantics {
namespace core {

DataServices::DataServices()
{
    resetSharedData();
    _forms = std::make_unique<Forms>(_formsSharedData);
}

DataServices::~DataServices()
{
}

void DataServices::loadData(const QString &uri)
{
    resetDAO(uri);
    resetSharedData();
    std::unique_ptr<Forms> forms = std::make_unique<Forms>(_formsSharedData);

    QVector<persistence::Form> p_forms = _dao_form->search();
    Forms &s_forms = *forms;
    for (const persistence::Form &p_f : p_forms) {

        QVector<persistence::Question> p_questions = _dao_question->search({{"form", p_f.id}});
        Form::Questions s_questions(_questionsSharedData);
        for (const persistence::Question &p_q : p_questions) {
            std::unique_ptr<Question> s_q;
            if (p_q.type == "opened") {
                s_q = std::make_unique<OpenedQuestion>(p_q.id, p_q.title, p_q.nb_words, p_q.modification_date);
            } else if (p_q.type == "unique" || p_q.type == "multiple") {
                ClosedQuestion::Type type;
                if (p_q.type == "unique") {
                    type = ClosedQuestion::Unique;
                } else if (p_q.type == "multiple") {
                    type = ClosedQuestion::Multiple;
                }

                QVector<persistence::Choice> p_choices = _dao_choice->search({{"question", p_q.id}});
                ClosedQuestion::Choices s_choices(_choicesSharedData);
                for (const persistence::Choice &p_c : p_choices) {
                    s_choices.insert(std::make_unique<Choice>(p_c.id, p_c.label, p_c.modification_date));
                }

                s_q = std::make_unique<ClosedQuestion>(p_q.id, type, s_choices, p_q.title, p_q.modification_date);
            } else {
                // exception
            }
            s_questions.insert(std::move(s_q));
        }

        QVector<persistence::Subject> p_subjects = _dao_subject->search({{"form", p_f.id}});
        Form::Subjects s_subjects(_subjectsSharedData);
        for (const persistence::Subject &p_s : p_subjects) {
            Subject::Answers s_answers;

            QVector<persistence::OpenedAnswer> p_openedAnswers = _dao_openedAnswer->search({{"subject", p_s.id}});
            for (const persistence::OpenedAnswer &p_oa : p_openedAnswers) {
                auto q = p_oa.question;
                s_answers.insert(q, new OpenedAnswer(p_oa.question, p_oa.words.split('|'), p_oa.modification_date)); // use JSON array
            }

            QVector<persistence::ClosedAnswer> p_closedAnswers = _dao_closedAnswer->search({{"subject", p_s.id}});
            QHash<int, std::reference_wrapper<const persistence::ClosedAnswer>> m_choices;
            for (const persistence::ClosedAnswer &p_ca : p_closedAnswers) {
                m_choices.insert(p_ca.choice, p_ca);
            }

            for (const auto it_q : s_questions) {
                ClosedQuestion * q = dynamic_cast<ClosedQuestion*>(it_q->second);
                if (q) {
                    ClosedAnswer::Choices choices;
                    for (const auto it_c : q->choices()) {
                        const Choice & c = *it_c->second;
                        if (m_choices.count(c.id()) > 0) {
                            choices.append(c.id());
                        }
                    }
                    auto id = q->id();
                    s_answers.insert(id, new ClosedAnswer(q->id(), choices)); // modification date ??
                }
            }
            s_subjects.insert(std::make_unique<Subject>(p_s.id, p_s.is_valid, s_answers, p_s.modification_date));
        }
        s_forms.insert(std::make_unique<Form>(p_f.id, s_questions, s_subjects, p_f.name, p_f.description, p_f.creation_date, p_f.modification_date));
    }

    _forms = std::move(forms);
}

void DataServices::saveData(const QString &uri)
{
    resetDAO(uri);
    _dao_form->remove();

    for (const auto it_f : *_forms) {
        const Form &s_f = *it_f->second;
        persistence::Form p_f;
        p_f.id = s_f.id();
        p_f.name = s_f.name();
        p_f.description = s_f.description();
        p_f.modification_date = s_f.modification_date();
        p_f.creation_date = s_f.creationDate();
        _dao_form->save(p_f);

        for (const auto it_q : s_f.questions()) {
            const Question &s_q = *it_q->second;
            persistence::Question p_q;
            p_q.id = s_q.id();
            p_q.title = s_q.title();
            p_q.form = p_f.id;
            p_q.modification_date = s_q.modification_date();

            const OpenedQuestion * oq = dynamic_cast<const OpenedQuestion*>(it_q->second);
            if (oq) {
                p_q.type = "opened";
                p_q.nb_words = oq->nbWords();
            }

            const ClosedQuestion * cq = dynamic_cast<const ClosedQuestion*>(it_q->second);
            if (cq) {
                switch (cq->type()) {
                case ClosedQuestion::Unique:
                    p_q.type = "unique";
                    break;
                case ClosedQuestion::Multiple:
                    p_q.type = "multiple";
                    break;
                }
            }
            _dao_question->save(p_q);

            if (cq) {
                for (const auto it_c : cq->choices()) {
                    const Choice &s_c = *it_c->second;
                    persistence::Choice p_c;
                    p_c.id = s_c.id();
                    p_c.label = s_c.label();
                    p_c.modification_date = s_c.modification_date();
                    p_c.question = p_q.id;
                    _dao_choice->save(p_c);
                }
            }
        }

        for (const auto it_q : s_f.subjects()) {
            const Subject &s_s = *it_q->second;
            persistence::Subject p_s;
            p_s.id = s_s.id();
            p_s.is_valid = s_s.isValid();
            p_s.modification_date = s_s.modification_date();
            p_s.form = p_f.id;
            _dao_subject->save(p_s);


            for (const auto it_a : s_s.answers()) {
                const OpenedAnswer * oa = dynamic_cast<const OpenedAnswer*>(it_a->second);
                if (oa) {
                    persistence::OpenedAnswer p_oa;
                    p_oa.question = oa->question();
                    p_oa.modification_date = oa->modification_date();
                    p_oa.subject = p_s.id;
                    p_oa.words = oa->words().join('|'); // JSON array
                    _dao_openedAnswer->save(p_oa);
                }

                const ClosedAnswer * ca = dynamic_cast<const ClosedAnswer*>(it_a->second);
                if (ca) {
                    persistence::ClosedAnswer p_ca;
                    p_ca.subject = p_s.id;
                    p_ca.modification_date = ca->modification_date();
                    for (auto c : ca->choices()) {
                        p_ca.choice = c;
                        _dao_closedAnswer->save(p_ca);
                    }
                }
            }
        }
    }
}

QVariantMap DataServices::listForms()
{
    QVariantMap r;
    for (auto it : *_forms) {
        const Form &f = *it->second;
        r[QString::number(f.id())] = f.toTinyMap();
    }
    return r;
}

QVariantMap DataServices::listSubjects(const Id id)
{
    QVariantMap r;
    for (auto it : _forms->at(id).subjects()) {
        const Subject &s = *it->second;
        r[QString::number(s.id())] = s.toTinyMap();
    }
    return r;
}

QVariantMap DataServices::getForm(const Id id)
{
    return _forms->at(id).toMap();
}

QVariantMap DataServices::getSubject(const Id id)
{
    for (auto it : *_forms) {
        Form * form = it->second;
        const  Form::Subjects & subjects = form->subjects();
        auto it_sub = subjects.find(id);
        if (it_sub != subjects.end()) {
            return it_sub->second->toMap();
        }
    }
    return QVariantMap();
}

QVariantMap DataServices::getNewSubject(const Id form)
{
    Subject::Answers answers;
    const Form &f = _forms->at(form);

    for (auto it_q : f.questions()) {
        const Question * q = it_q->second;
        auto id = q->id();
        const OpenedQuestion * oq = dynamic_cast<const OpenedQuestion*>(q);
        if (oq) {
            std::unique_ptr<OpenedAnswer> oa = std::make_unique<OpenedAnswer>(id);
            answers.insert(id, oa.release());
        }

        const ClosedQuestion * cq = dynamic_cast<const ClosedQuestion*>(q);
        if (cq) {
            std::unique_ptr<ClosedAnswer> ca = std::make_unique<ClosedAnswer>(id);
            answers.insert(id, ca.release());
        }
    }

    std::unique_ptr<Subject> s = std::make_unique<Subject>(takeSubjectId());
    s->setAnswers(answers);

    return s->toMap();
}

void DataServices::saveForm(const QVariantMap &form)
{
    std::unique_ptr<Form> f(Form::fromMap(form));
    auto it = _forms->find(f->id());
    if (it == _forms->end()) {
        _forms->insert(std::move(f));
    } else {
        it->second->assignFromMap(form);
    }
}

void DataServices::saveSubject(const Id form, const QVariantMap &subject)
{
    Form & f = _forms->at(form);
    Form::Subjects subjects = f.subjects();
    std::unique_ptr<Subject> s(Subject::fromMap(subject));
    auto it = subjects.find(s->id());
    if (it == subjects.end()) {
        subjects.insert(std::move(s));
    } else {
        it->second->assignFromMap(subject);
    }
    f.setSubjects(subjects);
}

void DataServices::deleteForm(const Id id)
{
    _forms->erase(id);
}

void DataServices::deleteSubject(const Id id)
{
    for (auto it : *_forms) {
        Form * form = it->second;
        const  Form::Subjects & subjects = form->subjects();
        auto it_sub = subjects.find(id);
        if (it_sub != subjects.end()) {
            auto subjects_copy = subjects;
            subjects_copy.erase(id);
            form->setSubjects(subjects_copy);
        }
    }
}

DataServices::Id DataServices::takeFormId()
{
    return _formsSharedData->takeId();
}

DataServices::Id DataServices::takeSubjectId()
{
    return _subjectsSharedData->takeId();
}

DataServices::Id DataServices::takeQuestionId()
{
    return _questionsSharedData->takeId();
}

DataServices::Id DataServices::takeChoiceId()
{
    return _choicesSharedData->takeId();
}

void DataServices::resetSharedData()
{
    _formsSharedData = std::make_shared<Forms::SharedData>();
    _questionsSharedData = std::make_shared<Form::Questions::SharedData>();
    _choicesSharedData = std::make_shared<ClosedQuestion::Choices::SharedData>();
    _subjectsSharedData = std::make_shared<Form::Subjects::SharedData>();
}

void DataServices::resetDAO(const QString &uri)
{
    _factory = std::make_unique<persistence::SQLite::DAOFactory>(uri);
    _dao_form.reset(_factory->form());
    _dao_question.reset(_factory->question());
    _dao_choice.reset(_factory->choice());
    _dao_subject.reset(_factory->subject());
    _dao_openedAnswer.reset(_factory->openedAnswer());
    _dao_closedAnswer.reset(_factory->closedAnswer());
}

}
}

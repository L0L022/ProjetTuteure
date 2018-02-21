#include <semantics/core/DataServices.hpp>

#include <persistence/SQLite/DAOFactory.hpp>

using namespace semantics::core;

DataServices::DataServices()
    :  _formsSharedData(std::make_unique<Forms::SharedData>())
    , _questionsSharedData(std::make_unique<Form::Questions::SharedData>())
    , _choicesSharedData(std::make_unique<ClosedQuestion::Choices::SharedData>())
    , _subjectsSharedData(std::make_unique<Form::Subjects::SharedData>())
    , _forms(_formsSharedData)
{
    std::unique_ptr<persistence::DAOFactory> factory = std::make_unique<persistence::SQLite::DAOFactory>(":memory:");
    _dao_form.reset(factory->form());
    _dao_question.reset(factory->question());
    _dao_choice.reset(factory->choice());
    _dao_subject.reset(factory->subject());
    _dao_openedAnswer.reset(factory->openedAnswer());
    _dao_closedAnswer.reset(factory->closedAnswer());

    load();
}

DataServices::~DataServices()
{
    save();
}

void DataServices::load()
{/*
    QVector<persistence::Form> p_forms = _dao_form->search();
    Forms s_forms(_formsSharedData);
    for (const persistence::Form &p_f : p_forms) {
        std::unique_ptr<Form> s_f = std::make_unique<Form>(p_f.id, _questionsSharedData, _subjectsSharedData, p_f.modification_date);
        s_f->setName(p_f.name);
        s_f->setDescription(p_f.description);
        s_f->setCreationDate(p_f.creation_date);

        QVector<persistence::Question> p_questions = _dao_question->search({{"form", p_f.id}});
        Form::Questions s_questions(_questionsSharedData);
        for (const persistence::Question &p_q : p_questions) {
            std::unique_ptr<Question> s_q;
            if (p_q.type == "opened") {
                std::unique_ptr<OpenedQuestion> q = std::make_unique<OpenedQuestion>(p_q.id, p_q.modification_date);
                q->setNbWords(p_q.nb_words);
                s_q = std::move(q);
            } else if (p_q.type == "unique" || p_q.type == "multiple") {
                ClosedQuestion::Type type;
                if (p_q.type == "unique") {
                    type = ClosedQuestion::Unique;
                } else if (p_q.type == "multiple") {
                    type = ClosedQuestion::Multiple;
                }
                std::unique_ptr<ClosedQuestion> q = std::make_unique<ClosedQuestion>(type, p_q.id, _choicesSharedData, p_q.modification_date);

                QVector<persistence::Choice> p_choices = _dao_choice->search({{"question", p_q.id}});
                ClosedQuestion::Choices s_choices(_choicesSharedData);
                for (const persistence::Choice &p_c : p_choices) {
                    std::unique_ptr<Choice> s_c = std::make_unique<Choice>(p_c.id, p_c.modification_date);
                    s_c->setLabel(p_c.label);
                    s_choices.insert(std::move(s_c));
                }
                q->setChoices(s_choices);

                s_q = std::move(q);
            }
            s_q->setTitle(p_q.title);
            s_questions.insert(std::move(s_q));
        }
        s_f->setQuestions(s_questions);

        QVector<persistence::Subject> p_subjects = _dao_subject->search({{"form", p_f.id}});
        Form::Subjects s_subjects(_subjectsSharedData);
        for (const persistence::Subject &p_s : p_subjects) {
            std::unique_ptr<Subject> s_subject = std::make_unique<Subject>(p_s.id, p_s.modification_date);

            Subject::Answers s_answers;

            QVector<persistence::OpenedAnswer> p_openedAnswers = _dao_openedAnswer->search({{"subject", p_s.id}});
            for (const persistence::OpenedAnswer &p_oa : p_openedAnswers) {
                std::unique_ptr<OpenedAnswer> s_oa = std::make_unique<OpenedAnswer>(p_oa.question, p_oa.modification_date);
                s_oa->setWords(p_oa.words); // convert words
                auto q = s_oa->question();
                s_answers.insert(q, s_oa.release());
            }

            QVector<persistence::ClosedAnswer> p_closedAnswers = _dao_closedAnswer->search({{"subject", p_s.id}});
            QHash<int, persistence::ClosedAnswer&> m_choices;
            for (const persistence::ClosedAnswer &p_ca : p_closedAnswers) {
                m_choices[p_ca.choice] = p_ca;
            }

            for (const auto it_q : s_questions) {
                ClosedQuestion * q = dynamic_cast<ClosedQuestion*>(it_q->second);
                if (q) {
                    ClosedAnswer::Choices choices;
                    for (const auto it_c : q->choices()) {
                        const Choice & c = *it_c->second;
                        if (m_choices.count(c.id())) {
                            choices.append(c.id());
                        }
                    }
                    std::unique_ptr<ClosedAnswer> s_ca = std::make_unique<ClosedAnswer>(q->id());
                    s_ca->setChoices(choices);
                    Question::Id id = q->id();
                    s_answers.insert(id, s_ca.release());
                }
            }

            s_subject->setAnswers(s_answers);
        }

        s_forms.insert(std::move(s_f));
    }*/
}

void DataServices::save()
{/*
    for (const auto it_f : _forms) {
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
            _dao_question->save(p_q);
        }

        for (const auto it_q : s_f.subjects()) {
//            const Subject &s_s =
        }
    }*/
}

QVariantMap DataServices::listForms()
{

}

QVariantMap DataServices::listSubjects(const Id id)
{

}

QVariantMap DataServices::getForm(const Id id)
{
    return _forms.at(id).toMap();
}

QVariantMap DataServices::getSubject(const Id id)
{
    for (auto it : _forms) {
        Form * form = it->second;
        const  Form::Subjects & subjects = form->subjects();
        auto it_sub = subjects.find(id);
        if (it_sub != subjects.end()) {
            return it_sub->second->toMap();
        }
    }
    return QVariantMap();
}

void DataServices::saveForm(const QVariantMap &form)
{
    std::unique_ptr<Form> f(Form::fromMap(form));
    if (_forms.count(f->id()) == 0) {
        _forms.insert(std::move(f));
    } else {
        _forms.at(f->id()).assignFromMap(form);
    }
}

void DataServices::saveSubject(const Id form, const QVariantMap &subject)
{
    Form & f = _forms.at(form);
    Form::Subjects subjects = f.subjects();
    std::unique_ptr<Subject> s(Subject::fromMap(subject));
    if (subjects.count(s->id()) == 0) {
        subjects.insert(std::move(s));
    } else {
        subjects.at(s->id()).assignFromMap(subject);
    }
}

void DataServices::deleteForm(const Id id)
{
    _forms.erase(id);
}

void DataServices::deleteSubject(const Id id)
{
    for (auto it : _forms) {
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

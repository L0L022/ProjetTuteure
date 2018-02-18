#include <semantics/core/Data.hpp>

Data::Data(const QVariantMap &m) : Data(m.value("modification_date", QDateTime::currentDateTime()).toDateTime()) {}

void Data::update_modification() {
  _modification_date = QDateTime::currentDateTime();
}

QVariantMap Data::do_toMap() const {
    QVariantMap m;
    m["modification_date"] = _modification_date;
    return m;
}

QVariantMap IdData::do_toMap() const {
    auto m = Data::do_toMap();
    m["id"] = _id;
    return m;
}

void Question::setTitle(const QString &title)
{
    if (title != _title) {
        _title = title;
        update_modification();
    }
}

QVariantMap Question::do_toMap() const {
    auto m = IdData::do_toMap();
    m["title"] = _title;
    return m;
}

void OpenedQuestion::setNbWords(const size_t nbWords) {
    if (nbWords != _nbWords) {
        _nbWords = nbWords;
        update_modification();
    }
}

QVariantMap OpenedQuestion::do_toMap() const {
    auto m = Question::do_toMap();
    m["nb_words"] = QVariant::fromValue(_nbWords);
    return m;
}

void Choice::setLabel(const QString &label) {
    if (label != _label) {
        _label = label;
        update_modification();
    }
}

QVariantMap Choice::do_toMap() const {
    auto m = IdData::do_toMap();
    m["label"] = _label;
    return m;
}

void ClosedQuestion::setType(const Type type) {
    if (type != _type) {
        _type = type;
        update_modification();
    }
}

void ClosedQuestion::setChoices(const Choices &choices) {
    if (choices != _choices) {
        _choices = choices;
        update_modification();
    }
}

QVariantMap ClosedQuestion::do_toMap() const {
    auto m = Question::do_toMap();
    m["type"] = _type;
    m["choices"] = toVariantMap(_choices);
    return m;
}

QVariantMap Answer::do_toMap() const {
    auto m = Data::do_toMap();
    m["question"] = _question;
    return m;
}

void OpenedAnswer::setWords(const QStringList &words) {
    if (words != _words) {
        _words = words;
        update_modification();
    }
}

QVariantMap OpenedAnswer::do_toMap() const {
    auto m = Answer::do_toMap();
    m["words"] = _words;
    return m;
}

void ClosedAnswer::setChoices(const Choices &choices) {
    if (choices != _choices) {
        _choices = choices;
        update_modification();
    }
}

QVariantMap ClosedAnswer::do_toMap() const {
    auto m = Answer::do_toMap();
    m["choices"] = QVariant::fromValue(_choices);
    return m;
}

void Subject::setIsValid(const bool isValid) {
    if (isValid != _isValid) {
        _isValid = isValid;
        update_modification();
    }
}

void Subject::setAnswers(const Answers &answers) {
    if (answers != _answers) {
        _answers = answers;
        update_modification();
    }
}

QVariantMap Subject::do_toMap() const {
    auto m = IdData::do_toMap();
    m["is_valid"] = _isValid;
    m["answers"] = toVariantMap(_answers);
    return m;
}

void Form::setName(const QString &name) {
    if (name != _name) {
        _name = name;
        update_modification();
    }
}

void Form::setDescription(const QString &description) {
    if (description != _description) {
        _description = description;
        update_modification();
    }
}

void Form::setCreationDate(const QDateTime &creation_date) {
    if (creation_date != _creation_date) {
        _creation_date = creation_date;
        update_modification();
    }
}

void Form::setQuestions(const Questions &questions) {
    if (questions != _questions) {
        _questions = questions;
        update_modification();
    }
}

void Form::setSubjects(const Subjects &subjects) {
    if (subjects != _subjects) {
        _subjects = subjects;
        update_modification();
    }
}

QVariantMap Form::do_toMap() const {
    auto m = IdData::do_toMap();
    m["name"] = _name;
    m["description"] = _description;
    m["creation_date"] = _creation_date;
    m["questions"] = toVariantMap(_questions);
    m["subjects"] = toVariantMap(_subjects);
    return m;
}

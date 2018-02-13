#include <semantics/core/Data.hpp>

Data::Data(const Id id, const QDateTime &modification_date)
    : _id(id), _modification_date(modification_date) {}

Data::Data(const QVariantMap &m) : Data(m.value("id", -1).toInt(), m.value("modification_date", QDateTime::currentDateTime()).toDateTime()) {}

void Data::update_modification() {
  _modification_date = QDateTime::currentDateTime();
}

void Question::setTitle(const QString &title)
{
    if (title != _title) {
        _title = title;
        update_modification();
    }
}

void OpenedQuestion::setNbWords(const size_t nbWords) {
    if (nbWords != _nbWords) {
        _nbWords = nbWords;
        update_modification();
    }
}

void Choice::setLabel(const QString &label) {
    if (label != _label) {
        _label = label;
        update_modification();
    }
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

void OpenedAnswer::setWords(const QStringList &words) {
    if (words != _words) {
        _words = words;
        update_modification();
    }
}

void ClosedAnswer::setChoices(const Choices &choices) {
    if (choices != _choices) {
        _choices = choices;
        update_modification();
    }
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

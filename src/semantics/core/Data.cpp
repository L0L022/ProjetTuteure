#include <semantics/core/Data.hpp>

Data::Data(const QDateTime &modification_date)
    : _modification_date(modification_date) {}

Data::~Data() {}

QVariantMap Data::toMap() const { return do_toMap(); }

void Data::assignFromMap(const QVariantMap &m) { do_assignFromMap(m); }

Data *Data::clone() const { return do_clone(); }

bool Data::operator==(const Data &d) const { return toMap() == d.toMap(); }

bool Data::operator!=(const Data &d) const { return toMap() != d.toMap(); }

Data::Data(const QVariantMap &m) { do_assignFromMap(m); }

Data::Data(const Data &d) : _modification_date(d._modification_date) {}

void Data::update_modification() {
  _modification_date = QDateTime::currentDateTime();
}

QVariantMap Data::do_toMap() const {
  QVariantMap m;
  m["modification_date"] = _modification_date;
  return m;
}

void Data::do_assignFromMap(const QVariantMap &m) {
  _modification_date = m.value("modification_date").toDateTime();
}

Data *new_clone(const Data &d) { return d.clone(); }

IdData::IdData(const Id id, const QDateTime &modification_date)
    : Data(modification_date), _id(id) {}

IdData::IdData(const QVariantMap &m)
    : Data(m), _id(m.value("id").value<Id>()) {}

QVariantMap IdData::do_toMap() const {
  auto m = Data::do_toMap();
  m["id"] = _id;
  return m;
}

void IdData::do_assignFromMap(const QVariantMap &m) {
  Data::do_assignFromMap(m);
  // check id corresponds
}

Question::Question(const IdData::Id id, const QDateTime &modification_date)
    : IdData(id, modification_date) {}

Question::Question(const QVariantMap &m) : IdData(m) {}

void Question::setTitle(const QString &title) {
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

void Question::do_assignFromMap(const QVariantMap &m) {
  IdData::do_assignFromMap(m);
  _title = m.value("title").toString();
}

OpenedQuestion::OpenedQuestion(const IdData::Id id,
                               const QDateTime &modification_date)
    : Question(id, modification_date), _nbWords(0) {}

void OpenedQuestion::setNbWords(const Size nbWords) {
  if (nbWords != _nbWords) {
    _nbWords = nbWords;
    update_modification();
  }
}

OpenedQuestion::OpenedQuestion(const QVariantMap &m) : Question(m) {}

QVariantMap OpenedQuestion::do_toMap() const {
  auto m = Question::do_toMap();
  m["nb_words"] = _nbWords;
  return m;
}

void OpenedQuestion::do_assignFromMap(const QVariantMap &m) {
  Question::do_assignFromMap(m);
  _nbWords = m.value("nb_words").value<Size>();
}

Choice::Choice(const IdData::Id id, const QDateTime &modification_date)
    : IdData(id, modification_date) {}

Choice::Choice(const QVariantMap &m) : IdData(m) {}

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

void Choice::do_assignFromMap(const QVariantMap &m) {
  IdData::do_assignFromMap(m);
  _label = m.value("label").toString();
}

ClosedQuestion::ClosedQuestion(const ClosedQuestion::Type type,
                               const IdData::Id id,
                               Choices::SharedDataPtr sharedData,
                               const QDateTime &modification_date)
    : Question(id, modification_date), _type(type), _choices(sharedData) {}

ClosedQuestion::ClosedQuestion(const QVariantMap &m) : Question(m) {}

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

void ClosedQuestion::do_assignFromMap(const QVariantMap &m) {
  Question::do_assignFromMap(m);
  _type = m.value("type").value<Type>();
  fromVariantMap(m.value("choices").toMap(), _choices);
}

Answer::Answer(const Answer::Id question, const QDateTime &modification_date)
    : Data(modification_date), _question(question) {}

Answer::Answer(const QVariantMap &m)
    : Data(m), _question(m.value("question").value<Id>()) {}

QVariantMap Answer::do_toMap() const {
  auto m = Data::do_toMap();
  m["question"] = _question;
  return m;
}

void Answer::do_assignFromMap(const QVariantMap &m) {
  Data::do_assignFromMap(m);
  // check question
}

OpenedAnswer::OpenedAnswer(const Answer::Id id,
                           const QDateTime &modification_date)
    : Answer(id, modification_date) {}

OpenedAnswer::OpenedAnswer(const QVariantMap &m) : Answer(m) {}

void OpenedAnswer::setWords(const QStringList &words) {
  if (words != _words) {
    _words = words;
    update_modification();
  }
}

bool OpenedAnswer::isValid(const Answer::Questions &questions) const {
  auto q = dynamic_cast<const OpenedQuestion &>(questions.at(question()));
  return _words.size() <= q.nbWords();
}

QVariantMap OpenedAnswer::do_toMap() const {
  auto m = Answer::do_toMap();
  m["words"] = _words;
  return m;
}

void OpenedAnswer::do_assignFromMap(const QVariantMap &m) {
  Answer::do_assignFromMap(m);
  _words = m.value("words").toStringList();
}

ClosedAnswer::ClosedAnswer(const Answer::Id id,
                           const QDateTime &modification_date)
    : Answer(id, modification_date) {}

ClosedAnswer::ClosedAnswer(const QVariantMap &m) : Answer(m) {}

void ClosedAnswer::setChoices(const Choices &choices) {
  if (choices != _choices) {
    _choices = choices;
    update_modification();
  }
}

bool ClosedAnswer::isValid(const Answer::Questions &questions) const {
  auto q = dynamic_cast<const ClosedQuestion &>(questions.at(question()));

  switch (q.type()) {
  case ClosedQuestion::Unique:
    if (_choices.size() >= 2)
      return false;
    break;
  case ClosedQuestion::Multiple:
    break;
  default:
    return false;
    break;
  }

  for (const Id &id : _choices)
    if (q.choices().count(id) == 0)
      return false;

  return true;
}

QVariantMap ClosedAnswer::do_toMap() const {
  auto m = Answer::do_toMap();
  m["choices"] = QVariant::fromValue(_choices);
  return m;
}

void ClosedAnswer::do_assignFromMap(const QVariantMap &m) {
  Answer::do_assignFromMap(m);
  _choices = m.value("choices").value<Choices>();
}

Subject::Subject(const IdData::Id id, const QDateTime &modification_date)
    : IdData(id, modification_date) {}

Subject::Subject(const QVariantMap &m) : IdData(m) {}

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

void Subject::do_assignFromMap(const QVariantMap &m) {
  IdData::do_assignFromMap(m);
  _isValid = m.value("is_valid").toBool();
  fromVariantMap(m.value("answers").toMap(), _answers);
}

Form::Form(const IdData::Id id, Questions::SharedDataPtr questionsSharedData,
           Subjects::SharedDataPtr subjectsSharedData,
           const QDateTime &modification_date)
    : IdData(id, modification_date), _questions(questionsSharedData),
      _subjects(subjectsSharedData) {}

Form::Form(const QVariantMap &m) : IdData(m) {}

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

void Form::do_assignFromMap(const QVariantMap &m) {
  IdData::do_assignFromMap(m);
  _name = m.value("name").toString();
  _description = m.value("description").toString();
  _creation_date = m.value("creation_date").toDateTime();
  fromVariantMap(m.value("questions").toMap(), _questions);
  fromVariantMap(m.value("subjects").toMap(), _subjects);
}

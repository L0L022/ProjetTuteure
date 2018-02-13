#ifndef SEMANTICS_CORE_DATA_HPP
#define SEMANTICS_CORE_DATA_HPP

#include <memory>

#include <QDateTime>
#include <QVariant>
#include <QVector>

#include <boost/ptr_container/ptr_map.hpp>

class Data : boost::noncopyable {
public:
  using Id = int;

  Data(const Id id,
       const QDateTime &modification_date = QDateTime::currentDateTime());
  Data(const QVariantMap &m);
  virtual ~Data() {}

  inline Id id() const { return _id; }

  inline const QDateTime &modification_date() const {
    return _modification_date;
  }

  QVariantMap toMap() const { return do_toMap(); }
  Data *clone() const { return do_clone(); }

protected:
  Data(const Data &d) : _id(d._id), _modification_date(d._modification_date) {}
  // Data &operator=(const Data &d) = default;

  void update_modification();

private:
  virtual QVariantMap do_toMap() const;
  virtual Data *do_clone() const = 0;

private:
  const Id _id;
  QDateTime _modification_date;
};

inline Data *new_clone(const Data &d) { return d.clone(); }

class Question : public Data {
protected:
  Question(const Id id,
           const QDateTime &modification_date = QDateTime::currentDateTime());
  Question(const QVariantMap &m);

public:
  inline QString &title() { return _title; }
  void setTitle(const QString &title);

private:
  virtual Data *do_clone() const { return new Question(*this); }

private:
  QString _title;
};

class OpenedQuestion : public Question {
public:
  OpenedQuestion(const Id id, const QDateTime &modification_date =
                                  QDateTime::currentDateTime());
  OpenedQuestion(const QVariantMap &m);

  inline size_t nbWords() const { return _nbWords; }
  void setNbWords(const size_t nbWords);

private:
  virtual Data *do_clone() const { return new OpenedQuestion(*this); }

private:
  size_t _nbWords;
};

class Choice : public Data {
public:
  Choice(const Id id,
         const QDateTime &modification_date = QDateTime::currentDateTime());
  Choice(const QVariantMap &m);

  inline const QString &label() const { return _label; }
  void setLabel(const QString &label);

private:
  virtual Data *do_clone() const { return new Choice(*this); }

private:
  QString _label;
};

class ClosedQuestion : public Question {
public:
  using Choices = boost::ptr_map<Id, Choice>;

  enum Type { Unique, Multiple };

  ClosedQuestion(const Id id, const QDateTime &modification_date =
                                  QDateTime::currentDateTime());
  ClosedQuestion(const QVariantMap &m);

  inline Type type() const { return _type; }
  void setType(const Type type);

  inline const Choices &choices() const { return _choices; }
  void setChoices(const Choices &choices);

private:
  virtual Data *do_clone() const { return new ClosedQuestion(*this); }

private:
  Type _type;
  Choices _choices;
};

class Answer : public Data {
protected:
  Answer(const Id id,
         const QDateTime &modification_date = QDateTime::currentDateTime());
  Answer(const QVariantMap &m);

public:
  Id question() const { return _question; }

private:
  virtual Data *do_clone() const { return new Answer(*this); }

private:
  const Id _question;
};

class OpenedAnswer : public Answer {
public:
  OpenedAnswer(const Id id, const QDateTime &modification_date =
                                QDateTime::currentDateTime());
  OpenedAnswer(const QVariantMap &m);

  inline const QStringList &words() const { return _words; }
  void setWords(const QStringList &words);

private:
  virtual Data *do_clone() const { return new OpenedAnswer(*this); }

private:
  QStringList _words;
};

class ClosedAnswer : public Answer {
public:
  using Choices = QVector<Id>;

  ClosedAnswer(const Id id, const QDateTime &modification_date =
                                QDateTime::currentDateTime());
  ClosedAnswer(const QVariantMap &m);

  inline const Choices &choices() const { return _choices; }
  void setChoices(const Choices &choices);

private:
  virtual Data *do_clone() const { return new ClosedAnswer(*this); }

private:
  Choices _choices;
};

class Subject : public Data {
public:
  using Answers = boost::ptr_map<Id, Answer>;

  Subject(const Id id,
          const QDateTime &modification_date = QDateTime::currentDateTime());
  Subject(const QVariantMap &m);

  bool isValid() const { return _isValid; }
  void setIsValid(const bool isValid);

  inline const Answers &answers() const { return _answers; }
  void setAnswers(const Answers &answers);

private:
  virtual Data *do_clone() const { return new Subject(*this); }

private:
  bool _isValid;
  Answers _answers;
};

class Form : public Data {
public:
  using Questions = boost::ptr_map<Id, Question>;
  using Subjects = boost::ptr_map<Id, Subject>;

  Form(const Id id,
       const QDateTime &modification_date = QDateTime::currentDateTime());
  Form(const QVariantMap &m);

  inline const QString &name() const { return _name; }
  void setName(const QString &name);

  inline const QString &description() const { return _description; }
  void setDescription(const QString &description);

  inline const QDateTime &creationDate() const { return _creation_date; }
  void setCreationDate(const QDateTime &creation_date);

  inline const Questions &questions() const { return _questions; }
  void setQuestions(const Questions &questions);

  inline const Subjects &subjects() const { return _subjects; }
  void setSubjects(const Subjects &subjects);

private:
  virtual Data *do_clone() const { return new Form(*this); }

private:
  QString _name;
  QString _description;
  QDateTime _creation_date;
  Questions _questions;
  Subjects _subjects;
};

#endif

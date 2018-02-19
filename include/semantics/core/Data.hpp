#ifndef SEMANTICS_CORE_DATA_HPP
#define SEMANTICS_CORE_DATA_HPP

#include <memory>

#include <QDateTime>
#include <QList>
#include <QVariant>

#include <boost/ptr_container/ptr_map.hpp>

namespace semantics {
namespace core {

class Data : boost::noncopyable {
public:
  Data(const QDateTime &modification_date = QDateTime::currentDateTime());
  virtual ~Data();

  inline const QDateTime &modification_date() const {
    return _modification_date;
  }

  QVariantMap toMap() const;
  void assignFromMap(const QVariantMap &m);

  Data *clone() const;

  bool operator==(const Data &d) const;
  bool operator!=(const Data &d) const;

protected:
  Data(const QVariantMap &m);
  Data(const Data &d);
  // Data &operator=(const Data &d) = default;

  void update_modification();

protected:
  virtual QVariantMap do_toMap() const;
  virtual void do_assignFromMap(const QVariantMap &m);

private:
  virtual Data *do_clone() const = 0;

private:
  QDateTime _modification_date;
};

inline Data *new_clone(const Data &d)  { return d.clone(); }

class IdData : public Data {
public:
  using Id = int;

  IdData(const Id id,
         const QDateTime &modification_date = QDateTime::currentDateTime());

  inline Id id() const { return _id; }

protected:
  IdData(const QVariantMap &m);
  virtual QVariantMap do_toMap() const;
  virtual void do_assignFromMap(const QVariantMap &m);

private:
  virtual Data *do_clone() const;

private:
  const Id _id;
};

inline IdData *new_clone(const IdData &d)  { return dynamic_cast<IdData*>(d.clone()); }

class IdDataMapSharedData {
public:
  using Id = IdData::Id;

  IdDataMapSharedData() : _max_id(1) {}
  inline Id takeId() { return _max_id++; }
  inline void trySetMaxId(const Id &maxId) {
    if (maxId > _max_id) {
      _max_id = maxId;
    }
  }

private:
  Id _max_id;
};

template <typename T> class IdDataMap {
public:
  using SharedData = IdDataMapSharedData;
  using SharedDataPtr = std::shared_ptr<SharedData>;
  using Id = SharedData::Id;

private:
  using Map = boost::ptr_map<Id, T>;

public:
  using iterator = typename Map::iterator;
  using const_iterator = typename Map::const_iterator;

  IdDataMap(const SharedDataPtr &sharedData = std::make_shared<SharedData>())
      : _sharedData(sharedData) {
      if (_sharedData == nullptr)
          ; // exception
  }

  void insert(std::unique_ptr<T> d) {
    // check d -> exception
      Id id = d->id();
    auto r = _map.insert(id, std::auto_ptr<T>(d.release()));
    if (r.second)
      _sharedData->trySetMaxId(id + 1);
    else
      ; // exception
  }
  void erase(const Id &id) { _map.erase(id); }
  void erase(iterator first, iterator last) { _map.erase(first, last); }
  inline T &at(const Id &id) const {
    return const_cast<boost::ptr_map<Id, T> &>(_map).at(id);
  }
  iterator find(const Id &id) { return _map.find(id); }
  const_iterator find(const Id &id) const { return _map.find(id); }
  inline Id takeId() { return _sharedData->takeId(); }
  size_t count(const Id &id) const { return _map.count(id); }

  bool operator==(const IdDataMap<T> &m) const { return _map == m._map; }
  bool operator!=(const IdDataMap<T> &m) const { return _map != m._map; }

  iterator begin() { return _map.begin(); }
  const_iterator begin() const { return _map.begin(); }
  iterator end() { return _map.end(); }
  const_iterator end() const { return _map.end(); }

private:
  SharedDataPtr _sharedData;
  Map _map;
};

template <typename T>
QVariantMap
toVariantMap(typename boost::ptr_map<IdData::Id, T>::const_iterator first,
             typename boost::ptr_map<IdData::Id, T>::const_iterator last) {
  QVariantMap m;
  for (; first != last; ++first)
    m.insert(QString::number(first->first), first->second->toMap());
  return m;
}

template <typename T>
QVariantMap toVariantMap(const boost::ptr_map<IdData::Id, T> &map) {
  return toVariantMap<T>(map.begin(), map.end());
}

template <typename T> QVariantMap toVariantMap(const IdDataMap<T> &map) {
  return toVariantMap<T>(map.begin(), map.end());
}

template <typename T>
void fromVariantMap(const QVariantMap &src,
                    boost::ptr_map<IdData::Id, T> &dest) {
  for (auto it = src.begin(); it != src.end(); ++it) {
    auto key = it.key().toInt();
    auto value = it.value().toMap();
    auto i = dest.find(key);
    if (i != dest.end())
      i->second->assignFromMap(value);
    else
      dest.insert(key, T::fromMap(value));
  }
}

template <typename T>
void fromVariantMap(const QVariantMap &src, IdDataMap<T> &dest) {
  for (auto it = src.begin(); it != src.end(); ++it) {
    auto key = it.key().toInt();
    auto value = it.value().toMap();
    auto i = dest.find(key);
    if (i != dest.end())
      i->second->assignFromMap(value);
    else
      dest.insert(std::unique_ptr<T>(T::fromMap(value)));
  }
}

class Question : public IdData {
protected:
  Question(const Id id,
           const QDateTime &modification_date = QDateTime::currentDateTime());
  Question(const QVariantMap &m);

public:
  inline QString &title() { return _title; }
  void setTitle(const QString &title);

  static Question *fromMap(const QVariantMap &m);

protected:
  virtual QVariantMap do_toMap() const;
  virtual void do_assignFromMap(const QVariantMap &m);

private:
  virtual Data *do_clone() const;

private:
  QString _title;
};

inline Question *new_clone(const Question &q)  { return dynamic_cast<Question*>(q.clone()); }

class OpenedQuestion : public Question {
public:
  using Size = uint;

  OpenedQuestion(const Id id, const QDateTime &modification_date =
                                  QDateTime::currentDateTime());

  inline Size nbWords() const { return _nbWords; }
  void setNbWords(const Size nbWords);

  static OpenedQuestion *fromMap(const QVariantMap &m);

protected:
  OpenedQuestion(const QVariantMap &m);
  virtual QVariantMap do_toMap() const;
  virtual void do_assignFromMap(const QVariantMap &m);

private:
  virtual Data *do_clone() const;

private:
  Size _nbWords;
};

inline OpenedQuestion *new_clone(const OpenedQuestion &q)  { return dynamic_cast<OpenedQuestion*>(q.clone()); }

class Choice : public IdData {
public:
  Choice(const Id id,
         const QDateTime &modification_date = QDateTime::currentDateTime());

  inline const QString &label() const { return _label; }
  void setLabel(const QString &label);

  static Choice *fromMap(const QVariantMap &m);

protected:
  Choice(const QVariantMap &m);
  virtual QVariantMap do_toMap() const;
  virtual void do_assignFromMap(const QVariantMap &m);

private:
  virtual Data *do_clone() const;

private:
  QString _label;
};

inline Choice *new_clone(const Choice &c)  { return dynamic_cast<Choice*>(c.clone()); }

class ClosedQuestion : public Question {
public:
  using Choices = IdDataMap<Choice>;

  enum Type { Unique, Multiple };

  ClosedQuestion(
      const Type type, const Id id,
      Choices::SharedDataPtr sharedData =
          std::make_shared<Choices::SharedData>(),
      const QDateTime &modification_date = QDateTime::currentDateTime());

  inline Type type() const { return _type; }
  void setType(const Type type);

  inline const Choices &choices() const { return _choices; }
  void setChoices(const Choices &choices);

  static ClosedQuestion *fromMap(const QVariantMap &m);

protected:
  ClosedQuestion(const QVariantMap &m);
  virtual QVariantMap do_toMap() const;
  virtual void do_assignFromMap(const QVariantMap &m);

private:
  virtual Data *do_clone() const;

private:
  Type _type;
  Choices _choices;
};

inline ClosedQuestion *new_clone(const ClosedQuestion &q)  { return dynamic_cast<ClosedQuestion*>(q.clone()); }

class Answer : public Data {
public:
  using Id = IdData::Id;
  using Questions = IdDataMap<Question>;

protected:
  Answer(const Id question,
         const QDateTime &modification_date = QDateTime::currentDateTime());
  Answer(const QVariantMap &m);

public:
  inline Id question() const { return _question; }
  virtual bool isValid(const Questions &questions) const = 0;

  static Answer *fromMap(const QVariantMap &m);

protected:
  virtual QVariantMap do_toMap() const;
  virtual void do_assignFromMap(const QVariantMap &m);

private:
  virtual Data *do_clone() const = 0;

private:
  const Id _question;
};

inline Answer *new_clone(const Answer &a)  { return dynamic_cast<Answer*>(a.clone()); }

class OpenedAnswer : public Answer {
public:
  OpenedAnswer(const Id id, const QDateTime &modification_date =
                                QDateTime::currentDateTime());

  inline const QStringList &words() const { return _words; }
  void setWords(const QStringList &words);

  bool isValid(const Questions &questions) const;

  static OpenedAnswer *fromMap(const QVariantMap &m);
  static bool validMap(const QVariantMap &m);

protected:
  OpenedAnswer(const QVariantMap &m);
  virtual QVariantMap do_toMap() const;
  virtual void do_assignFromMap(const QVariantMap &m);

private:
  virtual Data *do_clone() const;

private:
  QStringList _words;
};

inline OpenedAnswer *new_clone(const OpenedAnswer &a)  { return dynamic_cast<OpenedAnswer*>(a.clone()); }

class ClosedAnswer : public Answer {
public:
  using Choices = QList<Id>;

  ClosedAnswer(const Id id, const QDateTime &modification_date =
                                QDateTime::currentDateTime());

  inline const Choices &choices() const { return _choices; }
  void setChoices(const Choices &choices);

  bool isValid(const Questions &questions) const;

  static ClosedAnswer *fromMap(const QVariantMap &m);
  static bool validMap(const QVariantMap &m);

protected:
  ClosedAnswer(const QVariantMap &m);
  virtual QVariantMap do_toMap() const;
  virtual void do_assignFromMap(const QVariantMap &m);

private:
  virtual Data *do_clone() const;

private:
  Choices _choices;
};

inline ClosedAnswer *new_clone(const ClosedAnswer &a)  { return dynamic_cast<ClosedAnswer*>(a.clone()); }

class Subject : public IdData {
public:
  using Answers = boost::ptr_map<Id, Answer>;

  Subject(const Id id,
          const QDateTime &modification_date = QDateTime::currentDateTime());

  bool isValid() const { return _isValid; }
  void setIsValid(const bool isValid);

  inline const Answers &answers() const { return _answers; }
  void setAnswers(const Answers &answers);

  bool areAnswersValid() const;

  static Subject *fromMap(const QVariantMap &m);

protected:
  Subject(const QVariantMap &m);
  virtual QVariantMap do_toMap() const;
  virtual void do_assignFromMap(const QVariantMap &m);

private:
  virtual Data *do_clone() const;

private:
  bool _isValid;
  Answers _answers;
};

inline Subject *new_clone(const Subject &s)  { return dynamic_cast<Subject*>(s.clone()); }

class Form : public IdData {
public:
  using Questions = IdDataMap<Question>;
  using Subjects = IdDataMap<Subject>;

  Form(const Id id,
       Questions::SharedDataPtr questionsSharedData =
           std::make_shared<Questions::SharedData>(),
       Subjects::SharedDataPtr subjectsSharedData =
           std::make_shared<Subjects::SharedData>(),
       const QDateTime &modification_date = QDateTime::currentDateTime());

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

  static Form *fromMap(const QVariantMap &m);

protected:
  Form(const QVariantMap &m);
  virtual QVariantMap do_toMap() const;
  virtual void do_assignFromMap(const QVariantMap &m);

private:
  virtual Data *do_clone() const;

private:
  QString _name;
  QString _description;
  QDateTime _creation_date;
  Questions _questions;
  Subjects _subjects;
};

inline Form *new_clone(const Form &f)  { return dynamic_cast<Form*>(f.clone()); }

}
}

Q_DECLARE_METATYPE(semantics::core::ClosedQuestion::Type)

#endif

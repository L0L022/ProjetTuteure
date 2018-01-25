#ifndef PERSISTENCE_TABLES_HPP
#define PERSISTENCE_TABLES_HPP

#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QVariant>

namespace persistence {

class Form {
public:
  static const QString table;
  static const QStringList columns;

  Form() = default;
  Form(const QVariantMap &v);

  QVariantMap toMap() const;

  int id;
  QString name;
  QString description;
  QDateTime creation_date;
  QDateTime modification_date;
};

class Question {
public:
  static const QString table;
  static const QStringList columns;

  Question() = default;
  Question(const QVariantMap &v);

  QVariantMap toMap() const;

  int id;
  int form;
  QString title;
  QString type;
  int nb_words;
  QDateTime modification_date;
};

class Choice {
public:
  static const QString table;
  static const QStringList columns;

  Choice() = default;
  Choice(const QVariantMap &v);

  QVariantMap toMap() const;

  int id;
  int question;
  QString label;
  QDateTime modification_date;
};

class Subject {
public:
  static const QString table;
  static const QStringList columns;

  Subject() = default;
  Subject(const QVariantMap &v);

  QVariantMap toMap() const;

  int id;
  int form;
  bool is_valid;
  QDateTime modification_date;
};

class OpenedAnswer {
public:
  static const QString table;
  static const QStringList columns;

  OpenedAnswer() = default;
  OpenedAnswer(const QVariantMap &v);

  QVariantMap toMap() const;

  int subject;
  int question;
  QString words;
  QDateTime modification_date;
};

class ClosedAnswer {
public:
  static const QString table;
  static const QStringList columns;

  ClosedAnswer() = default;
  ClosedAnswer(const QVariantMap &v);

  QVariantMap toMap() const;

  int subject;
  int choice;
  QDateTime modification_date;
};

} // namespace persistence
#endif

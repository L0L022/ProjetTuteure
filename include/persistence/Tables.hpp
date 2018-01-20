#ifndef PERSISTENCE_TABLES_HPP
#define PERSISTENCE_TABLES_HPP

#include <QDateTime>
#include <QString>
#include <QStringList>

namespace persistence {

class Form {
public:
  static const QString table;
  static const QStringList columns;

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

  int id;
  int id_form;
  QString title;
  QString type;
  int nbWords;
  QDateTime modification_date;
};

class Choice {
public:
  static const QString table;
  static const QStringList columns;

  int id;
  int id_question;
  QString label;
  QDateTime modification_date;
};

class Subject {
public:
  static const QString table;
  static const QStringList columns;

  int id;
  int id_form;
  bool isValid;
  QDateTime modification_date;
};

class Answer {
public:
  static const QString table;
  static const QStringList columns;

  int id_subject;
  int id_question;
  QString words;
  QDateTime modification_date;
};

} // namespace persistence
#endif

#ifndef SEMANTICS_CORE_FORM_HPP
#define SEMANTICS_CORE_FORM_HPP

#include "Question.hpp"
#include "Subject.hpp"

class Form : public Data {
public:
  inline const QString &name() const { return _name; }
  void setName(const QString &name);

  inline const QString &description() const { return _description; }
  void setDescription(const QString &description);

  inline const QDateTime &creation_date() const { return _creation_date; }
  void setCreation_date(const QDateTime &creation_date); // réfléchir

private:
  QString _name;
  QString _description;
  QDateTime _creation_date;
  QMap<int, Question> _questions;
  QMap<int, Subject> _subjects;
};

#endif

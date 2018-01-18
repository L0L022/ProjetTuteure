#ifndef SEMANTICS_CORE_FORM_HPP
#define SEMANTICS_CORE_FORM_HPP

#include <QDate>
#include <QString>

class Form {

private:
  int id_form;

  QDate creation_date;
  QDate change_date;
  QString name;
  QString description;

public:
  Form(int _id_form, QString _name, QString _description, QDate _creation_date);
  Form();
  ~Form();

  inline int getIdForm() { return id_form; };

  inline QString getName() { return name; };
  inline QString getDescription(){return description};
  inline QDate getCreationDate() { return creation_date; };
  inline QDate getChangeDate() { return change_date; };

  void setName(QString _name);
  void setDescription(QString _description);
  inline void setChangeDate(QDate _change_date) { change_date = _change_date; };
}

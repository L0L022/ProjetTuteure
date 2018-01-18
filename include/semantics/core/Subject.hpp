#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <QString>
#include <QDate>

class Subject {

private:

  int subject_id;

  QDate change_date;
  bool validate;

public:

  Subject(int _subject_id, QDate change_date);
  Subject();
  ~Subject();

  inline int getIdForm(){ return id_form;};

  void setName(QString _name);
  void setValidate(bool _valide);
  inline void setChangeDate(QDate _change_date){ change_date = _change_date;};

}

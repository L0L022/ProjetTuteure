#ifndef REPLY_HPP
#define REPLY_HPP

#include <QString>
#include <QDate>

class Reply {

private:

  int id_reponse;
  QDate change_date;

public:

  Reply(int _id_reponse,QDate _creation_date);
  Reply();
  ~Reply();

  inline int getIdForm(){ return id_form;};

  inline QDate getChangeDate(){return change_date;};

  inline void setChangeDate(QDate _change_date){ change_date = _change_date;};
}

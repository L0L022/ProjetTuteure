#ifndef QUESTION_HPP
#ifndef QUESTION_HPP

#include <QString>
#include <QDate>


class Question {

private:

  int id_question;
  QDate change_date;
  QString label;

public:

  Question(int _id_question, QDate _change_date, QString _label);
  Question();
  ~Question();

  inline int getIdQuestion(){ return id_question};
  inline QString getLabel(){return label};
  inline Qdate getChangeDate(){ return change_date};

  void setLabel(QString _label);
  void setChangeDate(QDate _change_date);

}

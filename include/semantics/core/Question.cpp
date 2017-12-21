#include "../../../include/semantics/core/Question.hpp"

Question::Question(int _id_question, QDate _change_date, QString _label)
:id_question(_id_question),change_date(_change_date),label(_label){

}

Question::Question()
:id_question(0),change_date(QDate::currentDate()),label("");

void Question::setLabel(QString _label){
  label = _label;
  setChangeDate(QDate::currentDate);
}

void Question::setChangeDate(QDate _change_date){
  change_date = _change_date;
}

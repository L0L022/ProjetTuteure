#include "../../../include/semantics/core/Reply.hpp"

Reply::Reply(int _id_question, QDate _change_date)
:id_question(_id_question),change_date(_change_date){
}

Reply::Reply()
:id_question(0),change_date(QDate::currentDate());

void Question::setChangeDate(QDate _change_date){
  change_date = _change_date;
}

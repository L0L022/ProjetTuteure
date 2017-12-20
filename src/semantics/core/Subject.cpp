#include "../../../include/semantics/core/Subject.hpp"

Subject::Subject(int _subject_id, QDate _change_date)
:subject_id(_subject_id),change_date(_change_date){

}

Subject::Subject(){
  
}

Subject::setName(QString _name){
  name = _name;
  setChangeDate(QDate::currentDate());
}

Subject::setValidate(){
  validate = !validate;
  setChangeDate(QDate::currentDate());
}

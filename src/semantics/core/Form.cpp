#include "../../../include/semantics/core/Form.hpp"

Form::Form(int _id_form, QString _name, QString _description,QDate _creation_date)
:id_form(_id_form),name(_name),description(_description),creation_date(_creation_date),change_date(_creation_date){

}

Form::Form()
:id_form(0),name(0),description(0),creation_date(QDate::currentDate()),change_date(QDate::currentDate()){
}

Form::setName(QString _name){
  name = _name;
  setChangeDate(QDate::currentDate());
}

Form::setDescription(QString _description){
  description = _description;
  setChangeDate(QDate::currentDate());
}

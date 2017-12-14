#include "../../../include/semantics/core/Services.hpp"

Services::Services(Qobjet *parent = nullptr)
:QObjet(parent){

}

Services::~Services(){

}

QvariantMap Services::sendCommand(std::string id, QVariantMap param){
  qDebug() << "id = "<< id << "param=" << param;
  return param;
}

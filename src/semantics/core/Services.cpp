#include <semantics/core/Services.hpp>

#include <QDebug>

Services::Services(QObject *parent) : QObject(parent) {}

QVariantMap Services::run(const QString &id, const QVariantMap &args) {
  qDebug() << "id: " << id << " args: " << args;

//  QVariantMap r = ;
//  r["nombre"] = -29;
//  r["chaine de charactères"] = "string!";
//  r["tableau"] = QVariantList() << "str" << 10 << 20 << 30 << "blabla";

  QVariantMap r;

  if (_functions.contains(id))
    r = _functions[id](args);
  else
    r["error"] = "Cant't find function";

  return r;
}

void Services::insertFunction(const QString &id, const Function& f) {
    _functions[id] = f;
}

void Services::removeFunction(const QString &id) {
    _functions.remove(id);
}

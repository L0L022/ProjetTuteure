#include <semantics/core/Services.hpp>

#include <QDebug>

Services::Services(QObject *parent) : QObject(parent) {}

QVariantMap Services::run(const QString &id, const QVariantMap &args) {
  qDebug() << "id: " << id << " args: " << args;

  QVariantMap r;

  if (_functions.contains(id))
    r = _functions[id](args);
  else
    r["error"] = "Services cant't find function";

  qDebug() << "r: " << r;

  return r;
}

void Services::insertFunction(const QString &id, const Function& f) {
    _functions[id] = f;
}

void Services::removeFunction(const QString &id) {
    _functions.remove(id);
}

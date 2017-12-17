#include <semantics/core/Services.hpp>

#include <QDebug>

Services::Services(QObject *parent) : QObject(parent) {}

QVariantMap Services::sendCommand(const QString &id, const QVariantMap &args) {
  qDebug() << "id: " << id << " args: " << args;

  QVariantMap r;
  r["nombre"] = -29;
  r["chaine de charactères"] = "string!";
  r["tableau"] = QVariantList() << "str" << 10 << 20 << 30 << "blabla";
  return r;
}

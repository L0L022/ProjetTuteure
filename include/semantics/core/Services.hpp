#ifndef SERVICES_H
#define SERVICES_H

#include <QDebug>
#include <QTime>
#include <QTimer>
#include <Qvariant>

class Services : public QObject {

public:

  explicit Services(Qobjet *parent = nullptr);
  ~Services();

  QvariantMap sendCommand(std::string id, QVariantMap param);



};

#endif

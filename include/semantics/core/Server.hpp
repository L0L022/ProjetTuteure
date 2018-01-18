#ifndef SEMANTICS_CORE_SERVER_HPP
#define SEMANTICS_CORE_SERVER_HPP

#include <QWebSocketServer>

class Server : public QObject {
  Q_OBJECT
public:
  explicit Server(QObject *parent = nullptr);

  void start();
  void stop();

signals:
  void error(const QString &error);

private:
  QWebSocketServer *_server;
};

#endif

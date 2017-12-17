#ifndef SERVER_HPP
#define SERVER_HPP

#include <QObject>

class Server : public QObject {
  Q_OBJECT
public:
  explicit Server(QObject *parent = nullptr);
};

#endif

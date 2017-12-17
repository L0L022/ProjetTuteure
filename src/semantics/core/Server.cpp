#include <semantics/core/Server.hpp>

#include <semantics/core/Services.hpp>
#include <semantics/core/WebSocketClientWrapper.hpp>
#include <semantics/core/WebSocketTransport.hpp>

#include <QWebChannel>
#include <QWebSocketServer>

Server::Server(QObject *parent) : QObject(parent) {
  auto *server = new QWebSocketServer(
      QStringLiteral("QWebChannel Standalone Example Server"),
      QWebSocketServer::NonSecureMode, this);

  if (!server->listen(QHostAddress::LocalHost, 12345)) {
    qFatal("Failed to open web socket server.");
  }

  auto *clientWrapper = new WebSocketClientWrapper(server, this);

  auto *channel = new QWebChannel(this);
  connect(clientWrapper, &WebSocketClientWrapper::clientConnected, channel,
          &QWebChannel::connectTo);

  auto *services = new Services(this);
  channel->registerObject(QStringLiteral("services"), services);
}

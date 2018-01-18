#include <semantics/core/Server.hpp>

#include <semantics/core/UIServices.hpp>
#include <semantics/core/WebSocketClientWrapper.hpp>
#include <semantics/core/WebSocketTransport.hpp>

#include <QWebChannel>

Server::Server(QObject *parent) : QObject(parent), _server(nullptr) {
  _server = new QWebSocketServer(
      QStringLiteral("QWebChannel Standalone Example Server"),
      QWebSocketServer::NonSecureMode, this);

  connect(_server, &QWebSocketServer::serverError, this, [this](){ emit error(_server->errorString()); });

  auto *clientWrapper = new WebSocketClientWrapper(_server, this);

  auto *channel = new QWebChannel(this);
  connect(clientWrapper, &WebSocketClientWrapper::clientConnected, channel,
          &QWebChannel::connectTo);

  auto *services = new UIServices(this);
  channel->registerObject(QStringLiteral("services"), services);
}

void Server::start() {
    if (!_server->listen(QHostAddress::LocalHost, 12345)) {
      qFatal("Failed to open web socket server.");
    }
}

void Server::stop() {
    _server->close();
}

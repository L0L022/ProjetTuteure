#include <semantics/core/Services.hpp>
#include <semantics/core/WebSocketClientWrapper.hpp>
#include <semantics/core/WebSocketTransport.hpp>

#include <QApplication>
#include <QWebChannel>
#include <QWebSocketServer>

#include <QWebEngineView>

int main(int argc, char** argv) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QWebSocketServer server(QStringLiteral("QWebChannel Standalone Example Server"),
                            QWebSocketServer::NonSecureMode);
    if (!server.listen(QHostAddress::LocalHost, 12345)) {
        qFatal("Failed to open web socket server.");
        return 1;
    }

    // wrap WebSocket clients in QWebChannelAbstractTransport objects
    WebSocketClientWrapper clientWrapper(&server);

    // setup the channel
    QWebChannel channel;
    QObject::connect(&clientWrapper, &WebSocketClientWrapper::clientConnected,
                     &channel, &QWebChannel::connectTo);

    // setup the dialog and publish it to the QWebChannel
    Services* services = new Services(&app);
    channel.registerObject(QStringLiteral("services"), services);

    QWebEngineView view;
    view.setUrl(QUrl("qrc:/gui/index.html"));
    view.show();

    return app.exec();
}

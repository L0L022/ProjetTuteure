#include <presentation/MainWindow.hpp>

#include <semantics/core/Server.hpp>

#include <QWebEngineView>

inline void init_ressource() { Q_INIT_RESOURCE(ui); }

namespace sc = semantics::core;

namespace presentation {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _server_thread(nullptr) {
  init_ressource();

  setWindowTitle(QStringLiteral("ProjetTuteure"));
  resize(700, 600);

  _server_thread = new QThread(this);
  auto *server = new sc::Server;
  server->moveToThread(_server_thread);

  connect(_server_thread, &QThread::started, server, &sc::Server::start);
  connect(this, &MainWindow::destroyed, server, &sc::Server::deleteLater);

  _server_thread->start();

  auto *view = new QWebEngineView(this);
  view->setUrl(QUrl("qrc:/index.html"));
  setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    _server_thread->quit();
    _server_thread->wait();
}

}

#include <presentation/MainWindow.hpp>

#include <semantics/core/Server.hpp>

#include <QWebEngineView>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _server_thread(nullptr) {
  Q_INIT_RESOURCE(ui);

  setWindowTitle(QStringLiteral("ProjetTuteure"));
  resize(700, 600);

  _server_thread = new QThread(this);
  auto *server = new Server;
  server->moveToThread(_server_thread);

  connect(_server_thread, &QThread::started, server, &Server::start);
  connect(this, &MainWindow::destroyed, server, &Server::deleteLater);

  _server_thread->start();

  auto *view = new QWebEngineView(this);
  view->setUrl(QUrl("qrc:/ui/index.html"));
  setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    _server_thread->quit();
    _server_thread->wait();
}

#include <presentation/MainWindow.hpp>

#include <semantics/core/Server.hpp>

#include <QWebEngineView>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  Q_INIT_RESOURCE(ui);

  setWindowTitle(QStringLiteral("ProjetTuteure"));
  resize(700, 600);

  auto *server = new Server(this);

  if(QString error = Server.serverError() != "")
    qWarning(error);

  auto *view = new QWebEngineView(this);
  view->setUrl(QUrl("qrc:/ui/index.html"));
  setCentralWidget(view);
}

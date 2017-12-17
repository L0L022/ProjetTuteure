#include <QApplication>

#include <presentation/MainWindow.hpp>

int main(int argc, char **argv) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);

  MainWindow w;
  w.show();

  return app.exec();
}

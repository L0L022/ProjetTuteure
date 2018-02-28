#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QMessageBox>

#include <presentation/MainWindow.hpp>

int main(int argc, char **argv) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);

  QTranslator qtTranslator;
  qtTranslator.load("qt_" + QLocale::system().name(),
          QLibraryInfo::location(QLibraryInfo::TranslationsPath));
  app.installTranslator(&qtTranslator);

  int r = EXIT_FAILURE;
  try {
      MainWindow w;
      w.show();

      r = app.exec();
  } catch (const std::exception &e) {
      QMessageBox::critical(nullptr, QCoreApplication::translate("main", "An exception occurred"), QString::fromLocal8Bit(e.what()));
  }

  return r;
}

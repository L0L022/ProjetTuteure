#ifndef PRESENTATION_MAINWINDOW_HPP
#define PRESENTATION_MAINWINDOW_HPP

#include <QMainWindow>
#include <QThread>

namespace presentation {

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  QThread *_server_thread;
};

}

#endif

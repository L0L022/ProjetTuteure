#ifndef PERSISTENCE_SQLITE_TESTS_HPP
#define PERSISTENCE_SQLITE_TESTS_HPP

#include <QtTest/QtTest>

#include <QScopedPointer>

#include "DAOFactory.hpp"

namespace persistence {
namespace SQLite {

class Tests : public QObject {
  Q_OBJECT

public:
  Tests(QObject *parent = nullptr);

private slots:
  void initTestCase();
  void init();
  void cleanup();

  void search_data();
  void search();

  void save_data();
  void save();

  void remove_data();
  void remove();

private:
  QScopedPointer<DAOFactory> _factory;
};

} // namespace SQLite
} // namespace persistence

#endif

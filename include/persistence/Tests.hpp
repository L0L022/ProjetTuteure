#ifndef PERSISTENCE_TESTS_HPP
#define PERSISTENCE_TESTS_HPP

#include "DAOFactory.hpp"

#include <QtTest/QtTest>

namespace persistence {

class Tests : public QObject {
  Q_OBJECT

public:
  Tests(QObject *parent = nullptr);

private slots:
  void select_data();
  void select();
  void insert_data();
  void insert();
  void update_data();
  void update();
  void remove_data();
  void remove();
};

} // namespace persistence

#endif

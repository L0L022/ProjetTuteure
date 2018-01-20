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
  void insert_data();
  void insert();
};

} // namespace persistence

#endif

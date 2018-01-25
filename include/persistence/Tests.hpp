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
  void search_data();
  void search();
  void save_data();
  void save();
  void remove_data();
  void remove();
};

} // namespace persistence

#endif

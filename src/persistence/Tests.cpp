#include <persistence/Tests.hpp>

#include <persistence/DAOFactory.hpp>

using namespace persistence;

Q_DECLARE_METATYPE(DAOFactory::Drivers)

Tests::Tests(QObject *parent) : QObject(parent) {}

void Tests::insert_data() {
  QTest::addColumn<DAOFactory::Drivers>("driver");

  QTest::newRow("SQLite") << DAOFactory::SQLite;
}

void Tests::insert() {
  QFETCH(DAOFactory::Drivers, driver);
  DAOFactory *factory = DAOFactory::make(driver);
  delete factory;
}

QTEST_MAIN(Tests)

#include <persistence/Tests.hpp>

#include <persistence/DAOFactory.hpp>
#include <persistence/Exception.hpp>

#include <QDebug>
#include <QScopedPointer>

using namespace persistence;

Q_DECLARE_METATYPE(DAOFactory::Drivers)

Tests::Tests(QObject *parent) : QObject(parent) {}

void Tests::select_data() {
  QTest::addColumn<DAOFactory::Drivers>("driver");

  QTest::newRow("SQLite") << DAOFactory::SQLite;
}

void Tests::select() {
  QFETCH(DAOFactory::Drivers, driver);
  QScopedPointer<DAOFactory> factory(DAOFactory::make(driver));
  {
    QScopedPointer<DAO<Form>> form(factory->form());
    const QVariantMap where{};
    auto results = form->select(where);
    for (const Form &f : results)
      qDebug() << f.id << f.name << f.description;
  }
}

void Tests::insert_data() {
  QTest::addColumn<DAOFactory::Drivers>("driver");

  QTest::newRow("SQLite") << DAOFactory::SQLite;
}

void Tests::insert() {
  QFETCH(DAOFactory::Drivers, driver);
  QScopedPointer<DAOFactory> factory(DAOFactory::make(driver));
  {
    QScopedPointer<DAO<Form>> form(factory->form());
    const QVariantMap values{{"id", 1}};
    try {
      QVariant id = form->insert(values);
    } catch (Exception &e) {
      qDebug() << e.text();
    }
  }
}

void Tests::update_data() {
  QTest::addColumn<DAOFactory::Drivers>("driver");

  QTest::newRow("SQLite") << DAOFactory::SQLite;
}

void Tests::update() {
  QFETCH(DAOFactory::Drivers, driver);
  QScopedPointer<DAOFactory> factory(DAOFactory::make(driver));
  {
    QScopedPointer<DAO<Form>> form(factory->form());
    const QVariantMap set{};
    const QVariantMap where{};
    try {
      form->update(set, where);
    } catch (Exception &e) {
      qDebug() << e.text();
    }
  }
}

void Tests::remove_data() {
  QTest::addColumn<DAOFactory::Drivers>("driver");

  QTest::newRow("SQLite") << DAOFactory::SQLite;
}

void Tests::remove() {
  QFETCH(DAOFactory::Drivers, driver);
  QScopedPointer<DAOFactory> factory(DAOFactory::make(driver));
  {
    QScopedPointer<DAO<Form>> form(factory->form());
    const QVariantMap where{};
    try {
      form->remove(where);
    } catch (Exception &e) {
      qDebug() << e.text();
    }
  }
}

QTEST_MAIN(Tests)

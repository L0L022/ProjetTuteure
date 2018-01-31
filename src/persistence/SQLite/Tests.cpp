#include <persistence/Tests.hpp>

#include <persistence/DAOFactory.hpp>
#include <persistence/Exception.hpp>

#include <QDebug>
#include <QScopedPointer>

using namespace persistence;

Q_DECLARE_METATYPE(DAOFactory::Drivers)

Tests::Tests(QObject *parent) : QObject(parent) {}

void Tests::search_data() {
  QTest::addColumn<DAOFactory::Drivers>("driver");

  QTest::newRow("SQLite") << DAOFactory::SQLite;
}

void Tests::search() {
  QFETCH(DAOFactory::Drivers, driver);
  QScopedPointer<DAOFactory> factory(DAOFactory::make(driver));
  {
    QScopedPointer<DAO<Form>> form(factory->form());
    const QVariantMap where{};
    auto results = form->search(where);
    for (const Form &f : results)
      qDebug() << f.id << f.name << f.description;
  }
}

void Tests::save_data() {
  QTest::addColumn<DAOFactory::Drivers>("driver");

  QTest::newRow("SQLite") << DAOFactory::SQLite;
}

void Tests::save() {
  QFETCH(DAOFactory::Drivers, driver);
  QScopedPointer<DAOFactory> factory(DAOFactory::make(driver));
  {
    QScopedPointer<DAO<Form>> form(factory->form());

    Form f;
    f.id = 1;
    f.name = "Nouveau nom";
    f.description = "Nouvelle description";
    f.creation_date = QDateTime::currentDateTime();
    f.modification_date = QDateTime::currentDateTime();

    try {
      form->save(f);

      const QVariantMap where{};
      auto results = form->search(where);
      for (const Form &f : results)
        qDebug() << f.id << f.name << f.description;
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

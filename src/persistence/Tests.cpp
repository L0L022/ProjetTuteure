#include <persistence/Tests.hpp>

#include <persistence/DAOFactory.hpp>

#include <QDebug>

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
  {
    DAO<Form> *form = factory->form();
    const QVariantMap &v{};
    auto results = form->select(v);
    for (const Form &f : results)
      qDebug() << f.id << f.name << f.description;
    delete form;
  }
  {
    DAO<Question> *question = factory->question();
    const QVariantMap &v{};
    auto results = question->select(v);
    for (const Question &q : results)
      qDebug() << q.id << q.title << q.form;
    delete question;
  }
  delete factory;
}

QTEST_MAIN(Tests)

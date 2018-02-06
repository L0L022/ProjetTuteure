#include <persistence/SQLite/Tests.hpp>

#include <persistence/DAOFactory.hpp>
#include <persistence/Exception.hpp>

#include <QDebug>
#include <QFile>
#include <QDateTime>

using namespace persistence::SQLite;

inline void init_ressource() { Q_INIT_RESOURCE(sqlite); }

Tests::Tests(QObject *parent) : QObject(parent) { init_ressource(); }

void Tests::initTestCase() {}

void Tests::init() {
  _factory.reset(new DAOFactory);
  run_sql(":/sqlite/init_db.sql");
  run_sql(":/sqlite/init_tests.sql");
}

void Tests::cleanup() { _factory.reset(); }

void Tests::search_data() {
  QTest::addColumn<QVariantMap>("where");
  QTest::addColumn<QVector<int>>("result");

  QTest::newRow("Questions ouvertes")
      << QVariantMap{{"type", "opened"}} << QVector<int>{1, 4, 7};
  QTest::newRow("Questions uniques")
      << QVariantMap{{"type", "unique"}} << QVector<int>{2, 5, 8};
  QTest::newRow("Questions multiples")
      << QVariantMap{{"type", "multiple"}} << QVector<int>{3, 6};
}

void Tests::search() {
  QFETCH(QVariantMap, where);
  QFETCH(QVector<int>, result);

  QScopedPointer<persistence::DAO<Question>> question(_factory->question());
  try {
    auto results = question->search(where);
    for (const Question &q : results)
      QCOMPARE(result.removeAll(q.id), 1);
    QCOMPARE(result.size(), 0);
  } catch (Exception &e) {
    QFAIL(e.text().toUtf8().constData());
  }
}

void Tests::save_data() {
  QTest::addColumn<QVariantMap>("data");

  QTest::newRow("Test 9 ouverte")
      << QVariantMap{{"id", 9},
                     {"form", 1},
                     {"title", "Test 9 ouverte"},
                     {"type", "opened"},
                     {"nb_words", 10},
                     {"modification_date", QDateTime::currentDateTime()}};

  QTest::newRow("Test 10 unique")
      << QVariantMap{{"id", 10},
                     {"form", 1},
                     {"title", "Test 10 unique"},
                     {"type", "unique"},
                     {"nb_words", 0},
                     {"modification_date", QDateTime::currentDateTime()}};

  QTest::newRow("Test 11 multiple")
      << QVariantMap{{"id", 11},
                     {"form", 1},
                     {"title", "Test 11 multiple"},
                     {"type", "multiple"},
                     {"nb_words", 0},
                     {"modification_date", QDateTime::currentDateTime()}};
}

void Tests::save() {
  QFETCH(QVariantMap, data);

  QScopedPointer<persistence::DAO<Question>> question(_factory->question());
  Question q(data);
  try {
    question->save(q);
    auto results = question->search(data);
    QCOMPARE(results.size(), 1);
  } catch (Exception &e) {
    QFAIL(e.text().toUtf8().constData());
  }
}

void Tests::remove_data() {
    QTest::addColumn<QVariantMap>("where");

    QTest::newRow("Question 1") << QVariantMap{{"id", 1}};
    QTest::newRow("Question 2") << QVariantMap{{"id", 2}};
    QTest::newRow("Question 3") << QVariantMap{{"id", 3}};
    QTest::newRow("Question 7") << QVariantMap{{"id", 7}};
}

void Tests::remove() {
    QFETCH(QVariantMap, where);

    QScopedPointer<persistence::DAO<Question>> question(_factory->question());
    try {
      question->remove(where);
      auto results = question->search(where);
      QCOMPARE(results.size(), 0);
    } catch (Exception &e) {
      QFAIL(e.text().toUtf8().constData());
    }
}

void Tests::run_sql(const QString &fileName) {
  QFile file(fileName);

  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    qDebug() << " Could not open the file for reading";
    return;
  }

  QString commands = file.readAll();

  for (const QString &command : commands.split(';')) {
    QSqlQuery query;
    query.prepare(command);
    query.exec();
  }
}

QTEST_MAIN(Tests)

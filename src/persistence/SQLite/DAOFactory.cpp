#include <persistence/SQLite/DAOFactory.hpp>

#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>

using namespace persistence;

SQLite::DAOFactory::DAOFactory(const QString &name) {
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(name);
  if (!db.open())
    throw SQLErrorException("Connect to the db.", db.lastError());

  QSqlQuery query;
  prepareQuery(query, "PRAGMA foreign_keys = ON;");
  execQuery(query);
}

SQLite::DAOFactory::~DAOFactory() {
  if (QSqlDatabase::database().isValid()) {
    QString name = QSqlDatabase::database().connectionName();
    QSqlDatabase::removeDatabase(name);
  }
}

DAO<Form> *SQLite::DAOFactory::form() { return new SQLite::DAO<Form>(); }

DAO<Question> *SQLite::DAOFactory::question() {
  return new SQLite::DAO<Question>();
}

DAO<Choice> *SQLite::DAOFactory::choice() { return new SQLite::DAO<Choice>(); }

DAO<Subject> *SQLite::DAOFactory::subject() {
  return new SQLite::DAO<Subject>();
}

DAO<OpenedAnswer> *SQLite::DAOFactory::openedAnswer() {
  return new SQLite::DAO<OpenedAnswer>();
}

DAO<ClosedAnswer> *SQLite::DAOFactory::closedAnswer() {
  return new SQLite::DAO<ClosedAnswer>();
}

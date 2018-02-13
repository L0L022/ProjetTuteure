#include <persistence/SQLite/DAOFactory.hpp>

#include <persistence/SQLite/DAO.hpp>

#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>

using namespace persistence;

inline void init_ressource() { Q_INIT_RESOURCE(sqlite); }

SQLite::DAOFactory::DAOFactory(const QString &name) {
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(name);
  if (!db.open())
    throw SQLErrorException("Connect to the db.", db.lastError());

  init_ressource();
  SQLite::runSQLFromFile(":/sqlite/init_db.sql");
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

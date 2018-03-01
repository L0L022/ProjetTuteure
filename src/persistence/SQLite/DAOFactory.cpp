#include <persistence/SQLite/DAOFactory.hpp>

#include <persistence/SQLite/DAO.hpp>

#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>

inline void init_ressource() { Q_INIT_RESOURCE(sqlite); }

namespace persistence {
namespace SQLite {


DAOFactory::DAOFactory(const QString &name) {
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(name);
  if (!db.open())
    throw SQLErrorException("Connect to the db.", db.lastError());

  init_ressource();
  runSQLFromFile(":/sqlite/init_db.sql");
}

DAOFactory::~DAOFactory() {
  if (QSqlDatabase::database().isValid()) {
    QString name = QSqlDatabase::database().connectionName();
    QSqlDatabase::removeDatabase(name);
  }
}

persistence::DAO<Form> *DAOFactory::form() { return new DAO<Form>(); }

persistence::DAO<Question> *DAOFactory::question() {
  return new DAO<Question>();
}

persistence::DAO<Choice> *DAOFactory::choice() { return new DAO<Choice>(); }

persistence::DAO<Subject> *DAOFactory::subject() {
  return new DAO<Subject>();
}

persistence::DAO<OpenedAnswer> *DAOFactory::openedAnswer() {
  return new DAO<OpenedAnswer>();
}

persistence::DAO<ClosedAnswer> *DAOFactory::closedAnswer() {
  return new DAO<ClosedAnswer>();
}

}
}

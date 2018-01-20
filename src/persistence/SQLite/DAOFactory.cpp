#include <persistence/SQLite/DAOFactory.hpp>

#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>

using namespace persistence;

inline void init_ressource() { Q_INIT_RESOURCE(sqlite); }

SQLite::DAOFactory::DAOFactory() {
  init_ressource();
  // mettre dans un fonction
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(":memory:");
  bool ok = db.open();
  create_table();
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

void SQLite::DAOFactory::create_table() {
  init_ressource();
  QFile file(":/sqlite/init.sql");

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

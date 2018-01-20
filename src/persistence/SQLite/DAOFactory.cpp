#include <persistence/SQLite/DAOFactory.hpp>

#include <QSqlDatabase>

using namespace persistence;

SQLite::DAOFactory::DAOFactory() {
  // mettre dans un fonction
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(":memory:");
  bool ok = db.open();
}

DAO<Form> *SQLite::DAOFactory::form() { return new SQLite::DAO<Form>(); }
DAO<Question> *SQLite::DAOFactory::question() {
  return new SQLite::DAO<Question>();
}
DAO<Choice> *SQLite::DAOFactory::choice() { return new SQLite::DAO<Choice>(); }
DAO<Subject> *SQLite::DAOFactory::subject() {
  return new SQLite::DAO<Subject>();
}
DAO<Answer> *SQLite::DAOFactory::answer() { return new SQLite::DAO<Answer>(); }

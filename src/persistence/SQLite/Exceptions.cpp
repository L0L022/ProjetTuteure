#include <persistence/SQLite/Exceptions.hpp>

using namespace persistence;

void SQLite::prepareQuery(QSqlQuery &query, const QString &sql) {
  if (!query.prepare(sql)) {
    throw QueryPrepareException(sql);
  }
}

void SQLite::execQuery(QSqlQuery &query) {
  if (!query.exec()) {
    throw SQLErrorException(query.lastQuery(), query.lastError());
  }
}

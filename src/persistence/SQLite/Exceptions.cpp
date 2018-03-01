#include <persistence/SQLite/Exceptions.hpp>

namespace persistence {
namespace SQLite {

void prepareQuery(QSqlQuery &query, const QString &sql) {
  if (!query.prepare(sql)) {
    throw QueryPrepareException(sql);
  }
}

void execQuery(QSqlQuery &query) {
  if (!query.exec()) {
    throw SQLErrorException(query.lastQuery(), query.lastError());
  }
}

}
}

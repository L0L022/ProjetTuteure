#ifndef PERSISTENCE_SQLITE_EXCEPTIONS_HPP
#define PERSISTENCE_SQLITE_EXCEPTIONS_HPP

#include "../Exception.hpp"

#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QVariant>

namespace persistence {
namespace SQLite {

class QueryPrepareException : public persistence::Exception {
public:
  QString query;

  explicit QueryPrepareException(const QString &query) : query(query) {}

  void raise() const { throw *this; }

  QueryPrepareException *clone() const {
    return new QueryPrepareException(*this);
  }

  QString text() const {
    return QString("QSqlQuery can't prepare this query: %1").arg(query);
  }
};

class SQLErrorException : public persistence::Exception {
public:
  QString query;
  QSqlError sqlError;

  explicit SQLErrorException(const QString &query, const QSqlError &error)
      : query(query), sqlError(error) {}

  void raise() const { throw *this; }

  SQLErrorException *clone() const { return new SQLErrorException(*this); }

  QString text() const {
    return QString("This error happened: %1; when executing this query: %2")
        .arg(sqlError.text(), query);
  }
};

class QVariantConvertException : public persistence::Exception {
public:
    QVariant variant;
    QString wantedTypeName;

    explicit QVariantConvertException(const QVariant &variant, const QString &wantedTypeName) : variant(variant), wantedTypeName(wantedTypeName) {}

    void raise() const { throw *this; }

    QVariantConvertException * clone() const { return new QVariantConvertException(variant, wantedTypeName); }

    QString text() const {
      return QString("Can't convert a QVariant of type %1 to %2.").arg(variant.typeName(), wantedTypeName);
    }
};

void prepareQuery(QSqlQuery &query, const QString &sql);
void execQuery(QSqlQuery &query);

} // namespace SQLite
} // namespace persistence
#endif

#ifndef PERSISTENCE_SQLITE_DAO_HPP
#define PERSISTENCE_SQLITE_DAO_HPP

#include "../DAO.hpp"
#include "../Tables.hpp"
#include "Exceptions.hpp"

#include <QDateTime>
#include <QDebug>
#include <QMap>
#include <QtSql/QSqlQuery>

namespace persistence {
namespace SQLite {

enum ColumnType { Integer, String, DateTime, Boolean };

struct ColumnInfo {
  QString name;
  ColumnType type;
};

struct TableInfo {
  QString name;
  QMap<QString, ColumnInfo> columns;
};

template <typename T> class DAO : public persistence::DAO<T> {
public:
  QVector<T> search(const QVariantMap &where = QVariantMap());
  void save(const T &object);
  void remove(const QVariantMap &where = QVariantMap());

private:
  static const TableInfo table;

  static QVariant exportV(const QVariant &v, const ColumnType t);
  static QVariant importV(const QVariant &v, const ColumnType t);

  static QString makeWhere(const QVariantMap &v);
  static void bindValues(QSqlQuery &query, const QVariantMap &v,
                         const QString &prefix = QString());
};

void runSQLFromFile(const QString &fileName);

template <typename T>
QVariant DAO<T>::exportV(const QVariant &v, const ColumnType t) {
  switch (t) {
  case Integer:
    if (v.canConvert<int>())
      return v;
    else
      throw QVariantConvertException(v, "int");
  case String:
    if (v.canConvert<QString>())
      return v;
    else
      throw QVariantConvertException(v, "QString");
  case DateTime:
    if (v.canConvert<int>())
      return QDateTime::fromSecsSinceEpoch(v.toInt());
    else
      throw QVariantConvertException(v, "int");
  case Boolean:
    if (v.canConvert<int>())
      return v.toInt() > 0;
    else
      throw QVariantConvertException(v, "int");
  default:
    return QVariant();
  }
}

template <typename T>
QVariant DAO<T>::importV(const QVariant &v, const ColumnType t) {
  switch (t) {
  case Integer:
    if (v.canConvert<int>())
      return v;
    else
      throw QVariantConvertException(v, "int");
  case String:
    if (v.canConvert<QString>())
      return v;
    else
      throw QVariantConvertException(v, "QString");
  case DateTime:
    if (v.canConvert<QDateTime>())
      return v.toDateTime().toSecsSinceEpoch();
    else
      throw QVariantConvertException(v, "QDateTime");
  case Boolean:
    if (v.canConvert<bool>())
      return v.toBool() ? 1 : 0;
    else
      throw QVariantConvertException(v, "bool");
  default:
    return QVariant();
  }
}

template <typename T> QString DAO<T>::makeWhere(const QVariantMap &v) {
  QString query;
  if (!v.empty()) {
    query += "WHERE ";
    for (auto it = v.begin(); it != v.end();) {
      query += QString("`%1`.`%2` = :where_%3")
                   .arg(table.name, table.columns[it.key()].name, it.key());
      if (++it != v.end())
        query += " AND ";
    }
  }
  return query;
}

template <typename T>
void DAO<T>::bindValues(QSqlQuery &query, const QVariantMap &v,
                        const QString &prefix) {
  for (auto it = v.begin(); it != v.end(); ++it) {
    query.bindValue(QString(":") + prefix + it.key(),
                    importV(it.value(), table.columns[it.key()].type));
  }
}

template <typename T> QVector<T> DAO<T>::search(const QVariantMap &where) {
  QString query_str("SELECT ");
  for (auto it = table.columns.begin(); it != table.columns.end();) {
    query_str +=
        QString("`%1`.`%2` AS `%3`").arg(table.name, it.value().name, it.key());
    if (++it != table.columns.end())
      query_str += ", ";
  }
  // query_str.remove(query_str.size() - 1, 1);

  query_str += QString(" FROM `%1` ").arg(table.name);

  query_str += makeWhere(where);

    qDebug() << query_str;

  QSqlQuery query;
  prepareQuery(query, query_str);
  bindValues(query, where, "where_");
  execQuery(query);

  QVector<T> result;
  QVariantMap values;
  while (query.next()) {
    for (auto it = table.columns.begin(); it != table.columns.end(); ++it) {
      values[it.key()] = exportV(query.value(it.key()), it.value().type);
    }
    result << T(values);
  }

  return result;
}

template <typename T> void DAO<T>::save(const T &object) {
  const QVariantMap values = object.toMap();
  QString query_str = QString("INSERT OR REPLACE INTO %1 (").arg(table.name);
  QString v(" VALUES (");
  for (auto it = values.begin(); it != values.end(); ++it) {
    query_str += table.columns[it.key()].name + ',';
    v += QString(":v_%1,").arg(it.key());
  }
  query_str.back() = ')';
  v.back() = ')';
  query_str += v;

    qDebug() << query_str;

  QSqlQuery query;
  prepareQuery(query, query_str);
  bindValues(query, values, "v_");
  execQuery(query);
}

template <typename T> void DAO<T>::remove(const QVariantMap &where) {
  QString query_str = QString("DELETE FROM %1 ").arg(table.name);
  query_str += makeWhere(where);

    qDebug() << query_str;

  QSqlQuery query;
  prepareQuery(query, query_str);
  bindValues(query, where, "where_");
  execQuery(query);
}

} // namespace SQLite
} // namespace persistence
#endif

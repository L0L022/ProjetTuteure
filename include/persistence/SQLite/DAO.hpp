#ifndef PERSISTENCE_SQLITE_DAO_HPP
#define PERSISTENCE_SQLITE_DAO_HPP

#include "../DAO.hpp"
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

template <typename T> class DAO : public persistence::DAO<T> {
public:
  QVector<T> select(const QVariantMap &where);
  QVariant insert(const QVariantMap &values);
  void update(const QVariantMap &set, const QVariantMap &where);
  void remove(const QVariantMap &where);

private:
  static const QMap<QString, QString> tables;
  static const QMap<QString, QMap<QString, ColumnInfo>> columns;

  static QVariant exportV(const QVariant &v, const ColumnType t);
  static QVariant importV(const QVariant &v, const ColumnType t);
  static QString makeWhere(const QVariantMap &v);
  static void bindValues(QSqlQuery &query, const QVariantMap &v,
                         const QString &prefix = QString());
  static void prepareQuery(QSqlQuery &query, const QString &sql);
  static void execQuery(QSqlQuery &query);
};

template <typename T>
const QMap<QString, QString> DAO<T>::tables{{"form", "T_FORM_FRM"},
                                            {"question", "T_QUESTION_QST"},
                                            {"choice", "T_CHOICE_CHC"},
                                            {"subject", "T_SUBJECT_SBJ"}};

template <typename T>
const QMap<QString, QMap<QString, ColumnInfo>> DAO<T>::columns{
    {"form",
     {{"id", {"FRM_ID", Integer}},
      {"name", {"FRM_NAME", String}},
      {"description", {"FRM_DESCRIPTION", String}},
      {"creation_date", {"FRM_CREATION_DATE", DateTime}},
      {"modification_date", {"FRM_MODIFICATION_DATE", DateTime}}}},
    {"question",
     {{"id", {"QST_ID", Integer}},
      {"form", {"FRM_ID", Integer}},
      {"type", {"QST_TYPE", String}},
      {"title", {"QST_TITLE", String}},
      {"nb_words", {"QST_NBWORDS", Integer}},
      {"modification_date", {"QST_MODIFICATION_DATE", DateTime}}}},
    {"choice",
     {{"id", {"CHC_ID", Integer}},
      {"question", {"QST_ID", Integer}},
      {"label", {"CHC_LABEL", String}},
      {"modification_date", {"CHC_MODIFICATION_DATE", DateTime}}}},
    {"subject",
     {{"id", {"SBJ_ID", Integer}},
      {"form", {"FRM_ID", Integer}},
      {"is_valid", {"SBJ_ISVALID", Boolean}},
      {"modification_date", {"SBJ_MODIFICATION_DATE", DateTime}}}},
    {"opened_answer",
     {{"subject", {"SBJ_ID", Integer}},
      {"question", {"QST_ID", Integer}},
      {"words", {"SBJ_QST_WORDS", String}},
      {"modification_date", {"SBJ_QST_MODIFICATION_DATE", DateTime}}}},
    {"closed_answer",
     {{"subject", {"SBJ_ID", Integer}},
      {"choice", {"CHC_ID", Integer}},
      {"modification_date", {"SBJ_CHC_MODIFICATION_DATE", DateTime}}}}};

template <typename T>
QVariant DAO<T>::exportV(const QVariant &v, const ColumnType t) {
  switch (t) {
  case Integer:
  case String:
    return v;
  case DateTime:
    return QDateTime::fromSecsSinceEpoch(v.toInt());
  case Boolean:
    return v.toInt() > 0;
  default:
    return QVariant();
  }
}

template <typename T>
QVariant DAO<T>::importV(const QVariant &v, const ColumnType t) {
  switch (t) {
  case Integer:
  case String:
    return v;
  case DateTime:
    return v.toDateTime().toSecsSinceEpoch();
  case Boolean:
    return v.toBool() ? 1 : 0;
  default:
    return QVariant();
  }
}

template <typename T> QString DAO<T>::makeWhere(const QVariantMap &v) {
  QString query;
  if (!v.empty()) {
    query += "WHERE ";
    for (auto it = v.begin(); it != v.end(); ++it) {
      query += QString("`%1`.`%2` = :where_%3")
                   .arg(tables[T::table], columns[T::table][it.key()].name,
                        it.key());
    }
  }
  return query;
}

template <typename T>
void DAO<T>::bindValues(QSqlQuery &query, const QVariantMap &v,
                        const QString &prefix) {
  auto t_columns = columns[T::table];
  for (auto it = v.begin(); it != v.end(); ++it) {
    query.bindValue(QString(":") + prefix + it.key(),
                    importV(it.value(), t_columns[it.key()].type));
  }
}

template <typename T>
void DAO<T>::prepareQuery(QSqlQuery &query, const QString &sql) {
  if (!query.prepare(sql)) {
    throw QueryPrepareException(sql);
  }
}

template <typename T> void DAO<T>::execQuery(QSqlQuery &query) {
  query.exec();
  if (query.lastError().isValid()) {
    throw SQLErrorException(query.lastQuery(), query.lastError());
  }
}

template <typename T> QVector<T> DAO<T>::select(const QVariantMap &where) {
  QString table = T::table;
  QString real_table = tables[table];
  auto t_columns = columns[table];

  QString query_str("SELECT ");
  for (auto it = t_columns.begin(); it != t_columns.end(); ++it) {
    query_str += QString("`%1`.`%2` AS `%3`,")
                     .arg(real_table, it.value().name, it.key());
  }
  query_str.remove(query_str.size() - 1, 1);

  query_str += QString("FROM `%1`").arg(real_table);

  query_str += makeWhere(where);

  qDebug() << query_str;

  QSqlQuery query;
  prepareQuery(query, query_str);
  bindValues(query, where, "where_");
  execQuery(query);

  QVector<T> result;
  QVariantMap values;
  while (query.next()) {
    for (auto it = t_columns.begin(); it != t_columns.end(); ++it) {
      values[it.key()] = exportV(query.value(it.key()), it.value().type);
    }
    result << T(values);
  }

  return result;
}

template <typename T> QVariant DAO<T>::insert(const QVariantMap &values) {
  QString query_str = QString("INSERT INTO %1 (").arg(tables[T::table]);
  auto t_columns = columns[T::table];
  QString v(" VALUES (");
  for (auto it = values.begin(); it != values.end(); ++it) {
    query_str += t_columns[it.key()].name + ',';
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

  return query.lastInsertId();
}

template <typename T>
void DAO<T>::update(const QVariantMap &set, const QVariantMap &where) {
  auto t_columns = columns[T::table];
  QString query_str = QString("UPDATE %1 SET ").arg(tables[T::table]);
  for (auto it = set.begin(); it != set.end(); ++it) {
    query_str +=
        QString("`%1` = :set_%2,").arg(t_columns[it.key()].name, it.key());
  }
  query_str.remove(query_str.size() - 1, 1);

  query_str += makeWhere(where);

  qDebug() << query_str;

  QSqlQuery query;
  prepareQuery(query, query_str);
  bindValues(query, set, "set_");
  bindValues(query, where, "where_");
  execQuery(query);
}

template <typename T> void DAO<T>::remove(const QVariantMap &where) {
  QString query_str = QString("DELETE FROM %1 ").arg(tables[T::table]);
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

#ifndef PERSISTENCE_SQLITE_DAO_HPP
#define PERSISTENCE_SQLITE_DAO_HPP

#include "../DAO.hpp"

#include <QDateTime>
#include <QDebug>
#include <QMap>
#include <QSqlQuery>

namespace persistence {
namespace SQLite {

enum ColumnType { Integer, String, DateTime, Boolean };

struct ColumnInfo {
  QString name;
  ColumnType type;
};

template <typename T> class DAO : public persistence::DAO<T> {
public:
  QVector<T> select(const QVariantMap &);
  bool insert(const QVariantMap &);
  bool update(const QVariantMap &);
  bool remove(const QVariantMap &);

private:
  static const QMap<QString, QString> tables;
  static const QMap<QString, QMap<QString, ColumnInfo>> columns;

  static QVariant exportV(const QVariant &v, const ColumnType t);
  static QVariant importV(const QVariant &v, const ColumnType t);
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
      {"modification_date", {"FRM_MODIFICATION_DATE", DateTime}}}}};

template <typename T> QVariant exportV(const QVariant &v, const ColumnType t) {
  switch (v) {
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

template <typename T> QVariant importV(const QVariant &v, const ColumnType t) {
  switch (v) {
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

template <typename T> QVector<T> DAO<T>::select(const QVariantMap &v) {
  QString table = T::table;
  QString real_table = tables[table];
  QString query_str("SELECT ");
  auto t_columns = columns[table];
  for (auto it = t_columns.begin(); it != t_columns.end(); ++it) {
    query_str += QString("`%1`.`%2` AS `%3`,")
                     .arg(real_table, it.value().name, it.key());
  }
  query_str += QString("FROM %1") + real_table;
  if (!v.empty()) {
    query_str += "WHERE ";
    for (auto it = v.begin(); it != v.end(); ++it) {
      query_str += QString("`%1`.`%2` = :%3")
                       .arg(real_table, t_columns[it.key()].name, it.key());
    }
  }
  qDebug() << query_str;

  QSqlQuery query;
  query.prepare(query_str);
  for (auto it = v.begin(); it != v.end(); ++it) {
    query.bindValue(QString(":") + it.key(), it.value());
  }
  query.exec();

  QVector<T> result;
  QVariantMap values;
  while (query.next()) {
    for (auto it = t_columns.begin(); it != t_columns.end(); ++it) {
      values[it.key()] = exportV(query.value(it.key()), it.value().type);
    }
    qDebug() << values;
    // remplir result
  }

  return result;
}

template <typename T> bool DAO<T>::insert(const QVariantMap &v) {
  return false;
}

template <typename T> bool DAO<T>::update(const QVariantMap &v) {
  return false;
}

template <typename T> bool DAO<T>::remove(const QVariantMap &v) {
  return false;
}

} // namespace SQLite
} // namespace persistence
#endif

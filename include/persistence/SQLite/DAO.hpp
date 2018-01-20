#ifndef PERSISTENCE_SQLITE_DAO_HPP
#define PERSISTENCE_SQLITE_DAO_HPP

#include "../DAO.hpp"

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

template <typename T> QVector<T> DAO<T>::select(const QVariantMap &v) {
  QString table = T::table;
  QString real_table = tables[table];
  QString query_str("SELECT ");
  auto t_columns = columns[table];

  for (auto it = t_columns.begin(); it != t_columns.end(); ++it) {
    query_str += QString("`%1`.`%2` AS `%3`,")
                     .arg(real_table, it.value().name, it.key());
  }
  query_str.remove(query_str.size() - 1, 1);

  query_str += QString("FROM `%1`").arg(real_table);

  if (!v.empty()) {
    query_str += "WHERE ";
    for (auto it = v.begin(); it != v.end(); ++it) {
      query_str += QString("`%1`.`%2` = :%3")
                       .arg(real_table, t_columns[it.key()].name, it.key());
    }
  }

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
    result << T(values);
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

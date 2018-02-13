#include <persistence/SQLite/DAO.hpp>

#include <QFile>

using namespace persistence::SQLite;

template <>
const TableInfo DAO<persistence::Form>::table{
    "T_FORM_FRM",
    {{"id", {"FRM_ID", Integer}},
     {"name", {"FRM_NAME", String}},
     {"description", {"FRM_DESCRIPTION", String}},
     {"creation_date", {"FRM_CREATION_DATE", DateTime}},
     {"modification_date", {"FRM_MODIFICATION_DATE", DateTime}}}};

template <>
const TableInfo DAO<persistence::Question>::table{
    "T_QUESTION_QST",
    {{"id", {"QST_ID", Integer}},
     {"form", {"FRM_ID", Integer}},
     {"type", {"QST_TYPE", String}},
     {"title", {"QST_TITLE", String}},
     {"nb_words", {"QST_NBWORDS", Integer}},
     {"modification_date", {"QST_MODIFICATION_DATE", DateTime}}}};

template <>
const TableInfo DAO<persistence::Choice>::table{
    "T_CHOICE_CHC",
    {{"id", {"CHC_ID", Integer}},
     {"question", {"QST_ID", Integer}},
     {"label", {"CHC_LABEL", String}},
     {"modification_date", {"CHC_MODIFICATION_DATE", DateTime}}}};

template <>
const TableInfo DAO<persistence::Subject>::table{
    "T_SUBJECT_SBJ",
    {{"id", {"SBJ_ID", Integer}},
     {"form", {"FRM_ID", Integer}},
     {"is_valid", {"SBJ_ISVALID", Boolean}},
     {"modification_date", {"SBJ_MODIFICATION_DATE", DateTime}}}};

template <>
const TableInfo DAO<persistence::OpenedAnswer>::table{
    "TJ_SBJ_QST",
    {{"subject", {"SBJ_ID", Integer}},
     {"question", {"QST_ID", Integer}},
     {"words", {"SBJ_QST_WORDS", String}},
     {"modification_date", {"SBJ_QST_MODIFICATION_DATE", DateTime}}}};

template <>
const TableInfo DAO<persistence::ClosedAnswer>::table{
    "TJ_SBJ_CHC",
    {{"subject", {"SBJ_ID", Integer}},
     {"choice", {"CHC_ID", Integer}},
     {"modification_date", {"SBJ_CHC_MODIFICATION_DATE", DateTime}}}};

void persistence::SQLite::runSQLFromFile(const QString &fileName) {
  QFile file(fileName);

  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    qDebug() << " Could not open the file for reading";
    return;
  }

  QString commands = file.readAll();

  for (const QString &command : commands.split(';', QString::SkipEmptyParts)) {
      if (!command.simplified().isEmpty()) {
        QSqlQuery query;
        prepareQuery(query, command);
        execQuery(query);
      }
  }
}

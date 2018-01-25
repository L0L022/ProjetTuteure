#include <persistence/SQLite/DAO.hpp>

using namespace persistence::SQLite;

template <>
const TableInfo DAO<persistence::Form>::table{
    "T_FORM_FRM",
    "CREATE TABLE IF NOT EXISTS T_FORM_FRM("
    "FRM_ID INTEGER PRIMARY KEY NOT NULL,"
    "FRM_NAME TEXT NOT NULL,"
    "FRM_DESCRIPTION TEXT NOT NULL,"
    "FRM_CREATION_DATE INTEGER NOT NULL,"
    "FRM_MODIFICATION_DATE INTEGER NOT NULL"
    ");",
    {{"id", {"FRM_ID", Integer}},
     {"name", {"FRM_NAME", String}},
     {"description", {"FRM_DESCRIPTION", String}},
     {"creation_date", {"FRM_CREATION_DATE", DateTime}},
     {"modification_date", {"FRM_MODIFICATION_DATE", DateTime}}}};

template <>
const TableInfo DAO<persistence::Question>::table{
    "T_QUESTION_QST",
    "CREATE TABLE IF NOT EXISTS T_QUESTION_QST("
    "QST_ID INTEGER PRIMARY KEY NOT NULL,"
    "FRM_ID INTEGER NOT NULL,"
    "QST_TYPE TEXT NOT NULL,"
    "QST_TITLE TEXT NOT NULL,"
    "QST_NBWORDS INTEGER NOT NULL,"
    "QST_MODIFICATION_DATE INTEGER NOT NULL,"
    "FOREIGN KEY (FRM_ID) REFERENCES T_FORM_FRM(FRM_ID)"
    ");",
    {{"id", {"QST_ID", Integer}},
     {"form", {"FRM_ID", Integer}},
     {"type", {"QST_TYPE", String}},
     {"title", {"QST_TITLE", String}},
     {"nb_words", {"QST_NBWORDS", Integer}},
     {"modification_date", {"QST_MODIFICATION_DATE", DateTime}}}};

template <>
const TableInfo DAO<persistence::Choice>::table{
    "T_CHOICE_CHC",
    "CREATE TABLE IF NOT EXISTS T_CHOICE_CHC("
    "CHC_ID INTEGER PRIMARY KEY NOT NULL,"
    "QST_ID INTEGER NOT NULL,"
    "CHC_MODIFICATION_DATE INTEGER NOT NULL,"
    "CHC_LABEL TEXT NOT NULL,"
    "FOREIGN KEY (QST_ID) REFERENCES T_QUESTION_QST(QST_ID)"
    ");",
    {{"id", {"CHC_ID", Integer}},
     {"question", {"QST_ID", Integer}},
     {"label", {"CHC_LABEL", String}},
     {"modification_date", {"CHC_MODIFICATION_DATE", DateTime}}}};

template <>
const TableInfo DAO<persistence::Subject>::table{
    "T_SUBJECT_SBJ",
    "CREATE TABLE IF NOT EXISTS T_SUBJECT_SBJ("
    "SBJ_ID INTEGER PRIMARY KEY NOT NULL,"
    "FRM_ID INTEGER NOT NULL,"
    "SBJ_MODIFICATION_DATE INTEGER NOT NULL,"
    "SBJ_ISVALID INTEGER NOT NULL,"
    "FOREIGN KEY (FRM_ID) REFERENCES T_FORM_FRM(FRM_ID)"
    ");",
    {{"id", {"SBJ_ID", Integer}},
     {"form", {"FRM_ID", Integer}},
     {"is_valid", {"SBJ_ISVALID", Boolean}},
     {"modification_date", {"SBJ_MODIFICATION_DATE", DateTime}}}};

template <>
const TableInfo DAO<persistence::OpenedAnswer>::table{
    "TJ_SBJ_QST",
    "CREATE TABLE IF NOT EXISTS TJ_SBJ_QST("
    "SBJ_ID INTEGER NOT NULL,"
    "QST_ID INTEGER NOT NULL,"
    "SBJ_QST_MODIFICATION_DATE INTEGER NOT NULL,"
    "SBJ_QST_WORDS TEXT NOT NULL,"
    "FOREIGN KEY (SBJ_ID) REFERENCES T_SUBJECT_SBJ(SBJ_ID),"
    "FOREIGN KEY (QST_ID) REFERENCES T_QUESTION_QST(QST_ID)"
    ");",
    {{"subject", {"SBJ_ID", Integer}},
     {"question", {"QST_ID", Integer}},
     {"words", {"SBJ_QST_WORDS", String}},
     {"modification_date", {"SBJ_QST_MODIFICATION_DATE", DateTime}}}};

template <>
const TableInfo DAO<persistence::ClosedAnswer>::table{
    "TJ_SBJ_CHC",
    "CREATE TABLE IF NOT EXISTS TJ_SBJ_CHC("
    "SBJ_ID INTEGER NOT NULL,"
    "CHC_ID INTEGER NOT NULL,"
    "SBJ_CHC_MODIFICATION_DATE INTEGER NOT NULL,"
    "FOREIGN KEY (SBJ_ID) REFERENCES T_SUBJECT_SBJ(SBJ_ID),"
    "FOREIGN KEY (CHC_ID) REFERENCES T_CHOICE_CHC(CHC_ID)"
    ");",
    {{"subject", {"SBJ_ID", Integer}},
     {"choice", {"CHC_ID", Integer}},
     {"modification_date", {"SBJ_CHC_MODIFICATION_DATE", DateTime}}}};

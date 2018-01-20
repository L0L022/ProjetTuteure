#include <persistence/Tables.hpp>

using namespace persistence;

const QString Form::table = "form";
const QStringList Form::columns = {"id", "name", "description", "creation_date",
                                   "modification_date"};

const QString Question::table = "quesiton";
const QStringList Question::columns = {"id",   "id_form", "title",
                                       "type", "nbWords", "modification_date"};

const QString Choice::table = "choice";
const QStringList Choice::columns = {"id", "id_question", "label",
                                     "modification_date"};

const QString Subject::table = "subject";
const QStringList Subject::columns = {"id", "id_form", "isValid",
                                      "modification_date"};

const QString Answer::table = "answer";
const QStringList Answer::columns = {"id_subject", "id_question", "words",
                                     "modification_date"};

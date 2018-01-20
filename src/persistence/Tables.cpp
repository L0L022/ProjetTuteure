#include <persistence/Tables.hpp>

using namespace persistence;

const QString Form::table = "form";
const QStringList Form::columns = {"id", "name", "description", "creation_date",
                                   "modification_date"};

Form::Form(const QVariantMap &v) {
  id = v["id"].toInt();
  name = v["name"].toString();
  description = v["description"].toString();
  creation_date = v["creation_date"].toDateTime();
  modification_date = v["modification_date"].toDateTime();
}

const QString Question::table = "quesiton";
const QStringList Question::columns = {"id",   "form",     "title",
                                       "type", "nb_words", "modification_date"};

Question::Question(const QVariantMap &v) {
  id = v["id"].toInt();
  form = v["form"].toInt();
  title = v["title"].toString();
  type = v["type"].toString();
  nb_words = v["nb_words"].toInt();
  modification_date = v["modification_date"].toDateTime();
}

const QString Choice::table = "choice";
const QStringList Choice::columns = {"id", "question", "label",
                                     "modification_date"};

Choice::Choice(const QVariantMap &v) {
  id = v["id"].toInt();
  question = v["question"].toInt();
  label = v["label"].toString();
  modification_date = v["modification_date"].toDateTime();
}

const QString Subject::table = "subject";
const QStringList Subject::columns = {"id", "form", "is_valid",
                                      "modification_date"};

Subject::Subject(const QVariantMap &v) {
  id = v["id"].toInt();
  form = v["form"].toInt();
  is_valid = v["is_valid"].toBool();
  modification_date = v["modification_date"].toDateTime();
}

const QString OpenedAnswer::table = "opened_answer";
const QStringList OpenedAnswer::columns = {"subject", "question", "words",
                                           "modification_date"};

OpenedAnswer::OpenedAnswer(const QVariantMap &v) {
  subject = v["subject"].toInt();
  question = v["question"].toInt();
  words = v["words"].toString();
  modification_date = v["modification_date"].toDateTime();
}

const QString ClosedAnswer::table = "closed_answer";
const QStringList ClosedAnswer::columns = {"subject", "choice",
                                           "modification_date"};

ClosedAnswer::ClosedAnswer(const QVariantMap &v) {
  subject = v["subject"].toInt();
  choice = v["choice"].toInt();
  modification_date = v["modification_date"].toDateTime();
}

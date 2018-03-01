#include <persistence/Tables.hpp>

namespace persistence {

Form::Form(const QVariantMap &v) {
  id = v["id"].toInt();
  name = v["name"].toString();
  description = v["description"].toString();
  creation_date = v["creation_date"].toDateTime();
  modification_date = v["modification_date"].toDateTime();
}

QVariantMap Form::toMap() const {
  return {{"id", id},
          {"name", name},
          {"description", description},
          {"creation_date", creation_date},
          {"modification_date", modification_date}};
}

Question::Question(const QVariantMap &v) {
  id = v["id"].toInt();
  form = v["form"].toInt();
  title = v["title"].toString();
  type = v["type"].toString();
  nb_words = v["nb_words"].toInt();
  modification_date = v["modification_date"].toDateTime();
}

QVariantMap Question::toMap() const {
  return {{"id", id},
          {"form", form},
          {"title", title},
          {"type", type},
          {"nb_words", nb_words},
          {"modification_date", modification_date}};
}

Choice::Choice(const QVariantMap &v) {
  id = v["id"].toInt();
  question = v["question"].toInt();
  label = v["label"].toString();
  modification_date = v["modification_date"].toDateTime();
}

QVariantMap Choice::toMap() const {
  return {{"id", id},
          {"question", question},
          {"label", label},
          {"modification_date", modification_date}};
}

Subject::Subject(const QVariantMap &v) {
  id = v["id"].toInt();
  form = v["form"].toInt();
  is_valid = v["is_valid"].toBool();
  modification_date = v["modification_date"].toDateTime();
}

QVariantMap Subject::toMap() const {
  return {{"id", id},
          {"form", form},
          {"is_valid", is_valid},
          {"modification_date", modification_date}};
}

OpenedAnswer::OpenedAnswer(const QVariantMap &v) {
  subject = v["subject"].toInt();
  question = v["question"].toInt();
  words = v["words"].toString();
  modification_date = v["modification_date"].toDateTime();
}

QVariantMap OpenedAnswer::toMap() const {
  return {{"subject", subject},
          {"question", question},
          {"words", words},
          {"modification_date", modification_date}};
}

ClosedAnswer::ClosedAnswer(const QVariantMap &v) {
  subject = v["subject"].toInt();
  choice = v["choice"].toInt();
  modification_date = v["modification_date"].toDateTime();
}

QVariantMap ClosedAnswer::toMap() const {
  return {{"subject", subject},
          {"choice", choice},
          {"modification_date", modification_date}};
}

}

#ifndef SEMANTICS_CORE_QUESTION_HPP
#define SEMANTICS_CORE_QUESTION_HPP

#include "Data.hpp"

#include <QString>

class Question : public Data {
public:
  inline QString &title() const { return _title; }
  void setTitle(const QString &title);

private:
  QString _title;
};

#endif

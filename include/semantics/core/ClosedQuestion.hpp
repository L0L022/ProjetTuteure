#ifndef SEMANTICS_CORE_CLOSEDQUESTION_HPP
#define SEMANTICS_CORE_CLOSEDQUESTION_HPP

#include "Choice.hpp"
#include "Question.hpp"

#include <QMap>

class ClosedQuestion : public Question {
public:
  enum Type { Unique, Multiple };

  inline Type type() const { return _type; }
  void setType(const Type type);

  inline const QMap<int, Choice> &choices() const { return _choices; }
  void setChoices(const QMap<int, Choice> &choices);

private:
  Type _type;
  QMap<int, Choice> _choices;
};

#endif

#ifndef SEMANTICS_CORE_CLOSEDANSWER_HPP
#define SEMANTICS_CORE_CLOSEDANSWER_HPP

#include "Answer.hpp"

#include <QVector>

class ClosedAnswer : public Answer {
public:
private:
  QVector<int> _choices;
};

#endif

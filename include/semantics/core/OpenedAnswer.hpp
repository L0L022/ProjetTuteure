#ifndef SEMANTICS_CORE_OPENEDANSWER_HPP
#define SEMANTICS_CORE_OPENEDANSWER_HPP

#include "Answer.hpp"

#include <QString>
#include <QVector>

class OpenedAnswer : public Answer {
public:
  inline const QVector<QString> &words() const { return _words; }
  void setWords(const QVector<QString> &words);

private:
  QVector<QString> _words;
};

#endif

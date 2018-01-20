#ifndef SEMANTICS_CORE_OPENEDQUESTION_HPP
#define SEMANTICS_CORE_OPENEDQUESTION_HPP

#include "Question.hpp"

class OpenedQuestion : public Question {
public:
  inline size_t nbWords() const { return _nbWords; }
  void setNbWords(const size_t nbWords);

private:
  size_t _nbWords;
};

#endif

#ifndef SEMANTICS_CORE_SUBJECT_HPP
#define SEMANTICS_CORE_SUBJECT_HPP

#include "Data.hpp"

#include <QString>

class Subject : public Data {
public:
  bool isValid() const { return _isValid; }
  void setIsValid(const bool isValid);

private:
  bool _isValid;
};

#endif

#ifndef SEMANTICS_CORE_CHOICE_HPP
#define SEMANTICS_CORE_CHOICE_HPP

#include "Data.hpp"

#include <QString>

class Choice : public Data {
public:
  inline const QString &label() const { return _label; }
  void setLabel(const QString &label);

private:
  QString _label;
};

#endif

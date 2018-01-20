#include <semantics/core/Choice.hpp>

void Choice::setLabel(const QString &label) {
  if (_label != label) {
    _label = label;
    update_modification();
  }
}

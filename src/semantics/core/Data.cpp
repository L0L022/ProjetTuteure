#include <semantics/core/Data.hpp>

Data::Data(const int id, const QDateTime &modification_date)
    : _id(id), _modification_date(modification_date) {}

void Data::update_modification() {
  _modification_date = QDateTime::currentDateTime();
}

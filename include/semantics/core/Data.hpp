#ifndef SEMANTICS_CORE_DATA_HPP
#define SEMANTICS_CORE_DATA_HPP

#include <QDateTime>

#define DATA_PROPERTY(type, name) inline ##type ##name() const { return _##name; } void set_##name(const ##type &v) { if (v != _##name) {_##name = v;update_modification();}}

class Data {
public:
  Data(const int id,
       const QDateTime &modification_date = QDateTime::currentDateTime());

  inline int id() const { return _id; }
  inline const QDateTime &modification_date() const {
    return _modification_date;
  }

protected:
  void update_modification();

private:
  const int _id;
  QDateTime _modification_date;
};

#endif

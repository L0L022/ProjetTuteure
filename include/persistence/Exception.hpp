#ifndef PERSISTENCE_EXCEPTION_HPP
#define PERSISTENCE_EXCEPTION_HPP

#include <QException>
#include <QString>

namespace persistence {

class Exception : public QException {
public:
  virtual QString text() const = 0;
  virtual const char * what() const noexcept { return text().toLocal8Bit().constData(); }
};

} // namespace persistence
#endif

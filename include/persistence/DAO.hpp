#ifndef PERSISTENCE_DAO_HPP
#define PERSISTENCE_DAO_HPP

#include <QVariant>
#include <QVector>

namespace persistence {

template <typename T> class DAO {
public:
  virtual QVector<T> search(const QVariantMap &where = QVariantMap()) = 0;
  virtual void save(const T &object) = 0;
  virtual void remove(const QVariantMap &where = QVariantMap()) = 0;
};

} // namespace persistence
#endif

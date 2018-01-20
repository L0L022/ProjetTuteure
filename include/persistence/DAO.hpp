#ifndef PERSISTENCE_DAO_HPP
#define PERSISTENCE_DAO_HPP

#include <QVariant>
#include <QVector>

namespace persistence {

template <typename T> class DAO {
public:
  virtual QVector<T> select(const QVariantMap &) = 0;
  virtual bool insert(const QVariantMap &) = 0;
  virtual bool update(const QVariantMap &) = 0;
  virtual bool remove(const QVariantMap &) = 0;
};

} // namespace persistence
#endif

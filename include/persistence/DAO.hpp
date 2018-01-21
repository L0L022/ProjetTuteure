#ifndef PERSISTENCE_DAO_HPP
#define PERSISTENCE_DAO_HPP

#include <QVariant>
#include <QVector>

namespace persistence {

template <typename T> class DAO {
public:
  virtual QVector<T> select(const QVariantMap &where) = 0;
  virtual QVariant insert(const QVariantMap &values) = 0;
  virtual void update(const QVariantMap &set, const QVariantMap &where) = 0;
  virtual void remove(const QVariantMap &where) = 0;
};

} // namespace persistence
#endif

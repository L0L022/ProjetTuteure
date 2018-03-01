#ifndef SEMANTICS_CORE_SERVICES_HPP
#define SEMANTICS_CORE_SERVICES_HPP

#include <functional>

#include <QObject>
#include <QVariant>
namespace semantics {
namespace core {

class Services : public QObject {
  Q_OBJECT
public:
  typedef std::function<QVariantMap(QVariantMap)> Function;

  explicit Services(QObject *parent = nullptr);

  Q_INVOKABLE QVariantMap run(const QString &id, const QVariantMap &args);

  // Q_INVOKABLE QList<QString> functions() const { return _functions.keys(); }
  Q_INVOKABLE QVariantList functions() const {
    return QVariant::fromValue(QStringList(_functions.keys())).toList();
  }
  Q_INVOKABLE bool hasFunction(const QString &id) const {
    return _functions.contains(id);
  }

protected:
  void insertFunction(const QString &id, const Function &f);
  void removeFunction(const QString &id);

private:
  QHash<QString, Function> _functions;
};
}
}

#endif

#ifndef SERVICES_HPP
#define SERVICES_HPP

#include <QObject>
#include <QVariant>

class Services : public QObject {

    Q_OBJECT
public:

  explicit Services(QObject *parent = nullptr);

  Q_INVOKABLE QVariantMap sendCommand(const QString& id, const QVariantMap& args);
};

#endif

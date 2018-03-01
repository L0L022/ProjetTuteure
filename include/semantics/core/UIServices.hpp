#ifndef SEMANTICS_CORE_UISERVICES_HPP
#define SEMANTICS_CORE_UISERVICES_HPP

#include <semantics/core/Services.hpp>
#include <semantics/core/DataServices.hpp>

namespace semantics {
namespace core {

class UIServices : public Services {
  Q_OBJECT
public:
  UIServices(QObject *parent = nullptr);

private:
  void registerData();

  DataServices _dataServices;
};
}
}
#endif

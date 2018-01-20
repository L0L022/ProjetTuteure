#ifndef SEMANTICS_CORE_UISERVICES_HPP
#define SEMANTICS_CORE_UISERVICES_HPP

#include "Services.hpp"
#include "Data.hpp"

class UIServices : public Services {
  Q_OBJECT
public:
  UIServices(QObject *parent = nullptr);
};

#endif

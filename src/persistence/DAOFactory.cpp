#include <persistence/DAOFactory.hpp>

#include <persistence/SQLite/DAOFactory.hpp>

using namespace persistence;

DAOFactory *DAOFactory::make(const Drivers d) {
  switch (d) {
  case DAOFactory::SQLite:
    return new SQLite::DAOFactory();
  default:
    return nullptr;
  }
}

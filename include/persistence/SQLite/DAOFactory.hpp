#ifndef PERSISTENCE_SQLITE_DAOFACTORY_HPP
#define PERSISTENCE_SQLITE_DAOFACTORY_HPP

#include "../DAOFactory.hpp"
#include "DAO.hpp"

namespace persistence {
namespace SQLite {

class DAOFactory : public persistence::DAOFactory {
public:
  DAOFactory(const QString &name = ":memory:");
  ~DAOFactory();

  persistence::DAO<Form> *form();
  persistence::DAO<Question> *question();
  persistence::DAO<Choice> *choice();
  persistence::DAO<Subject> *subject();
  persistence::DAO<OpenedAnswer> *openedAnswer();
  persistence::DAO<ClosedAnswer> *closedAnswer();
};

} // namespace SQLite
} // namespace persistence

#endif
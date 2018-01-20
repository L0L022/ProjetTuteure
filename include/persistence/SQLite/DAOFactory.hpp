#ifndef PERSISTENCE_SQLITE_DAOFACTORY_HPP
#define PERSISTENCE_SQLITE_DAOFACTORY_HPP

#include "../DAOFactory.hpp"
#include "DAO.hpp"

namespace persistence {
namespace SQLite {

class DAOFactory : public persistence::DAOFactory {
public:
  DAOFactory();

  persistence::DAO<Form> *form();
  persistence::DAO<Question> *question();
  persistence::DAO<Choice> *choice();
  persistence::DAO<Subject> *subject();
  persistence::DAO<Answer> *answer();
};

} // namespace SQLite
} // namespace persistence

#endif

#ifndef PERSISTENCE_DAOFACTORY_HPP
#define PERSISTENCE_DAOFACTORY_HPP

#include "DAO.hpp"
#include "Tables.hpp"

namespace persistence {

class DAOFactory {
public:
  enum Drivers { SQLite };

  DAOFactory() = default;

  static DAOFactory *make(const Drivers d);

  virtual DAO<Form> *form() = 0;
  virtual DAO<Question> *question() = 0;
  virtual DAO<Choice> *choice() = 0;
  virtual DAO<Subject> *subject() = 0;
  virtual DAO<Answer> *answer() = 0;
};

} // namespace persistence
#endif

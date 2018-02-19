#ifndef SEMANTICS_CORE_DATATESTS_HPP
#define SEMANTICS_CORE_DATATESTS_HPP

#include <QtTest/QtTest>

namespace semantics {
namespace core {

class DataTests : public QObject {
  Q_OBJECT

public:
  DataTests(QObject *parent = nullptr);

private slots:
  void initTestCase();
  void init();
  void cleanup();

  void create_form();
};

} // namespace core
} // namespace semantics

#endif

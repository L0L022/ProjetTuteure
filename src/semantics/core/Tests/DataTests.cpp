#include <semantics/core/Tests/DataTests.hpp>

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>

using namespace semantics::core;

DataTests::DataTests(QObject *parent) : QObject(parent) {}

void DataTests::initTestCase() {}

void DataTests::init() {}

void DataTests::cleanup() {}

void DataTests::toAndFromMap() {
  std::unique_ptr<Form> f_origin = create_form();
  std::unique_ptr<Form> f_copy(Form::fromMap(f_origin->toMap()));
  QCOMPARE(*f_origin, *f_copy);
}

std::unique_ptr<Form> DataTests::create_form() {
  ClosedQuestion::Choices::SharedDataPtr choicesSharedData =
      std::make_shared<ClosedQuestion::Choices::SharedData>();
  Form::Questions::SharedDataPtr questionsSharedData =
      std::make_shared<Form::Questions::SharedData>();
  Form::Subjects::SharedDataPtr subjectsSharedData =
      std::make_shared<Form::Subjects::SharedData>();

  Form::Questions questions;

  for (size_t i = 0; i < 5; ++i) {
    auto q = std::make_unique<OpenedQuestion>(questionsSharedData->takeId());
    q->setTitle(QString("Opened question n %1").arg(q->id()));
    q->setNbWords(10);
    questions.insert(std::move(q));
  }

  for (size_t i = 0; i < 3; ++i) {
    ClosedQuestion::Choices choices;
    for (size_t i = 0; i < 5; ++i) {
      auto c = std::make_unique<Choice>(choicesSharedData->takeId());
      c->setLabel(QString("Choice %1").arg(c->id()));
      choices.insert(std::move(c));
    }
    {
      auto q = std::make_unique<ClosedQuestion>(ClosedQuestion::Unique,
                                                questionsSharedData->takeId(),
                                                choicesSharedData);
      q->setTitle(QString("Unique closed question n %1").arg(q->id()));
      q->setChoices(choices);
      questions.insert(std::move(q));
    }
    {
      auto q = std::make_unique<ClosedQuestion>(ClosedQuestion::Multiple,
                                                questionsSharedData->takeId(),
                                                choicesSharedData);
      q->setTitle(QString("Multiple closed question n %1").arg(q->id()));
      q->setChoices(choices);
      questions.insert(std::move(q));
    }
  }

  // IdDataMap<Form> forms;
  auto form =
      std::make_unique<Form>(1, questionsSharedData, subjectsSharedData);
  // std::unique_ptr<Form> form(new Form(forms.takeId(), questionsSharedData,
  // subjectsSharedData));
  form->setName("Name");
  form->setDescription("Description");
  form->setQuestions(questions);
  // std::cout <<
  // QJsonDocument::fromVariant(form->toMap()).toJson().toStdString();
  // forms.insert(std::move(form));

  return form;
}

QTEST_MAIN(DataTests)

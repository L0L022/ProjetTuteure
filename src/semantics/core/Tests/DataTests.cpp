#include <semantics/core/Tests/DataTests.hpp>

#include <semantics/core/Data.hpp>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>

#include <memory>

using namespace semantics::core;

DataTests::DataTests(QObject *parent) : QObject(parent)
{

}

void DataTests::initTestCase()
{

}

void DataTests::init()
{

}

void DataTests::cleanup()
{

}

void DataTests::create_form()
{
    Form::Questions questions;

    ClosedQuestion::Choices::SharedDataPtr choicesSharedData = std::make_shared<ClosedQuestion::Choices::SharedData>();
    Form::Questions::SharedDataPtr questionsSharedData = std::make_shared<Form::Questions::SharedData>();
    Form::Subjects::SharedDataPtr subjectsSharedData = std::make_shared<Form::Subjects::SharedData>();

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
            auto q = std::make_unique<ClosedQuestion>(ClosedQuestion::Unique, questionsSharedData->takeId(), choicesSharedData);
            q->setTitle(QString("Unique closed question n %1").arg(q->id()));
            q->setChoices(choices);
            questions.insert(std::move(q));
        }
        {
            auto q = std::make_unique<ClosedQuestion>(ClosedQuestion::Multiple, questionsSharedData->takeId(), choicesSharedData);
            q->setTitle(QString("Multiple closed question n %1").arg(q->id()));
            q->setChoices(choices);
            questions.insert(std::move(q));
        }
    }

    IdDataMap<Form> forms;
    std::unique_ptr<Form> form(new Form(forms.takeId(), questionsSharedData, subjectsSharedData));
    form->setQuestions(questions);
    //std::cout << QJsonDocument::fromVariant(form->toMap()).toJson().toStdString();
    forms.insert(std::move(form));
}

QTEST_MAIN(DataTests)

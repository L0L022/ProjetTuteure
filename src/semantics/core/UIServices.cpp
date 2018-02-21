#include <semantics/core/UIServices.hpp>
#include <QDebug>
#include <QThread>

UIServices::UIServices(QObject *parent) : Services(parent) {
    registerData();
}

void UIServices::registerData() {
    insertFunction(QStringLiteral("listForms"), [](const QVariantMap &args) -> QVariantMap {
        Q_UNUSED(args)
        QVariantList forms;
        for (int i = 0; i < 10; ++i) {
            QVariantMap form;
            form["id"] = i;
            form["name"] = "Name";
            form["description"] = "Description";
            forms.push_back(form);
        }
        QVariantMap r;
        r["forms"] = forms;
        return r;
    });
    insertFunction(QStringLiteral("listSubjects"), [](const QVariantMap &args) -> QVariantMap {
        Q_UNUSED(args)
        QVariantList subjects;
        for (int i = 0; i < 10; ++i) {
            QVariantMap subject;
            subject["id"] = i;
            subject["isValid"] = false;
            subjects.push_back(subject);
        }
        QVariantMap r;
        r["subjects"] = subjects;
        return r;
    });
    insertFunction(QStringLiteral("getForm"), [](const QVariantMap &args) -> QVariantMap {
        QVariantMap opened_q;
        opened_q["id"] = 1;
        opened_q["title"] = "Une question ouverte";
        opened_q["type"] = "opened";
        opened_q["nbAnswers"] = 10;

        QVariantMap choice_1;
        choice_1["id"] = 0;
        choice_1["label"] = "Choix 1";

        QVariantMap choice_2;
        choice_2["id"] = 1;
        choice_2["label"] = "Choix 2";

        QVariantMap choice_3;
        choice_3["id"] = 2;
        choice_3["label"] = "Choix 3";

        QVariantList choices = {choice_1, choice_2, choice_3};

        QVariantMap unique_q;
        unique_q["id"] = 2;
        unique_q["title"] = "Une question unique";
        unique_q["type"] = "unique";
        unique_q["choices"] = choices;

        QVariantMap multiple_q;
        multiple_q["id"] = 3;
        multiple_q["title"] = "Une question multiple";
        multiple_q["type"] = "multiple";
        multiple_q["choices"] = choices;

        QVariantMap questions;
        questions[QString::number(opened_q["id"].toInt())] = opened_q;
        questions[QString::number(unique_q["id"].toInt())] = unique_q;
        questions[QString::number(multiple_q["id"].toInt())] = multiple_q;

        QVariantMap form;
        form["id"] = args["id"].toInt();
        form["name"] = "Name";
        form["description"] = "Description";
        form["questions"] = questions;

        return form;
    });
    insertFunction(QStringLiteral("getSubject"), [](const QVariantMap &args) -> QVariantMap {
        QVariantMap answer_1;
        answer_1["id"] = 0;
        answer_1["words"] = "une liste de  mots";

        QVariantMap answer_2;
        answer_2["id"] = 1;
        answer_2["choice"] = 2;

        QVariantMap answer_3;
        answer_3["id"] = 2;
        answer_3["choices"] = QVariantList() << 0 << 2;

        QVariantMap answers;
        answers[QString::number(answer_1["id"].toInt())] = answer_1;
        answers[QString::number(answer_2["id"].toInt())] = answer_2;
        answers[QString::number(answer_3["id"].toInt())] = answer_3;

        QVariantMap subject;
        subject["id"] = args["id"];
        subject["isValid"] = false;
        subject["answers"] = answers;

        return subject;
    });
    insertFunction(QStringLiteral("saveForm"), [](const QVariantMap &args) -> QVariantMap {
        qDebug() << "saveForm: " << args["form"];
        QThread::sleep(4);
        return QVariantMap();
    });
    insertFunction(QStringLiteral("saveSubject"), [](const QVariantMap &args) -> QVariantMap {
        qDebug() << "saveSubject: " << args["subject"];
        return QVariantMap();
    });
    insertFunction(QStringLiteral("deleteForm"), [](const QVariantMap &args) -> QVariantMap {
        qDebug() << "deleteForm: " << args["id"];
        return QVariantMap();
    });
    insertFunction(QStringLiteral("deleteSubject"), [](const QVariantMap &args) -> QVariantMap {
        qDebug() << "deleteSubject: " << args["id"];
        return QVariantMap();
    });
}

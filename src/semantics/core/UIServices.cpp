#include <semantics/core/UIServices.hpp>
#include <QDebug>
#include <QThread>

namespace semantics {
namespace core {

UIServices::UIServices(QObject *parent) : Services(parent) {
    registerData();
}

void UIServices::registerData() {
    insertFunction(QStringLiteral("listForms"), [this](const QVariantMap &) -> QVariantMap {
        QVariantMap r;
        try {
            r["forms"] = _dataServices.listForms();
        } catch(std::exception &e) {
            r["error"] = e.what();
        }
        return r;
    });
    insertFunction(QStringLiteral("listSubjects"), [this](const QVariantMap &args) -> QVariantMap {
        QVariantMap r;
        try {
            if (args.contains("id") && args.value("id").canConvert<DataServices::Id>()) {
                r["subjects"] = _dataServices.listSubjects(args.value("id").value<DataServices::Id>());
            } else {
                r["error"] = "id is missing or is not in the right type";
            }
        } catch(std::exception &e) {
            r["error"] = e.what();
        }
        return r;
    });
    insertFunction(QStringLiteral("getForm"), [this](const QVariantMap &args) -> QVariantMap {
        QVariantMap r;
        try {
            if (args.contains("id") && args.value("id").canConvert<DataServices::Id>()) {
                r = _dataServices.getForm(args.value("id").value<DataServices::Id>());
            } else {
                r["error"] = "id is missing or is not in the right type";
            }
        } catch(std::exception &e) {
            r["error"] = e.what();
        }
        return r;
    });
    insertFunction(QStringLiteral("getSubject"), [this](const QVariantMap &args) -> QVariantMap {
        QVariantMap r;
        try {
            if (args.contains("id") && args.value("id").canConvert<DataServices::Id>()) {
                r = _dataServices.getSubject(args.value("id").value<DataServices::Id>());
            } else {
                r["error"] = "id is missing or is not in the right type";
            }
        } catch(std::exception &e) {
            r["error"] = e.what();
        }
        return r;
    });
    insertFunction(QStringLiteral("getNewSubject"), [this](const QVariantMap &args) -> QVariantMap {
        QVariantMap r;
        try {
            if (args.contains("form") && args.value("form").canConvert<DataServices::Id>()) {
                r = _dataServices.getNewSubject(args.value("form").value<DataServices::Id>());
            } else {
                r["error"] = "form is missing or is not in the right type";
            }
        } catch(std::exception &e) {
            r["error"] = e.what();
        }
        return r;
    });
    insertFunction(QStringLiteral("saveForm"), [this](const QVariantMap &args) -> QVariantMap {
        QVariantMap r;
        try {
            _dataServices.saveForm(args);
        }catch(std::exception &e) {
            r["error"] = e.what();
        }
        return r;
    });
    insertFunction(QStringLiteral("saveSubject"), [this](const QVariantMap &args) -> QVariantMap {
        QVariantMap r;
        try {
            if (args.contains("form") && args.value("form").canConvert<DataServices::Id>() && args.contains("subject") && args.value("subject").canConvert<QVariantMap>()) {
            _dataServices.saveSubject(args.value("form").value<DataServices::Id>(), args.value("subject").toMap());
            } else {
                r["error"] = "form or subject are missing or are not in the right type";
            }
        }catch(std::exception &e) {
            r["error"] = e.what();
        }
        return r;
    });
    insertFunction(QStringLiteral("deleteForm"), [this](const QVariantMap &args) -> QVariantMap {
        QVariantMap r;
        try {
            if (args.contains("id") && args.value("id").canConvert<DataServices::Id>()) {
                _dataServices.deleteForm(args.value("id").value<DataServices::Id>());
            } else {
                r["error"] = "id is missing or is not in the right type";
            }
        } catch(std::exception &e) {
            r["error"] = e.what();
        }
        return r;
    });
    insertFunction(QStringLiteral("deleteSubject"), [this](const QVariantMap &args) -> QVariantMap {
        QVariantMap r;
        try {
            if (args.contains("id") && args.value("id").canConvert<DataServices::Id>()) {
                _dataServices.deleteSubject(args.value("id").value<DataServices::Id>());
            } else {
                r["error"] = "id is missing or is not in the right type";
            }
        } catch(std::exception &e) {
            r["error"] = e.what();
        }
        return r;

    });
    insertFunction(QStringLiteral("takeFormId"), [this](const QVariantMap &) -> QVariantMap {
        QVariantMap r;
        try {
            r["id"] = _dataServices.takeFormId();
        } catch(std::exception &e) {
            r["error"] = e.what();
        }
        return r;
    });
    insertFunction(QStringLiteral("takeSubjectId"), [this](const QVariantMap &) -> QVariantMap {
        QVariantMap r;
        try {
            r["id"] = _dataServices.takeSubjectId();
        } catch(std::exception &e) {
            r["error"] = e.what();
        }
        return r;
    });
    insertFunction(QStringLiteral("takeQuestionId"), [this](const QVariantMap &) -> QVariantMap {
        QVariantMap r;
        try {
            r["id"] = _dataServices.takeQuestionId();
        } catch(std::exception &e) {
            r["error"] = e.what();
        }
        return r;
    });
    insertFunction(QStringLiteral("takeChoiceId"), [this](const QVariantMap &) -> QVariantMap {
        QVariantMap r;
        try {
            r["id"] = _dataServices.takeChoiceId();
        } catch(std::exception &e) {
            r["error"] = e.what();
        }
        return r;
    });
    insertFunction(QStringLiteral("loadData"), [this](const QVariantMap &args) -> QVariantMap {
        QVariantMap r;
        try {
            if (args.contains("uri") && args.value("uri").canConvert<QString>()) {
                _dataServices.loadData(args.value("uri").value<QString>());
            } else {
                r["error"] = "uri is missing or is not in the right type";
            }
        } catch(std::exception &e) {
            r["error"] = e.what();
        }
        return r;
    });
    insertFunction(QStringLiteral("saveData"), [this](const QVariantMap &args) -> QVariantMap {
        QVariantMap r;
        try {
            if (args.contains("uri") && args.value("uri").canConvert<QString>()) {
                _dataServices.saveData(args.value("uri").value<QString>());
            } else {
                r["error"] = "uri is missing or is not in the right type";
            }
        } catch(std::exception &e) {
            r["error"] = e.what();
        }
        return r;
    });
}

}
}

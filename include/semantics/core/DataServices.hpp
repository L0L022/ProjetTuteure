#ifndef SEMANTICS_CORE_DATASERVICES_HPP
#define SEMANTICS_CORE_DATASERVICES_HPP

#include <semantics/core/Data.hpp>
#include <persistence/Tables.hpp>
#include <persistence/DAOFactory.hpp>

namespace semantics {
namespace core {

class DataServices {
    using Forms = IdDataMap<Form>;
public:
    using Id = IdData::Id;

    DataServices();
    ~DataServices();

    void loadData(const QString &uri);
    void saveData(const QString &uri);

    QVariantMap listForms();
    QVariantMap listSubjects(const Id id);

    QVariantMap getForm(const Id id);
    QVariantMap getSubject(const Id id);

    QVariantMap getNewSubject(const Id form);

    void saveForm(const QVariantMap &form);
    void saveSubject(const Id form, const QVariantMap &subject);

    void deleteForm(const Id id);
    void deleteSubject(const Id id);

    Id takeFormId();
    Id takeSubjectId();
    Id takeQuestionId();
    Id takeChoiceId();

private:
    void resetSharedData();
    void resetDAO(const QString &uri);

private:
    Forms::SharedDataPtr _formsSharedData;
    Form::Questions::SharedDataPtr _questionsSharedData;
    ClosedQuestion::Choices::SharedDataPtr _choicesSharedData;
    Form::Subjects::SharedDataPtr _subjectsSharedData;
    std::unique_ptr<Forms> _forms;

    std::unique_ptr<persistence::DAOFactory> _factory;
    std::unique_ptr<persistence::DAO<persistence::Form>> _dao_form;
    std::unique_ptr<persistence::DAO<persistence::Question>> _dao_question;
    std::unique_ptr<persistence::DAO<persistence::Choice>> _dao_choice;
    std::unique_ptr<persistence::DAO<persistence::Subject>> _dao_subject;
    std::unique_ptr<persistence::DAO<persistence::OpenedAnswer>> _dao_openedAnswer;
    std::unique_ptr<persistence::DAO<persistence::ClosedAnswer>> _dao_closedAnswer;
};

}
}

#endif

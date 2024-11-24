#pragma once

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRecord>
#include "questionnairebankmodel.h"

namespace Ui {
class QuestionnaireManagementWidget;
}

class QuestionnaireManagementWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QuestionnaireManagementWidget(QWidget *parent = nullptr);
    ~QuestionnaireManagementWidget();
    void init();
public slots:
    void slot_questionnaire_edit();
    void slot_questionnaire_delete();
private:
    Ui::QuestionnaireManagementWidget *ui;
    QSqlTableModel *model_questionbank;
    QSqlTableModel *model_questionnaire;
    QuestionnaireBankModel *questionnaireBankModel;
private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_add_question_type1_clicked();
    void on_add_question_type2_clicked();
    void on_add_question_type3_clicked();
    void on_add_questionnaire_clicked();
    void on_finish_questionnaire_clicked();
    void on_finish_edit_clicked();
};

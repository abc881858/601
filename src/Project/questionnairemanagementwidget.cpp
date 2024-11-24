#include "questionnairemanagementwidget.h"
#include "ui_questionnairemanagementwidget.h"
#include "questionnairelistitem.h"
#include "questionlistitem.h"
#include "questiontypedialog.h"
#include "answerlistitem.h"
#include <QSqlQuery>

QuestionnaireManagementWidget::QuestionnaireManagementWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionnaireManagementWidget)
{
    ui->setupUi(this);

    ui->questionnaireListLayout->addStretch();

    ui->stackedWidget->setCurrentIndex(0);

    ui->treeWidget->expandAll();

    ui->answerListLayout->addStretch();
}

void QuestionnaireManagementWidget::init()
{
    model_questionbank = new QSqlTableModel;
    model_questionbank->setTable("questionbank");
    model_questionbank->setEditStrategy(QSqlTableModel::OnFieldChange);
    model_questionbank->select();

    questionnaireBankModel = new QuestionnaireBankModel(model_questionbank, this);
    ui->tableView_bank->setModel(questionnaireBankModel);
    ui->tableView_bank->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    QSqlQuery query("SELECT * FROM questionnaire");
    while (query.next()) {
        QString questionnaire_name = query.value(0).toString();
        int answer_number = query.value(1).toInt();

        QuestionnaireListItem *item = new QuestionnaireListItem(this);
        connect(item, &QuestionnaireListItem::signal_questionnaire_edit, this, &QuestionnaireManagementWidget::slot_questionnaire_edit);
        connect(item, &QuestionnaireListItem::signal_questionnaire_delete, this, &QuestionnaireManagementWidget::slot_questionnaire_delete);
        item->set_questionnaire_name(questionnaire_name);
        item->set_average_score(query.value("average_score").toInt());
        item->set_question_number(query.value("question_number").toInt());
        item->set_answer_number(query.value("answer_number").toInt());
        item->set_create_time(query.value("create_time").toDateTime());
        item->set_questionnaire_description(query.value("questionnaire_description").toString());
        item->set_question(query.value("question").toString());
        item->set_answer(query.value("answer").toString());
        ui->questionnaireListLayout->insertWidget(0, item);

        AnswerListItem *answerItem = new AnswerListItem(this);
        answerItem->set_questionnaire_name(questionnaire_name);
        answerItem->set_answer_number(answer_number);
        ui->answerListLayout->insertWidget(0, answerItem);
    }
}

QuestionnaireManagementWidget::~QuestionnaireManagementWidget()
{
    delete ui;
}

void QuestionnaireManagementWidget::on_pushButton_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void QuestionnaireManagementWidget::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void QuestionnaireManagementWidget::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void QuestionnaireManagementWidget::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void QuestionnaireManagementWidget::on_add_question_type1_clicked()
{
    QuestionTypeDialog dialog;
    dialog.setType(1);
    if(dialog.exec() == QDialog::Accepted)
    {
        QuestionListItem *item = new QuestionListItem(this);
        item->set_type(1);
        ui->questionListLayout->insertWidget(0, item);
    }
}

void QuestionnaireManagementWidget::on_add_question_type2_clicked()
{
    QuestionTypeDialog dialog;
    dialog.setType(2);
    if(dialog.exec() == QDialog::Accepted)
    {
        QuestionListItem *item = new QuestionListItem(this);
        item->set_type(2);
        ui->questionListLayout->insertWidget(0, item);
    }
}

void QuestionnaireManagementWidget::on_add_question_type3_clicked()
{
    QuestionTypeDialog dialog;
    dialog.setType(3);
    if(dialog.exec() == QDialog::Accepted)
    {
        QuestionListItem *item = new QuestionListItem(this);
        item->set_type(3);
        ui->questionListLayout->insertWidget(0, item);
    }
}

void QuestionnaireManagementWidget::on_add_questionnaire_clicked()
{
    while (QLayoutItem* item = ui->questionListLayout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
    ui->questionnaire_name->clear();
    ui->questionListLayout->addStretch();
    ui->stackedWidget->setCurrentIndex(4);
    ui->finish_questionnaire->show();
    ui->finish_edit->hide();
}

void QuestionnaireManagementWidget::on_finish_questionnaire_clicked()
{
    QuestionnaireListItem *item = new QuestionnaireListItem(this);
    connect(item, &QuestionnaireListItem::signal_questionnaire_edit, this, &QuestionnaireManagementWidget::slot_questionnaire_edit);
    connect(item, &QuestionnaireListItem::signal_questionnaire_delete, this, &QuestionnaireManagementWidget::slot_questionnaire_delete);
    item->set_questionnaire_name(ui->questionnaire_name->text());
    item->set_average_score(-1);
    item->set_question_number(ui->questionListLayout->count() - 1);
    item->set_answer_number(0);
    item->set_create_time(QDateTime::currentDateTime());

    ui->questionnaireListLayout->insertWidget(0, item);

    ui->stackedWidget->setCurrentIndex(0);
}

void QuestionnaireManagementWidget::slot_questionnaire_edit()
{
    while (QLayoutItem* item = ui->questionListLayout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

    //添加问卷
    QuestionnaireListItem *item = qobject_cast<QuestionnaireListItem*>(sender());
    ui->questionnaire_name->setText(item->questionnaire_name());
    ui->questionnaire_description->setText(item->questionnaire_description());

    //添加题目
    ui->questionListLayout->addStretch();

    QString question = item->question();
    QString answer = item->answer();
    QStringList questionStringList = question.split(',');
    QStringList answerStringList = answer.split(',');
    for (int i=0; i<questionStringList.size(); i++)
    {
        QSqlQuery query(QString("SELECT * FROM questionbank WHERE id = %1;").arg(questionStringList.at(i).toInt()));
        while (query.next()) {
            int type = query.value(1).toInt();

            QuestionListItem *questionItem = new QuestionListItem(this);
            questionItem->set_type(type);
            switch (type) {
            case 1:
                questionItem->set_scoring_question(query.value(2).toString());
                questionItem->set_scoring_answer(answerStringList.at(i).toInt());
                break;
            case 2:
                questionItem->set_choice_question(query.value(3).toString());
                questionItem->set_choice_enable_1(query.value("choice_enable_1").toInt());
                questionItem->set_choice_optional_1(query.value("choice_optional_1").toString());
                questionItem->set_choice_enable_2(query.value("choice_enable_2").toInt());
                questionItem->set_choice_optional_2(query.value("choice_optional_2").toString());
                questionItem->set_choice_enable_3(query.value("choice_enable_3").toInt());
                questionItem->set_choice_optional_3(query.value("choice_optional_3").toString());
                questionItem->set_choice_enable_4(query.value("choice_enable_4").toInt());
                questionItem->set_choice_optional_4(query.value("choice_optional_4").toString());
                questionItem->set_choice_answer(answerStringList.at(i).toInt());
                break;
            case 3:
                questionItem->set_subjective_question(query.value(4).toString());
                questionItem->set_subjective_answer(answerStringList.at(i));
                break;
            }

            ui->questionListLayout->insertWidget(0, questionItem);
        }
    }

    ui->stackedWidget->setCurrentIndex(4);
    ui->finish_questionnaire->hide();
    ui->finish_edit->show();
}

void QuestionnaireManagementWidget::slot_questionnaire_delete()
{
    //
}

void QuestionnaireManagementWidget::on_finish_edit_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


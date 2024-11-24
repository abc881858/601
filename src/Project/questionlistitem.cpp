#include "questionlistitem.h"
#include "ui_questionlistitem.h"

QuestionListItem::QuestionListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionListItem)
{
    ui->setupUi(this);
    ui->choice_optional_1->hide();
    ui->choice_optional_2->hide();
    ui->choice_optional_3->hide();
    ui->choice_optional_4->hide();
}

QuestionListItem::~QuestionListItem()
{
    delete ui;
}

void QuestionListItem::set_type(int type)
{
    ui->stackedWidget->setCurrentIndex(type - 1);
}

void QuestionListItem::set_scoring_question(QString text)
{
    ui->scoring_question->setText(text);
}

void QuestionListItem::set_scoring_answer(int score)
{
    switch (score) {
    case 1:
        ui->radioButton_1->setChecked(true);
        break;
    case 2:
        ui->radioButton_2->setChecked(true);
        break;
    case 3:
        ui->radioButton_3->setChecked(true);
        break;
    case 4:
        ui->radioButton_4->setChecked(true);
        break;
    case 5:
        ui->radioButton_5->setChecked(true);
        break;
    case 6:
        ui->radioButton_6->setChecked(true);
        break;
    case 7:
        ui->radioButton_7->setChecked(true);
        break;
    case 8:
        ui->radioButton_8->setChecked(true);
        break;
    case 9:
        ui->radioButton_9->setChecked(true);
        break;
    case 10:
        ui->radioButton_10->setChecked(true);
        break;
    }
}

void QuestionListItem::set_choice_question(QString text)
{
    ui->choice_question->setText(text);
}

void QuestionListItem::set_choice_answer(int choice)
{
    switch (choice) {
    case 1:
        ui->choice_optional_1->setChecked(true);
        break;
    case 2:
        ui->choice_optional_2->setChecked(true);
        break;
    case 3:
        ui->choice_optional_3->setChecked(true);
        break;
    case 4:
        ui->choice_optional_4->setChecked(true);
        break;
    }
}

void QuestionListItem::set_subjective_question(QString text)
{
    ui->subjective_question->setText(text);
}

void QuestionListItem::set_subjective_answer(QString text)
{
    ui->subjective_answer->setPlainText(text);
}

void QuestionListItem::set_choice_optional_1(QString text)
{
    ui->choice_optional_1->setText(text);
}

void QuestionListItem::set_choice_optional_2(QString text)
{
    ui->choice_optional_2->setText(text);
}

void QuestionListItem::set_choice_optional_3(QString text)
{
    ui->choice_optional_3->setText(text);
}

void QuestionListItem::set_choice_optional_4(QString text)
{
    ui->choice_optional_4->setText(text);
}

void QuestionListItem::set_choice_enable_1(bool visible)
{
    ui->choice_optional_1->setVisible(visible);
}

void QuestionListItem::set_choice_enable_2(bool visible)
{
    ui->choice_optional_2->setVisible(visible);
}

void QuestionListItem::set_choice_enable_3(bool visible)
{
    ui->choice_optional_3->setVisible(visible);
}

void QuestionListItem::set_choice_enable_4(bool visible)
{
    ui->choice_optional_4->setVisible(visible);
}

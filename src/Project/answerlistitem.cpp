#include "answerlistitem.h"
#include "ui_answerlistitem.h"

AnswerListItem::AnswerListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnswerListItem)
{
    ui->setupUi(this);
}

AnswerListItem::~AnswerListItem()
{
    delete ui;
}

void AnswerListItem::set_questionnaire_name(QString text)
{
    ui->questionnaire_name->setText(text);
}

void AnswerListItem::set_answer_number(int value)
{
    ui->answer_number->setText(QString::number(value));
}

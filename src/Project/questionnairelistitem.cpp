#include "questionnairelistitem.h"
#include "ui_questionnairelistitem.h"

QuestionnaireListItem::QuestionnaireListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionnaireListItem)
{
    ui->setupUi(this);
}

QuestionnaireListItem::~QuestionnaireListItem()
{
    delete ui;
}

void QuestionnaireListItem::set_questionnaire_name(QString text)
{
    ui->questionnaire_name->setText(text);
}

void QuestionnaireListItem::set_average_score(int value)
{
    if(value == -1)
    {
        ui->average_score->setText("——");
    }
    else
    {
        ui->average_score->setText(QString::number(value));
    }
}

void QuestionnaireListItem::set_question_number(int value)
{
    ui->question_number->setText(QString::number(value));
}

void QuestionnaireListItem::set_answer_number(int value)
{
    ui->answer_number->setText(QString::number(value));
}

void QuestionnaireListItem::set_create_time(QDateTime dateTime)
{
    ui->create_time->setDateTime(dateTime);
}

void QuestionnaireListItem::on_preview_clicked()
{
    //
}

void QuestionnaireListItem::on_export_pdf_clicked()
{
    //
}

void QuestionnaireListItem::on_export_word_clicked()
{
    //
}

void QuestionnaireListItem::on_questionnaire_edit_clicked()
{
    emit signal_questionnaire_edit();
}

void QuestionnaireListItem::on_questionnaire_delete_clicked()
{
    emit signal_questionnaire_delete();
}

QString QuestionnaireListItem::questionnaire_name()
{
    return ui->questionnaire_name->text();
}

int QuestionnaireListItem::average_score()
{
    return ui->average_score->text().toInt();
}

int QuestionnaireListItem::question_number()
{
    return ui->question_number->text().toInt();
}

int QuestionnaireListItem::answer_number()
{
    return ui->answer_number->text().toInt();
}

QDateTime QuestionnaireListItem::create_time()
{
    return ui->create_time->dateTime();
}

void QuestionnaireListItem::set_questionnaire_description(QString text)
{
    m_questionnaire_description = text;
}

QString QuestionnaireListItem::questionnaire_description()
{
    return m_questionnaire_description;
}

void QuestionnaireListItem::set_question(QString question)
{
    m_question = question;
}

QString QuestionnaireListItem::question()
{
    return m_question;
}

void QuestionnaireListItem::set_answer(QString answer)
{
    m_answer = answer;
}

QString QuestionnaireListItem::answer()
{
    return m_answer;
}

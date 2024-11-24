#pragma once

#include <QWidget>

namespace Ui {
class QuestionnaireListItem;
}

class QuestionnaireListItem : public QWidget
{
    Q_OBJECT
public:
    explicit QuestionnaireListItem(QWidget *parent = nullptr);
    ~QuestionnaireListItem();
    void set_questionnaire_name(QString text);
    void set_average_score(int value);
    void set_question_number(int value);
    void set_answer_number(int value);
    void set_create_time(QDateTime dateTime);
    QString questionnaire_name();
    int average_score();
    int question_number();
    int answer_number();
    QDateTime create_time();
    void set_questionnaire_description(QString text);
    QString questionnaire_description();
    void set_question(QString question);
    QString question();
    void set_answer(QString answer);
    QString answer();
private slots:
    void on_preview_clicked();
    void on_export_pdf_clicked();
    void on_export_word_clicked();
    void on_questionnaire_edit_clicked();
    void on_questionnaire_delete_clicked();
private:
    Ui::QuestionnaireListItem *ui;
    QString m_questionnaire_description;
    QString m_question;
    QString m_answer;
signals:
    void signal_questionnaire_edit();
    void signal_questionnaire_delete();
};

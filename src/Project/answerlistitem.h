#pragma once

#include <QWidget>

namespace Ui {
class AnswerListItem;
}

class AnswerListItem : public QWidget
{
    Q_OBJECT
public:
    explicit AnswerListItem(QWidget *parent = nullptr);
    ~AnswerListItem();
    void set_questionnaire_name(QString text);
    void set_answer_number(int value);
private:
    Ui::AnswerListItem *ui;
};

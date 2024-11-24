#pragma once

#include <QWidget>

namespace Ui {
class QuestionListItem;
}

class QuestionListItem : public QWidget
{
    Q_OBJECT
public:
    explicit QuestionListItem(QWidget *parent = nullptr);
    ~QuestionListItem();
    void set_type(int type);
    void set_scoring_question(QString text);
    void set_choice_question(QString text);
    void set_subjective_question(QString text);
    void set_choice_optional_1(QString text);
    void set_choice_optional_2(QString text);
    void set_choice_optional_3(QString text);
    void set_choice_optional_4(QString text);
    void set_choice_enable_1(bool visible);
    void set_choice_enable_2(bool visible);
    void set_choice_enable_3(bool visible);
    void set_choice_enable_4(bool visible);
    void set_scoring_answer(int score);
    void set_choice_answer(int choice);
    void set_subjective_answer(QString text);
private:
    Ui::QuestionListItem *ui;
};

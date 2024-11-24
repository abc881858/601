#pragma once

#include <QWidget>

namespace Ui {
class QuestionItem;
}

class QuestionItem : public QWidget
{
    Q_OBJECT
public:
    explicit QuestionItem(QWidget *parent = nullptr);
    void setNameIndex(int nameIndex);
    ~QuestionItem();
private slots:
    void on_trigger_action_clicked();

private:
    Ui::QuestionItem *ui;
};

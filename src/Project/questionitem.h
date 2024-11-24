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
    QString name();
    void set_select_questionnaire(QString text);
    void set_trigger_action(int id);
private:
    Ui::QuestionItem *ui;
private slots:
    void on_trigger_action_clicked();
signals:
    void trigger_questionnaire_changed(QString, int);
};

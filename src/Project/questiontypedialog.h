#pragma once

#include <QDialog>

namespace Ui {
class QuestionTypeDialog;
}

class QuestionTypeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit QuestionTypeDialog(QWidget *parent = nullptr);
    ~QuestionTypeDialog();
    void setType(int type);
private:
    Ui::QuestionTypeDialog *ui;
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

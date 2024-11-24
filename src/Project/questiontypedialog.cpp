#include "questiontypedialog.h"
#include "ui_questiontypedialog.h"

QuestionTypeDialog::QuestionTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionTypeDialog)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

QuestionTypeDialog::~QuestionTypeDialog()
{
    delete ui;
}

void QuestionTypeDialog::setType(int type)
{
    ui->stackedWidget->setCurrentIndex(type - 1);
}

void QuestionTypeDialog::on_buttonBox_accepted()
{
    accept();
}

void QuestionTypeDialog::on_buttonBox_rejected()
{
    reject();
}

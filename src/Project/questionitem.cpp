#include "questionitem.h"
#include "ui_questionitem.h"
#include <QSqlQuery>
#include "triggeractiondialog.h"

//任务下的问卷列表
QuestionItem::QuestionItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionItem)
{
    ui->setupUi(this);

    QStringList stringList;
    QSqlQuery query("SELECT questionnaire_name FROM questionnaire");
    while (query.next()) {
        stringList << query.value(0).toString();
    }
    ui->select_questionnaire->addItems(stringList);
}

void QuestionItem::setNameIndex(int nameIndex)
{
    ui->name->setText(QString("问卷%1").arg(nameIndex));
}

QuestionItem::~QuestionItem()
{
    delete ui;
}

void QuestionItem::on_trigger_action_clicked()
{
    TriggerActionDialog dialog;
    if(dialog.exec() == QDialog::Accepted)
    {
        ui->trigger_action->setText(dialog.result_name());
        dialog.result_id();
    }
}

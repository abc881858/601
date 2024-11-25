#include "questionitem.h"
#include "ui_questionitem.h"
#include "triggeractiondialog.h"

//任务下的问卷列表
QuestionItem::QuestionItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionItem)
{
    ui->setupUi(this);

    QStringList stringList;
    QSqlQuery query;
    query.exec("SELECT questionnaire_name FROM questionnaire");
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

QString QuestionItem::name()
{
    return ui->select_questionnaire->currentText();
}

void QuestionItem::on_trigger_action_clicked()
{
    TriggerActionDialog dialog;
    if(ui->trigger_action->text() != "请选择触发动作")
    {
        dialog.selectItemByPath(ui->trigger_action->text());
    }
    if(dialog.exec() == QDialog::Accepted)
    {
        ui->trigger_action->setText(dialog.result_name());

        //QSqlQuery query("UPDATE task SET trigger_questionnaire = '%1' WHERE ");

        emit trigger_questionnaire_changed(ui->select_questionnaire->currentText(), dialog.result_id());
    }
}

void QuestionItem::set_select_questionnaire(QString text)
{
    ui->select_questionnaire->setCurrentText(text);
}

void QuestionItem::set_trigger_action(int id)
{
    TriggerActionDialog dialog;
    dialog.hide();
    ui->trigger_action->setText(dialog.name_from_id(id));
}

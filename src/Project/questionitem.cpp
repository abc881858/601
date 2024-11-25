#include "questionitem.h"
#include "ui_questionitem.h"

//任务下的问卷列表
QuestionItem::QuestionItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionItem)
{
    ui->setupUi(this);
    dialog.hide();

    QStringList stringList;
    QSqlQuery query;
    query.exec("SELECT questionnaire_name FROM questionnaire");
    while (query.next()) {
        stringList << query.value(0).toString();
    }
    ui->task_questionnaire->addItems(stringList);
}

void QuestionItem::setNameIndex(int nameIndex)
{
    ui->name->setText(QString("问卷%1").arg(nameIndex));
}

QuestionItem::~QuestionItem()
{
    delete ui;
}

void QuestionItem::set_task_questionnaire(QString text)
{
    ui->task_questionnaire->setCurrentText(text);
}

QString QuestionItem::task_questionnaire()
{
    return ui->task_questionnaire->currentText();
}

void QuestionItem::set_trigger_questionnaire(int id)
{
    qDebug() << __func__ << id;
    ui->trigger_questionnaire->setText(dialog.name_from_id(id));
    dialog.selectItemByButtonId(id);
}

int QuestionItem::trigger_questionnaire()
{
    return dialog.result_id();
}

void QuestionItem::on_trigger_questionnaire_clicked()
{
    if(ui->trigger_questionnaire->text() != "请选择触发动作")
    {
        dialog.selectItemByPath(ui->trigger_questionnaire->text());
    }
    if(dialog.exec() == QDialog::Accepted)
    {
        ui->trigger_questionnaire->setText(dialog.result_name());
    }
}

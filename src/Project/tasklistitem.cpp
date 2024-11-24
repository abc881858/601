#include "tasklistitem.h"
#include "ui_tasklistitem.h"

TaskListItem::TaskListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskListItem)
{
    ui->setupUi(this);
}

TaskListItem::~TaskListItem()
{
    delete ui;
}

void TaskListItem::on_task_start_clicked()
{
    qDebug() << __func__ << __FILE__ << __LINE__;
    emit task_start();
}

void TaskListItem::on_task_edit_clicked()
{
    qDebug() << __func__ << __FILE__ << __LINE__;
    emit task_edit();
}

void TaskListItem::on_task_delete_clicked()
{
    qDebug() << __func__ << __FILE__ << __LINE__;
    emit task_delete();
}

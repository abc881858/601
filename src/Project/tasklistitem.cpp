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

void TaskListItem::set_task_name(QString text)
{
    ui->task_name->setText(text);
}

void TaskListItem::set_create_name(QString text)
{
    ui->create_name->setText(text);
}

void TaskListItem::set_create_time(QDateTime dateTime)
{
    ui->create_time->setDateTime(dateTime);
}

void TaskListItem::set_task_description(QString text)
{
    ui->task_description->setPlainText(text);
}

void TaskListItem::set_task_type(QString task_type)
{
    m_task_type = task_type;
}

void TaskListItem::set_task_path(QString task_path)
{
    m_task_path = task_path;
}

void TaskListItem::set_task_questionnaire(QString task_questionnaire)
{
    m_task_questionnaire = task_questionnaire;
}

void TaskListItem::set_task_event(QString task_event)
{
    m_task_event = task_event;
}

void TaskListItem::set_trigger_questionnaire(QString trigger_questionnaire)
{
    m_trigger_questionnaire = trigger_questionnaire;
}

void TaskListItem::set_trigger_event(QString trigger_event)
{
    m_trigger_event = trigger_event;
}

QString TaskListItem::task_questionnaire() const
{
    return m_task_questionnaire;
}

QString TaskListItem::task_event() const
{
    return m_task_event;
}

QString TaskListItem::trigger_questionnaire() const
{
    return m_trigger_questionnaire;
}

QString TaskListItem::trigger_event() const
{
    return m_trigger_event;
}

QString TaskListItem::task_name()
{
    return ui->task_name->text();
}

QString TaskListItem::create_name()
{
    return ui->create_name->text();
}

QDateTime TaskListItem::create_time()
{
    return ui->create_time->dateTime();
}

QString TaskListItem::task_description()
{
    return ui->task_description->toPlainText();
}

QString TaskListItem::task_type()
{
    return m_task_type;
}

QString TaskListItem::task_path()
{
    return m_task_path;
}

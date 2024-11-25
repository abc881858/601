#include "eventitem.h"
#include "ui_eventitem.h"
#include <QSqlQuery>
#include "eventchilditem.h"

//任务下的事件列表
EventItem::EventItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventItem)
{
    ui->setupUi(this);
}

EventItem::~EventItem()
{
    delete ui;
}

void EventItem::on_add_child_clicked()
{
    EventChildItem *item = new EventChildItem;
    ui->eventItemLayout->addWidget(item);
}

void EventItem::on_delete_child_clicked()
{
    if(ui->eventItemLayout->count() > 0)
    {
        QLayoutItem* item = ui->eventItemLayout->takeAt(ui->eventItemLayout->count() - 1);
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
}

void EventItem::set_task_event(QString task_event)
{
    ui->task_event->setText(task_event);
}

QString EventItem::task_event()
{
    return ui->task_event->text();
}

void EventItem::set_trigger_event(QString trigger_event)
{
    QStringList trigger_event_list = trigger_event.split('-');
    for(int i=0; i<trigger_event_list.size(); i++)
    {
        EventChildItem *eventChildItem = new EventChildItem;
        eventChildItem->set_trigger_event(trigger_event_list.at(i).toInt());
        ui->eventItemLayout->addWidget(eventChildItem);
    }
}

QString EventItem::trigger_event()
{
    QStringList trigger_event_list;
    for(int i=0; i<ui->eventItemLayout->count(); i++)
    {
        QLayoutItem* item = ui->eventItemLayout->itemAt(i);
        if (!item) continue;

        QWidget* widget = item->widget();
        if (widget)
        {
            EventChildItem* eventChildItem = qobject_cast<EventChildItem*>(widget);
            if (eventChildItem) {
                trigger_event_list << QString::number(eventChildItem->trigger_event());
            }
        }
    }
    return trigger_event_list.join('-');
}

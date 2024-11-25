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

    QStringList stringList;
    QSqlQuery query("SELECT event_name FROM event");
    while (query.next()) {
        stringList << query.value(0).toString();
    }
    //ui->select_questionnaire->addItems(stringList);
}

EventItem::~EventItem()
{
    delete ui;
}

void EventItem::on_add_child_clicked()
{
    EventChildItem *item = new EventChildItem;
    ui->eventItemLayout->insertWidget(0, item);
}

void EventItem::on_delete_child_clicked()
{
    QLayoutItem* item = ui->eventItemLayout->takeAt(0);
    if (QWidget* widget = item->widget()) {
        widget->deleteLater();
    }
    delete item;
}

QString EventItem::name()
{
    return "";
}

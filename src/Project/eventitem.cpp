#include "eventitem.h"
#include "ui_eventitem.h"

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

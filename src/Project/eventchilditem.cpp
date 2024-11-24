#include "eventchilditem.h"
#include "ui_eventchilditem.h"

EventChildItem::EventChildItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::eventChildItem)
{
    ui->setupUi(this);
}

EventChildItem::~EventChildItem()
{
    delete ui;
}

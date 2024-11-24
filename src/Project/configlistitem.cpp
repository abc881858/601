#include "configlistitem.h"
#include "ui_configlistitem.h"

ConfigListItem::ConfigListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigListItem)
{
    ui->setupUi(this);
}

ConfigListItem::~ConfigListItem()
{
    delete ui;
}

#include "replaywidget.h"
#include "ui_replaywidget.h"
#include "replaylistitem.h"

ReplayWidget::ReplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReplayWidget)
{
    ui->setupUi(this);

    for(int i=0; i<5; i++)
    {
        ReplayListItem *item = new ReplayListItem(this);
        ui->replayListLayout->addWidget(item);
    }
    ui->replayListLayout->addStretch();
}

ReplayWidget::~ReplayWidget()
{
    delete ui;
}

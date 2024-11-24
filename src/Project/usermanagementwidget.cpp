#include "usermanagementwidget.h"
#include "ui_usermanagementwidget.h"

UserManagementWidget::UserManagementWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManagementWidget)
{
    ui->setupUi(this);
}

UserManagementWidget::~UserManagementWidget()
{
    delete ui;
}

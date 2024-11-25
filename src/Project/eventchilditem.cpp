#include "eventchilditem.h"
#include "ui_eventchilditem.h"

EventChildItem::EventChildItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::eventChildItem)
{
    ui->setupUi(this);
    dialog.hide();
}

EventChildItem::~EventChildItem()
{
    delete ui;
}

void EventChildItem::set_trigger_event(int id)
{
    ui->trigger_event->setText(dialog.name_from_id(id));
    dialog.selectItemByButtonId(id);
}

int EventChildItem::trigger_event()
{
    return dialog.result_id();
}

void EventChildItem::on_pushButton_clicked()
{
    if(dialog.exec() == QDialog::Accepted)
    {
        ui->trigger_event->setText(dialog.result_name());
    }
}

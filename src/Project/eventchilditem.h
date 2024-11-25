#pragma once

#include <QWidget>
#include "triggeractiondialog.h"

namespace Ui {
class eventChildItem;
}

class EventChildItem : public QWidget
{
    Q_OBJECT
public:
    explicit EventChildItem(QWidget *parent = nullptr);
    ~EventChildItem();
    void set_trigger_event(int id);
    int trigger_event();
private:
    Ui::eventChildItem *ui;
    TriggerActionDialog dialog;
private slots:
    void on_pushButton_clicked();
};

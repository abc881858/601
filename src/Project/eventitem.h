#pragma once

#include <QWidget>

namespace Ui {
class EventItem;
}

class EventItem : public QWidget
{
    Q_OBJECT
public:
    explicit EventItem(QWidget *parent = nullptr);
    ~EventItem();
private:
    Ui::EventItem *ui;
};

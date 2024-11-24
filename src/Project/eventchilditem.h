#pragma once

#include <QWidget>

namespace Ui {
class eventChildItem;
}

class EventChildItem : public QWidget
{
    Q_OBJECT
public:
    explicit EventChildItem(QWidget *parent = nullptr);
    ~EventChildItem();
private:
    Ui::eventChildItem *ui;
};

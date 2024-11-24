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
    QString name();
private:
    Ui::EventItem *ui;
private slots:
    void on_add_child_clicked();
    void on_delete_child_clicked();
};

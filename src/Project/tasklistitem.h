#pragma once

#include <QWidget>

namespace Ui {
class TaskListItem;
}

class TaskListItem : public QWidget
{
    Q_OBJECT
public:
    explicit TaskListItem(QWidget *parent = nullptr);
    ~TaskListItem();
private:
    Ui::TaskListItem *ui;
private slots:
    void on_task_start_clicked();
    void on_task_edit_clicked();
    void on_task_delete_clicked();
signals:
    void task_start();
    void task_edit();
    void task_delete();
};

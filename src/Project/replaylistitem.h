#pragma once

#include <QWidget>

namespace Ui {
class ReplayListItem;
}

class ReplayListItem : public QWidget
{
    Q_OBJECT

public:
    explicit ReplayListItem(QWidget *parent = nullptr);
    ~ReplayListItem();

private:
    Ui::ReplayListItem *ui;
};

#pragma once

#include <QWidget>

namespace Ui {
class ConfigListItem;
}

class ConfigListItem : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigListItem(QWidget *parent = nullptr);
    ~ConfigListItem();

private:
    Ui::ConfigListItem *ui;
};

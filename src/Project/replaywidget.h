#ifndef REPLAYWIDGET_H
#define REPLAYWIDGET_H

#include <QWidget>

namespace Ui {
class ReplayWidget;
}

class ReplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReplayWidget(QWidget *parent = nullptr);
    ~ReplayWidget();

private:
    Ui::ReplayWidget *ui;
};

#endif // REPLAYWIDGET_H

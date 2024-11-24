#pragma once

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSslSocket>

namespace QWK {
    class WidgetWindowAgent;
    class StyleAgent;
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;
protected:
    bool event(QEvent *event) override;
private:
    Ui::MainWindow *ui;
    void installWindowAgent();
    QWK::WidgetWindowAgent *windowAgent;
    QSqlDatabase db;
private slots:
    void on_toolButton_1_clicked();
    void on_toolButton_2_clicked();
    void on_toolButton_3_clicked();
};

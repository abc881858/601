#pragma once

#include <QWidget>
#include <QUdpSocket>
#include <QProcess>

struct ButtonClickEvent
{
    int buttonId;      /*按键号*/
    int hour;          //时间戳-时
    int minute;        //时间戳-分
    int second;        //时间戳-秒
    int millisecond;   //时间戳-毫秒
};

namespace Ui {
class TaskWidget;
}

class TaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TaskWidget(QWidget *parent = nullptr);
    ~TaskWidget();
    QString type_string();
    void init();
private:
    Ui::TaskWidget *ui;
    QUdpSocket *m_udp;
    ButtonClickEvent receivedData;
    QProcess process;
    int m_question_item_count{0};
    int m_event_item_count{0};
    QTimer *m_task_timer;
    QString m_exePath;
public slots:
    void readyRead();
    void task_start();
    void task_edit();
private slots:
    void on_add_task_clicked();
    void on_buttonReturn_clicked();
    void on_buttonSave_clicked();
    void on_config_clicked();
    void on_addConfig_clicked();
    void on_configSave_clicked();
    void on_buttonBack_clicked();
    void on_buttonOpen_clicked();
    void on_add_question_clicked();
    void on_add_event_clicked();
    void on_task_return_clicked();
    void on_task_finish_clicked();
    void on_checkBox_type_left_clicked();
    void on_checkBox_type_right_clicked();
    void on_finish_edit_clicked();
};

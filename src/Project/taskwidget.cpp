#include "taskwidget.h"
#include "ui_taskwidget.h"
#include "tasklistitem.h"
#include "configlistitem.h"
#include <QDebug>
#include <QFileDialog>
#include "questionitem.h"
#include "eventitem.h"
#include <QTimer>
#include <QSqlQuery>

TaskWidget::TaskWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskWidget)
{
    ui->setupUi(this);

    m_udp = new QUdpSocket(this);
    m_udp->bind(QHostAddress::AnyIPv4, 6500, QUdpSocket::ShareAddress);
    m_udp->joinMulticastGroup(QHostAddress("224.0.0.0"));
    connect(m_udp, &QUdpSocket::readyRead, this, &TaskWidget::readyRead);

    ui->stack_widget->setCurrentIndex(0);

    ui->taskListLayout->addStretch();

    for(int i=0; i<10; i++)
    {
        ConfigListItem *item = new ConfigListItem(this);
        ui->configListLayout->addWidget(item);
    }
    ui->configListLayout->addStretch();

    ui->widget_type_right->hide();
    m_task_timer = new QTimer(this);
    connect(m_task_timer, &QTimer::timeout, [=](){
        ui->timeEdit->setTime(ui->timeEdit->time().addSecs(1));
    });
}

TaskWidget::~TaskWidget()
{
    if (process.state() == QProcess::Running)
    {
        process.terminate();
        process.waitForFinished(3000);
    }
    delete ui;
}

void TaskWidget::readyRead()
{
    while(m_udp->hasPendingDatagrams())
    {
        QByteArray buffer;
        buffer.resize(m_udp->pendingDatagramSize());
        m_udp->readDatagram(buffer.data(), buffer.size());
        memcpy(&receivedData, buffer.data(), sizeof(ButtonClickEvent));
        qDebug() << receivedData.buttonId << receivedData.hour << receivedData.minute << receivedData.second << receivedData.millisecond;
    }
}

void TaskWidget::on_add_task_clicked()
{
    ui->task_name->clear();
    ui->task_description->clear();
    ui->checkBox_type_left->setChecked(false);
    ui->stack_widget->setCurrentIndex(1);
}

void TaskWidget::on_buttonReturn_clicked()
{
    ui->stack_widget->setCurrentIndex(0);
}

QString TaskWidget::type_string()
{
    QString string1;
    QString string2;
    if(ui->checkBox_type_left->isChecked())
    {
        string1 = ui->checkBox_type_left->text();
        if(ui->checkBox_left_sub1->isChecked())
        {
            string2 = ui->checkBox_left_sub1->text();
        }
        else if(ui->checkBox_left_sub2->isChecked())
        {
            string2 = ui->checkBox_left_sub2->text();
        }
        else if(ui->checkBox_left_sub3->isChecked())
        {
            string2 = ui->checkBox_left_sub3->text();
        }
        else if(ui->checkBox_left_sub4->isChecked())
        {
            string2 = ui->checkBox_left_sub4->text();
        }
    }
    else
    {
        string1 = ui->checkBox_type_right->text();
        if(ui->checkBox_right_sub1->isChecked())
        {
            string2 = ui->checkBox_right_sub1->text();
        }
        else if(ui->checkBox_right_sub2->isChecked())
        {
            string2 = ui->checkBox_right_sub2->text();
        }
        else if(ui->checkBox_right_sub3->isChecked())
        {
            string2 = ui->checkBox_right_sub3->text();
        }
        else if(ui->checkBox_right_sub4->isChecked())
        {
            string2 = ui->checkBox_right_sub4->text();
        }
    }

    return string1 + "-" + string2;
}

void TaskWidget::on_buttonSave_clicked()
{
    TaskListItem *item = new TaskListItem(this);
    connect(item, &TaskListItem::task_start, [=](){
        ui->label_task_name->setText(ui->task_name->text());
        ui->label_task_type->setText(type_string());
        ui->stack_widget->setCurrentIndex(4);
        m_task_timer->start(1000);
    });
    ui->taskListLayout->insertWidget(0, item);

    // for(int i=0; i<ui->layout_question->count(); i++)
    // {
    //     QuestionItem *item = qobject_cast<QuestionItem *>(ui->layout_question->itemAt(i)->widget());
    //     item->task_name();
    // }

    // QSqlQuery query(QString("INSERT INTO task (task_user, task_name, task_type, task_description, task_path, task_questionnaire, task_event, trigger_questionnaire, trigger_event) "
    //                 "VALUES ('%1','%2','%3','%4','%5','%6','%7','%8','%9');").arg("小菜无敌")
    //                 .arg(ui->task_name->text())
    //                 .arg(type_string())
    //                 .arg(ui->task_description->toPlainText())
    //                 .arg(m_exePath)
    //                 .arg());
    // query.exec();

    ui->stack_widget->setCurrentIndex(0);
}

void TaskWidget::on_config_clicked()
{
    ui->stack_widget->setCurrentIndex(2);
}

void TaskWidget::on_addConfig_clicked()
{
    ui->stack_widget->setCurrentIndex(3);
}

void TaskWidget::on_configSave_clicked()
{
    ui->stack_widget->setCurrentIndex(2);
}

void TaskWidget::on_buttonBack_clicked()
{
    ui->stack_widget->setCurrentIndex(1);
}

void TaskWidget::on_buttonOpen_clicked()
{
    m_exePath = QFileDialog::getOpenFileName(this, "选择可执行文件", "./", "可执行文件 (*.exe);;所有文件 (*)");
    if (!m_exePath.isEmpty())
    {
        process.start(m_exePath);
    }
}

void TaskWidget::on_add_question_clicked()
{
    QuestionItem *item = new QuestionItem;
    item->setNameIndex(1 + m_question_item_count);
    ui->layout_question->insertWidget(1 + m_question_item_count, item);
    m_question_item_count++;
}

void TaskWidget::on_add_event_clicked()
{
    EventItem *item = new EventItem;
    ui->layout_event->insertWidget(1 + m_event_item_count, item);
    m_event_item_count++;
}

void TaskWidget::on_task_return_clicked()
{
    ui->stack_widget->setCurrentIndex(0);
}

void TaskWidget::on_task_finish_clicked()
{
    ui->stack_widget->setCurrentIndex(0);
    m_task_timer->stop();
    ui->timeEdit->setTime(QTime(0,0,0,0));
}

void TaskWidget::on_checkBox_type_left_clicked()
{
    ui->widget_type_left->show();
    ui->widget_type_right->hide();
}

void TaskWidget::on_checkBox_type_right_clicked()
{
    ui->widget_type_left->hide();
    ui->widget_type_right->show();
}

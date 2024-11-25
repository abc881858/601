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

    ui->finish_edit->hide();
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

void TaskWidget::init()
{
    QSqlQuery query(QString("SELECT * FROM task"));
    while (query.next()) {
        TaskListItem *taskListItem = new TaskListItem(this);
        connect(taskListItem, &TaskListItem::task_start, this, &TaskWidget::task_start);
        connect(taskListItem, &TaskListItem::task_edit, this, &TaskWidget::task_edit);
        taskListItem->set_task_name(query.value(0).toString());
        taskListItem->set_create_name(query.value(1).toString());
        taskListItem->set_create_time(query.value(2).toDateTime());
        taskListItem->set_task_description(query.value(3).toString());
        taskListItem->set_task_type(query.value(4).toString());
        taskListItem->set_task_path(query.value(5).toString());
        taskListItem->set_task_questionnaire(query.value(6).toString());
        taskListItem->set_trigger_questionnaire(query.value(7).toString());
        taskListItem->set_task_event(query.value(8).toString());
        taskListItem->set_trigger_event(query.value(9).toString());
        ui->taskListLayout->insertWidget(0, taskListItem);
    }
}

void TaskWidget::task_start()
{
    //TODO: 提示先关闭上一个任务 然后才能开启新任务
    ui->label_task_name->setText(ui->task_name->text());
    ui->label_task_type->setText(type_string());
    ui->stack_widget->setCurrentIndex(4);

    if (!m_exePath.isEmpty())
    {
        process.start(m_exePath);
    }

    m_task_timer->start(1000);
}

void TaskWidget::task_edit()
{
    ui->buttonSave->hide();
    ui->finish_edit->show();

    TaskListItem *taskListItem = qobject_cast<TaskListItem*>(sender());

    QSqlQuery query(QString("SELECT * FROM task WHERE task_name = '%1';").arg(taskListItem->task_name()));
    if(query.next())
    {
        taskListItem->set_create_name(query.value(1).toString());
        taskListItem->set_create_time(query.value(2).toDateTime());
        taskListItem->set_task_description(query.value(3).toString());
        taskListItem->set_task_type(query.value(4).toString());
        taskListItem->set_task_path(query.value(5).toString());
        taskListItem->set_task_questionnaire(query.value(6).toString());
        taskListItem->set_trigger_questionnaire(query.value(7).toString());
        taskListItem->set_task_event(query.value(8).toString());
        taskListItem->set_trigger_event(query.value(9).toString());
    }

    ui->task_name->setText(taskListItem->task_name());
    ui->task_description->setText(taskListItem->task_description());
    QStringList task_type_list = taskListItem->task_type().split('-');
    if(task_type_list.size() == 2)
    {
        if(ui->checkBox_type_left->text() == task_type_list.at(0))
        {
            ui->checkBox_type_left->setChecked(true);
            if(ui->checkBox_left_sub1->text() == task_type_list.at(1))
            {
                ui->checkBox_left_sub1->setChecked(true);
            }
            else if(ui->checkBox_left_sub2->text() == task_type_list.at(1))
            {
                ui->checkBox_left_sub2->setChecked(true);
            }
            else if(ui->checkBox_left_sub3->text() == task_type_list.at(1))
            {
                ui->checkBox_left_sub3->setChecked(true);
            }
            else if(ui->checkBox_left_sub4->text() == task_type_list.at(1))
            {
                ui->checkBox_left_sub4->setChecked(true);
            }
        }
        else
        {
            ui->checkBox_type_right->setChecked(true);
            if(ui->checkBox_right_sub1->text() == task_type_list.at(1))
            {
                ui->checkBox_right_sub1->setChecked(true);
            }
            else if(ui->checkBox_right_sub2->text() == task_type_list.at(1))
            {
                ui->checkBox_right_sub2->setChecked(true);
            }
            else if(ui->checkBox_right_sub3->text() == task_type_list.at(1))
            {
                ui->checkBox_right_sub3->setChecked(true);
            }
            else if(ui->checkBox_right_sub4->text() == task_type_list.at(1))
            {
                ui->checkBox_right_sub4->setChecked(true);
            }
        }
    }

    //TODO: m_exePath 放入 TaskListItem 类
    m_exePath = taskListItem->task_path();

    m_question_item_count = 0;
    while (QLayoutItem* item = ui->layout_question->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
    ui->layout_question->addStretch();

    m_event_item_count = 0;
    while (QLayoutItem* item = ui->layout_event->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
    ui->layout_event->addStretch();

    QStringList task_questionnaire_list = taskListItem->task_questionnaire().split(',');
    QStringList trigger_questionnaire_list = taskListItem->trigger_questionnaire().split(',');
    for(int i=0; i<task_questionnaire_list.size(); i++)
    {
        QuestionItem *questionItem = new QuestionItem;
        questionItem->setNameIndex(1 + m_question_item_count);
        questionItem->set_task_questionnaire(task_questionnaire_list.at(i));
        questionItem->set_trigger_questionnaire(trigger_questionnaire_list.at(i).toInt());
        ui->layout_question->insertWidget(1 + m_question_item_count, questionItem);
        m_question_item_count++;
    }

    QStringList task_event_list = taskListItem->task_event().split(',');
    QStringList trigger_event_list = taskListItem->trigger_event().split(',');
    for(int i=0; i<task_event_list.size(); i++)
    {
        EventItem *eventItem = new EventItem;
        eventItem->set_task_event(task_event_list.at(i));
        eventItem->set_trigger_event(trigger_event_list.at(i));
        ui->layout_event->insertWidget(1 + m_event_item_count, eventItem);
        m_event_item_count++;
    }

    ui->stack_widget->setCurrentIndex(1);
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

    while (QLayoutItem* item = ui->layout_question->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
    ui->layout_question->addStretch();

    while (QLayoutItem* item = ui->layout_event->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
    ui->layout_event->addStretch();

    ui->buttonSave->show();
    ui->finish_edit->hide();

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
    QStringList task_questionnaire_list;
    QStringList trigger_questionnaire_list;
    for(int i=0; i<ui->layout_question->count(); i++)
    {
        QLayoutItem* item = ui->layout_question->itemAt(i);
        if (!item) continue;

        QWidget* widget = item->widget();
        if (widget)
        {
            QuestionItem* questionItem = qobject_cast<QuestionItem*>(widget);
            if (questionItem)
            {
                task_questionnaire_list << questionItem->task_questionnaire();
                trigger_questionnaire_list << QString::number(questionItem->trigger_questionnaire());
            }
        }
    }

    QStringList task_event_list;
    QStringList trigger_event_list;
    for(int i=0; i<ui->layout_event->count(); i++)
    {
        QLayoutItem* item = ui->layout_event->itemAt(i);
        if (!item) continue;

        QWidget* widget = item->widget();
        if (widget)
        {
            EventItem* eventItem = qobject_cast<EventItem*>(widget);
            if (eventItem)
            {
                task_event_list << eventItem->task_event();
                trigger_event_list << eventItem->trigger_event();
            }
        }
    }

    QSqlQuery query;
    QString str = QString("INSERT INTO task (task_name, create_name, create_time, task_description, task_type, task_path, task_questionnaire, task_event, trigger_questionnaire, trigger_event) "
                          "VALUES ('%1', '%2', %3, '%4', '%5', '%6', '%7', '%8', '%9', '%10');")
            .arg(ui->task_name->text())
            .arg("小菜无敌")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
            .arg(ui->task_description->toPlainText())
            .arg(type_string())
            .arg(m_exePath)
            .arg(task_questionnaire_list.join(','))
            .arg(task_event_list.join(','))
            .arg(trigger_questionnaire_list.join(','))
            .arg(trigger_event_list.join(','));
    query.exec(str);

    TaskListItem *taskListItem = new TaskListItem(this);
    connect(taskListItem, &TaskListItem::task_start, this, &TaskWidget::task_start);
    connect(taskListItem, &TaskListItem::task_edit, this, &TaskWidget::task_edit);
    taskListItem->set_task_name(ui->task_name->text());
    taskListItem->set_create_name("小菜无敌");
    taskListItem->set_create_time(QDateTime::currentDateTime());
    taskListItem->set_task_description(ui->task_description->toPlainText());
    ui->taskListLayout->insertWidget(0, taskListItem);

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

    if (process.state() == QProcess::Running)
    {
        process.terminate();
        process.waitForFinished(3000);
    }
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

void TaskWidget::on_finish_edit_clicked()
{
    QStringList task_questionnaire_list;
    QStringList trigger_questionnaire_list;
    for(int i=0; i<ui->layout_question->count(); i++)
    {
        QLayoutItem* item = ui->layout_question->itemAt(i);
        if (!item) continue;

        QWidget* widget = item->widget();
        if (widget)
        {
            QuestionItem* questionItem = qobject_cast<QuestionItem*>(widget);
            if (questionItem)
            {
                task_questionnaire_list << questionItem->task_questionnaire();
                trigger_questionnaire_list << QString::number(questionItem->trigger_questionnaire());
            }
        }
    }

    QStringList task_event_list;
    QStringList trigger_event_list;
    for(int i=0; i<ui->layout_event->count(); i++)
    {
        QLayoutItem* item = ui->layout_event->itemAt(i);
        if (!item) continue;

        QWidget* widget = item->widget();
        if (widget)
        {
            EventItem* eventItem = qobject_cast<EventItem*>(widget);
            if (eventItem)
            {
                task_event_list << eventItem->task_event();
                trigger_event_list << eventItem->trigger_event();
            }
        }
    }

    QSqlQuery query;
    QString task_name = ui->task_name->text();
    QString str = QString("UPDATE task "
                          "SET create_name = '%1', create_time = '%2', "
                          "task_description = '%3', task_type = '%4', task_path = '%5', "
                          "task_questionnaire = '%6', task_event = '%7', "
                          "trigger_questionnaire = '%8', trigger_event = '%9' "
                          "WHERE task_name = '%10';")
            .arg("小菜无敌")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))  // 更新时间
            .arg(ui->task_description->toPlainText())                           // 更新任务描述
            .arg(type_string())                                                 // 更新任务类型
            .arg(m_exePath)                                                     // 更新任务路径
            .arg(task_questionnaire_list.join(','))                             // 更新问卷列表
            .arg(task_event_list.join(','))                                     // 更新事件列表
            .arg(trigger_questionnaire_list.join(','))                          // 更新触发问卷列表
            .arg(trigger_event_list.join(','))                                  // 更新触发事件列表
            .arg(task_name);                                                    // 指定更新的任务名
    query.exec(str);

    for(int i=0; i<ui->taskListLayout->count(); i++)
    {
        QLayoutItem* item = ui->taskListLayout->itemAt(i);
        if (!item) continue;

        QWidget* widget = item->widget();
        if (widget)
        {
            TaskListItem* taskListItem = qobject_cast<TaskListItem*>(widget);
            if (taskListItem)
            {
                if(taskListItem->task_name() == ui->task_name->text())
                {
                    taskListItem->set_create_name("小菜无敌");
                    taskListItem->set_create_time(QDateTime::currentDateTime());
                    taskListItem->set_task_description(ui->task_description->toPlainText());
                    break;
                }
            }
        }
    }

    ui->stack_widget->setCurrentIndex(0);
}


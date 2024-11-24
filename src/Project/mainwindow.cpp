#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QWindow>
#include <QApplication>
#include <QStyle>
#include <QPushButton>
#include <QActionGroup>

#include <widgetwindowagent.h>
#include "widgetframe/windowbar.h"
#include "widgetframe/windowbar.cpp"
#include "widgetframe/windowbutton.cpp"
#include "widgetframe/windowbar.h"
#include "widgetframe/windowbar_p.h"
#include "widgetframe/windowbutton.h"
#include "widgetframe/windowbutton_p.h"

static inline void emulateLeaveEvent(QWidget *widget)
{
    Q_ASSERT(widget);
    if (!widget) return;
    QTimer::singleShot(0, widget, [widget]() {
        const QScreen *screen = widget->screen();
        const QPoint globalPos = QCursor::pos(screen);
        if (!QRect(widget->mapToGlobal(QPoint{0, 0}), widget->size()).contains(globalPos)) {
            QCoreApplication::postEvent(widget, new QEvent(QEvent::Leave));
            if (widget->testAttribute(Qt::WA_Hover)) {
                const QPoint localPos = widget->mapFromGlobal(globalPos);
                const QPoint scenePos = widget->window()->mapFromGlobal(globalPos);
                static constexpr const auto oldPos = QPoint{};
                const Qt::KeyboardModifiers modifiers = QGuiApplication::keyboardModifiers();
                const auto event =
                    new QHoverEvent(QEvent::HoverLeave, scenePos, globalPos, oldPos, modifiers);
                Q_UNUSED(localPos);
                QCoreApplication::postEvent(widget, event);
            }
        }
    });
}

bool MainWindow::event(QEvent *event) {
    switch (event->type()) {
        case QEvent::WindowActivate: {
            auto menu = menuWidget();
            if (menu) {
                menu->setProperty("bar-active", true);
                style()->polish(menu);
            }
            break;
        }
        case QEvent::WindowDeactivate: {
            auto menu = menuWidget();
            if (menu) {
                menu->setProperty("bar-active", false);
                style()->polish(menu);
            }
            break;
        }
        default:
            break;
    }
    return QMainWindow::event(event);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DontCreateNativeAncestors);
    installWindowAgent();

    qDebug() << QSqlDatabase::drivers();
    qDebug() << QSslSocket::supportsSsl() <<QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("1234");

    if (!db.open())
    {
        qDebug() << "database open error!";
        qDebug() <<  db.lastError();
    }
    else
    {
        qDebug() << "database open success!";
    }

    ui->page_5->init();
}

void MainWindow::installWindowAgent()
{
    windowAgent = new QWK::WidgetWindowAgent(this);
    windowAgent->setup(this);

    auto menuBar = [this]() {
        auto menuBar = new QMenuBar(this);
        auto dropDown = new QMenu(menuBar);
        dropDown->setIcon(QIcon(":/dropDown.png"));
        auto action1 = new QAction(QIcon(":/UserManagement.png"), "用户管理", menuBar);
        connect(action1, &QAction::triggered, [=](){
            ui->stackedWidget->setCurrentIndex(3);
            ui->toolButton_1->setChecked(false);
            ui->toolButton_2->setChecked(false);
            ui->toolButton_3->setChecked(false);
        });
        auto action2 = new QAction(QIcon(":/QuestionnaireManagement.png"), "问卷管理", menuBar);
        connect(action2, &QAction::triggered, [=](){
            ui->stackedWidget->setCurrentIndex(4);
            ui->toolButton_1->setChecked(false);
            ui->toolButton_2->setChecked(false);
            ui->toolButton_3->setChecked(false);
        });
        dropDown->addAction(action1);
        dropDown->addAction(action2);
        dropDown->addSeparator();
        menuBar->addMenu(dropDown);
        return menuBar;
    }();
    menuBar->setObjectName(QStringLiteral("win-menu-bar"));

    auto titleLabel = new QLabel();
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName(QStringLiteral("win-title-label"));
    titleLabel->setText("人机交互界面评估系统");
    QFont font("Times", 10, QFont::Bold);
    titleLabel->setFont(font);
    titleLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    auto iconButton = new QWK::WindowButton();
    iconButton->setObjectName(QStringLiteral("icon-button"));
    iconButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto minButton = new QWK::WindowButton();
    minButton->setObjectName(QStringLiteral("min-button"));
    minButton->setProperty("system-button", true);
    minButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto maxButton = new QWK::WindowButton();
    maxButton->setCheckable(true);
    maxButton->setObjectName(QStringLiteral("max-button"));
    maxButton->setProperty("system-button", true);
    maxButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto closeButton = new QWK::WindowButton();
    closeButton->setObjectName(QStringLiteral("close-button"));
    closeButton->setProperty("system-button", true);
    closeButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto windowBar = new QWK::WindowBar();
    windowBar->setIconButton(iconButton);
    windowBar->setMinButton(minButton);
    windowBar->setMaxButton(maxButton);
    windowBar->setCloseButton(closeButton);
    windowBar->setTitleLabel(titleLabel);
    windowBar->setMenuBar(menuBar);
    windowBar->setHostWidget(this);

    windowAgent->setTitleBar(windowBar);
    windowAgent->setSystemButton(QWK::WindowAgentBase::WindowIcon, iconButton);
    windowAgent->setSystemButton(QWK::WindowAgentBase::Minimize, minButton);
    windowAgent->setSystemButton(QWK::WindowAgentBase::Maximize, maxButton);
    windowAgent->setSystemButton(QWK::WindowAgentBase::Close, closeButton);
    windowAgent->setHitTestVisible(menuBar, true);

    setMenuWidget(windowBar);

    connect(windowBar, &QWK::WindowBar::minimizeRequested, this, &QWidget::showMinimized);
    connect(windowBar, &QWK::WindowBar::maximizeRequested, this, [this, maxButton](bool max) {
        if (max) {
            showMaximized();
        } else {
            showNormal();
        }
        emulateLeaveEvent(maxButton);
    });
    connect(windowBar, &QWK::WindowBar::closeRequested, this, &QWidget::close);

    QFile qss(QStringLiteral(":/light-style.qss"));
    qss.open(QIODevice::ReadOnly | QIODevice::Text);
    setStyleSheet(QString::fromUtf8(qss.readAll()));
}

void MainWindow::on_toolButton_1_clicked()
{
    ui->toolButton_1->setChecked(true);
    ui->toolButton_2->setChecked(false);
    ui->toolButton_3->setChecked(false);
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_toolButton_2_clicked()
{
    ui->toolButton_1->setChecked(false);
    ui->toolButton_2->setChecked(true);
    ui->toolButton_3->setChecked(false);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_toolButton_3_clicked()
{
    ui->toolButton_1->setChecked(false);
    ui->toolButton_2->setChecked(false);
    ui->toolButton_3->setChecked(true);
    ui->stackedWidget->setCurrentIndex(2);
}

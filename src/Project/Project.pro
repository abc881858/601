QT += core gui widgets network sql

CONFIG += c++17

include(widgetframe/widgetframe.pri)

SOURCES += \
    answerlistitem.cpp \
    configlistitem.cpp \
    evaluatewidget.cpp \
    eventchilditem.cpp \
    eventitem.cpp \
    main.cpp \
    mainwindow.cpp \
    questionitem.cpp \
    questionlistitem.cpp \
    questionnairebankmodel.cpp \
    questionnairelistitem.cpp \
    questionnairemanagementwidget.cpp \
    questiontypedialog.cpp \
    replaylistitem.cpp \
    replaywidget.cpp \
    tasklistitem.cpp \
    taskwidget.cpp \
    triggeractiondialog.cpp \
    usermanagementwidget.cpp

HEADERS += \
    answerlistitem.h \
    configlistitem.h \
    evaluatewidget.h \
    eventchilditem.h \
    eventitem.h \
    mainwindow.h \
    packet.h \
    questionitem.h \
    questionlistitem.h \
    questionnairebankmodel.h \
    questionnairelistitem.h \
    questionnairemanagementwidget.h \
    questiontypedialog.h \
    replaylistitem.h \
    replaywidget.h \
    tasklistitem.h \
    taskwidget.h \
    triggeractiondialog.h \
    usermanagementwidget.h

FORMS += \
    answerlistitem.ui \
    configlistitem.ui \
    evaluatewidget.ui \
    eventchilditem.ui \
    eventitem.ui \
    mainwindow.ui \
    questionitem.ui \
    questionlistitem.ui \
    questionnairelistitem.ui \
    questionnairemanagementwidget.ui \
    questiontypedialog.ui \
    replaylistitem.ui \
    replaywidget.ui \
    tasklistitem.ui \
    taskwidget.ui \
    triggeractiondialog.ui \
    usermanagementwidget.ui

RESOURCES += \
    res/mainwindow.qrc

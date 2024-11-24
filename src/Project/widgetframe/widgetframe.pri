INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/include/QWKCore
INCLUDEPATH += $$PWD/include/QWKWidgets

LIBS += $$PWD/lib/libQWKCore.dll.a
LIBS += $$PWD/lib/libQWKWidgets.dll.a

HEADERS += \
    $$PWD/windowbar.h \
    $$PWD/windowbar_p.h \
    $$PWD/windowbutton.h \
    $$PWD/windowbutton_p.h

SOURCES += \
    $$PWD/windowbar.cpp \
    $$PWD/windowbutton.cpp

RESOURCES += \
    $$PWD/res.qrc

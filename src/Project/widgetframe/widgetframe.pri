INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/include/QWKCore
INCLUDEPATH += $$PWD/include/QWKWidgets

# LIBS += $$PWD/lib/release/libQWKCore.dll.a
# LIBS += $$PWD/lib/release/libQWKWidgets.dll.a

LIBS += $$PWD/lib/debug/libQWKCore.dll.a
LIBS += $$PWD/lib/debug/libQWKWidgets.dll.a


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

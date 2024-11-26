DEFINES += USE_WINDOWS_MULTIMEDIA

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/include

LIBS += -lopengl32  -lGLU32 -lwinmm
LIBS += -L$$PWD/lib/ -lavutil -lavformat -lavcodec -lswscale -lswresample

HEADERS += \
    $$PWD/ffmpegplayer.h \
    $$PWD/ffmpegwidget.h

SOURCES += \
    $$PWD/ffmpegplayer.cpp \
    $$PWD/ffmpegwidget.cpp



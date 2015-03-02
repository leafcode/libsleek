#-------------------------------------------------
#
# Project created by QtCreator 2015-01-29T18:34:23
#
#-------------------------------------------------

QT += core gui widgets

TEMPLATE = lib

DEFINES += LIBSLEEK_LIBRARY
CONFIG += debug_and_release
CONFIG += build_all

CONFIG(debug, debug|release) {
    TARGET = libsleekd
} else {
    TARGET = libsleek
}

win32 {
LIBS += gdi32.lib dwmapi.lib

SOURCES += qwinwidget.cpp \
    sleekwindowclass.cpp \
    sleekborderless.cpp

HEADERS += qwinwidget.h \
    sleekwindowclass.h \
    sleekborderless.h
}

SOURCES += \
    sleekwindow.cpp

HEADERS += \
    sleekwindow.h \
    libsleek_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

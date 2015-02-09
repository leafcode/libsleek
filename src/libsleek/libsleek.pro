#-------------------------------------------------
#
# Project created by QtCreator 2015-01-29T18:34:23
#
#-------------------------------------------------

QT += core gui widgets

TARGET = libsleek
TEMPLATE = lib

DEFINES += LIBSLEEK_LIBRARY

win32 {
LIBS += gdi32.lib dwmapi.lib

SOURCES += qwinwidget.cpp

HEADERS += qwinwidget.h
}

SOURCES += \
    sleekwindow.cpp \
    sleekwindowclasssingleton.cpp \
    sleekwindowclass.cpp \
    sleekborderless.cpp

HEADERS += \
    sleekwindowclasssingleton.h \
    sleekwindowclass.h \
    sleekwindow_global.h \
    sleekwindow.h \
    sleekborderless.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

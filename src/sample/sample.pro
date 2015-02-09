#-------------------------------------------------
#
# Project created by QtCreator 2015-01-29T18:34:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sample
TEMPLATE = app


SOURCES += main.cpp\
    testwindow.cpp

HEADERS  += \
    testwindow.h

FORMS    += \
    testwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libsleek/release/ -llibsleek
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libsleek/debug/ -llibsleek
else:unix: LIBS += -L$$OUT_PWD/../libsleek/ -llibsleek

INCLUDEPATH += $$PWD/../libsleek
DEPENDPATH += $$PWD/../libsleek

RESOURCES += \
    desktop.qrc

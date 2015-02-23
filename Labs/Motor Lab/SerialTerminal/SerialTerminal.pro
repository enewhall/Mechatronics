#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T16:02:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = SerialTerminal
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    console.cpp \
    settingsdialog.cpp

HEADERS  += mainwindow.h \
    console.h \
    settingsdialog.h

FORMS    += mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    terminal.qrc

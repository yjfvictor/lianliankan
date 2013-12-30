#-------------------------------------------------
#
# Project created by QtCreator 2013-12-27T10:24:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lianliankan
TEMPLATE = app
CONFIG -= app_bundle


SOURCES += main.cpp\
        mainwindow.cpp \
    myitemmodel.cpp \
    maintableview.cpp \
    myippartlineedit.cpp \
    myipaddredit.cpp

HEADERS  += mainwindow.h \
    myitemmodel.h \
    maintableview.h \
    data.h \
    myippartlineedit.h \
    myipaddredit.h

RESOURCES += \
    resource.qrc

CODECFORTR = UTF-8
CODECFORSRC = UTF-8

TRANSLATIONS += zh_CN.ts

RC_FILE += fileicon.rc

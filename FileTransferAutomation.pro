#-------------------------------------------------
#
# Project created by QtCreator 2019-09-27T22:05:21
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FileTransferAutomation
TEMPLATE = app


SOURCES += main.cpp\
    autornamecollection.cpp \
        mainwindow.cpp \
    dragwidget.cpp \
    selectpathdialog.cpp

HEADERS  += mainwindow.h \
    autornamecollection.h \
    dragwidget.h \
    selectpathdialog.h

FORMS    += mainwindow.ui \
    dragwidget.ui \
    selectpathdialog.ui

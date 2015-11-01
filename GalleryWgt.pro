#-------------------------------------------------
#
# Project created by QtCreator 2015-10-19T23:53:25
#
#-------------------------------------------------

QT       += core gui network websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GalleryWgt
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
        listener.cpp

HEADERS  += mainwindow.h \
            listener.h

FORMS    += mainwindow.ui

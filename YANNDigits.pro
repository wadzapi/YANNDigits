#-------------------------------------------------
#
# Project created by QtCreator 2013-04-10T11:59:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YANNDigits
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imgframe.cpp \
    imagedata.cpp \
    mnistdataset.cpp \
    mnistiterator.cpp

HEADERS  += mainwindow.h \
    imgframe.h \
    imagedata.h \
    mnistdataset.h \
    mnistiterator.h

FORMS    += mainwindow.ui

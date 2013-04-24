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
    counter.cpp \
    annrecognizer.cpp

HEADERS  += mainwindow.h \
    imgframe.h \
    imagedata.h \
    mnistdataset.h \
    counter.h \
    annrecognizer.h

FORMS    += mainwindow.ui

win32: LIBS += -L$$PWD/third_party/fann/ -llibfann

INCLUDEPATH += $$PWD/third_party/fann/include
DEPENDPATH += $$PWD/third_party/fann/include

win32: PRE_TARGETDEPS += $$PWD/third_party/fann/libfann.lib


win32: LIBS += -L$$PWD/third_party/fann/ -llibdoublefann

INCLUDEPATH += $$PWD/third_party/fann/include
DEPENDPATH += $$PWD/third_party/fann/include

win32: PRE_TARGETDEPS += $$PWD/third_party/fann/libdoublefann.lib

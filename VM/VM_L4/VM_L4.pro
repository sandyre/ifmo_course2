#-------------------------------------------------
#
# Project created by QtCreator 2015-11-13T04:09:15
#
#-------------------------------------------------
CONFIG += c++11
QT       += core gui printsupport opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = VM_L3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    Interpolation.cpp \
    odem.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    Interpolation.h \
    consts.h \
    odem.h

FORMS    += mainwindow.ui

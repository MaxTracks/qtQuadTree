#-------------------------------------------------
#
# Project created by QtCreator 2015-05-11T20:03:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test2
TEMPLATE = app

QMAKE_CXXFLAGS = -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    quadtree.cpp

HEADERS  += mainwindow.h \
    node.h \
    quadtree.h

FORMS    += mainwindow.ui

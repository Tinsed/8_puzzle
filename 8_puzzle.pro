#-------------------------------------------------
#
# Project created by QtCreator 2016-09-16T23:38:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 8_puzzle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    node.cpp \
    problem.cpp \
    actionsPr.cpp \

HEADERS  += mainwindow.h \
    node.h \
    problem.h \
    state.h \
    actionsPr.h \

FORMS    += mainwindow.ui

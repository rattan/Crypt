#-------------------------------------------------
#
# Project created by QtCreator 2016-04-15T00:10:39
#
#-------------------------------------------------

QT       += core gui winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Crypt
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    des.cpp \
    aes.cpp

HEADERS  += widget.h \
    des.h \
    aes.h

FORMS    += widget.ui

CONFIG += c++11

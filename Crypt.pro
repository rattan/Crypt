#-------------------------------------------------
#
# Project created by QtCreator 2016-04-15T00:10:39
#
#-------------------------------------------------


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Crypt
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    des.cpp \
    aes.cpp \
    console.cpp \
    sender.cpp

HEADERS  += widget.h \
    des.h \
    aes.h \
    console.h \
    sender.h

FORMS    += widget.ui \
    console.ui

CONFIG += c++11 static

RESOURCES += \
    resources.qrc

RC_FILE = icon.rc

DISTFILES += \
    icon.rc

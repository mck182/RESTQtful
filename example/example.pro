QT += core network
QT -= gui

CONFIG += c++11

TARGET = rest-qt-example
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../src
LIBS += -L../src -lrestqtful

SOURCES += main.cpp \
    px500.cpp \
    pxphoto.cpp \
    pxuser.cpp

HEADERS += \
    px500.h \
    px500secrets.h \
    pxphoto.h \
    pxuser.h

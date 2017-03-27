QT += core network
QT -= gui

CONFIG += c++11

TARGET = rest-qt
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += src

TEMPLATE = app

SOURCES += main.cpp \
    src/serverbase.cpp \
    src/networkmanager.cpp \
    example/px500.cpp

HEADERS += \
    src/serverbase.h \
    src/networkmanager.h \
    example/px500.h \
    example/px500secrets.h

QT += core network
QT -= gui

CONFIG += c++11

TARGET = rest-qt
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    serverbase.cpp \
    networkmanager.cpp

HEADERS += \
    serverbase.h \
    networkmanager.h

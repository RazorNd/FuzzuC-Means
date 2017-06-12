#-------------------------------------------------
#
# Project created by QtCreator 2017-05-07T12:46:21
#
#-------------------------------------------------

QT       += testlib

TARGET = tst_distancetest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++14

TEMPLATE = app

SOURCES += tst_distancetest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

RESOURCES += \
    ../shared/images.qrc

INCLUDEPATH += $$PWD/../../src/FuzzuC-Means
DEPENDPATH += $$PWD/../../src/FuzzuC-Means

INCLUDEPATH += $$PWD/../shared

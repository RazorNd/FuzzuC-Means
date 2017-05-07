#-------------------------------------------------
#
# Project created by QtCreator 2017-05-07T12:46:21
#
#-------------------------------------------------

QT       += testlib

TARGET = tst_distancetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_distancetest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    xvector.h \
    ximage.h

RESOURCES += \
    images.qrc

INCLUDEPATH += $$PWD/../../src/FuzzuC-Means
DEPENDPATH += $$PWD/../../src/FuzzuC-Means

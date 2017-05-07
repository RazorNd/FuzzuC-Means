#-------------------------------------------------
#
# Project created by QtCreator 2017-05-06T22:53:09
#
#-------------------------------------------------

QT       -= gui

TARGET = FuzzuC-Means
TEMPLATE = lib

DEFINES += FUZZUCMEANS_LIBRARY

HEADERS += FuzzuCMeans.h \
    EntitySetIterator.h \
    EntitySetTraits.h \
    Distance.h \
    Cluster.h

unix {
    target.path = /usr/local/lib
    INSTALLS += target
}

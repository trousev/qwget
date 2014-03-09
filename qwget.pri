isEmpty(LIB_QWGET) { LIB_QWGET=YES
qwget_root = $$PWD
QT       += core
QT       += network
SOURCES += $$qwget_root/qwget.cpp
HEADERS += $$qwget_root/qwget.h

INCLUDEPATH += $$qwget_root/
}
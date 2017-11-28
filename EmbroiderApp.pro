#-------------------------------------------------
#
# Project created by QtCreator 2012-11-24T10:22:48
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = EmbroiderApp
TEMPLATE = app

INCLUDEPATH +=.
INCLUDEPATH +=/usr/include/qt4/
INCLUDEPATH +=/usr/include/qt4/Qt
INCLUDEPATH  +=/usr/include/qt4/QtCore/
INCLUDEPATH  +=/usr/include/qt4/QtGui/
INCLUDEPATH += Class/
INCLUDEPATH += control/
INCLUDEPATH += devthread/
INCLUDEPATH += ioperate/
INCLUDEPATH += serial/

SOURCES += main.cpp\
        widget.cpp \
    enterform.cpp \
    setform.cpp \
    handform.cpp \
    testform.cpp \
    manageform.cpp \
    mainmenuform.cpp \
    ioperate/ioperate.cpp \
    devthread/devicesthread.cpp \
    control/mytextedit.cpp \
    control/paintarea.cpp \
    control/selectplugin.cpp \
    serial/mserialoperate.cpp \
    Class/mfileoperate.cpp \
    serial/serialport.cpp

HEADERS  += widget.h \
    enterform.h \
    setform.h \
    handform.h \
    testform.h \
    manageform.h \
    mainmenuform.h \
    ioperate/ioperate.h \
    devthread/devicesthread.h \
    control/mytextedit.h \
    control/paintarea.h \
    control/selectplugin.h \
    serial/mserialoperate.h \
    Class/mfileoperate.h \
    Class/commonType.h \
    serial/serialport.h

FORMS    += widget.ui \
    enterform.ui \
    setform.ui \
    handform.ui \
    testform.ui \
    manageform.ui \
    mainmenuform.ui \
    selectplugin.ui

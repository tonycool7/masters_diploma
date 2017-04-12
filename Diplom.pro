#-------------------------------------------------
#
# Project created by QtCreator 2017-04-12T13:23:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Diplom
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mysqlsettings.cpp \
    postgresqlsettings.cpp

HEADERS  += mainwindow.h \
    mysqlsettings.h \
    postgresqlsettings.h

FORMS    += mainwindow.ui \
    mysqlsettings.ui \
    postgresqlsettings.ui

RESOURCES += \
    projectresource.qrc

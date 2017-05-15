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
    postgresqlsettings.cpp \
    databasemanager.cpp \
    sshmanager.cpp \
    zip.cpp \
    mysqldatabasemanager.cpp \
    postgresqldatabasemanager.cpp

HEADERS  += mainwindow.h \
    mysqlsettings.h \
    postgresqlsettings.h \
    node.h \
    databasemanager.h \
    databasecontainer.h \
    sshmanager.h \
    zip.h \
    mysqldatabasemanager.h \
    postgresqldatabasemanager.h

FORMS    += mainwindow.ui \
    mysqlsettings.ui \
    postgresqlsettings.ui \
    databasemanager.ui

RESOURCES += \
    projectresource.qrc

LIBS += -L"/usr/include/driver" -lmysqlcppconn

LIBS += -L"/usr/lib" -lssh

LIBS += -L"/usr/lib" -lpqxx

LIBS += -L"/usr/lib" -lpq


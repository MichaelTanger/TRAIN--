#-------------------------------------------------
#
# Project created by QtCreator 2016-09-07T17:33:18
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ticket_Service
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    signin.cpp \
    register.cpp \
    userpage.cpp \
    Train.cpp \
    User.cpp \
    traininfo.cpp \
    changepassword.cpp \
    Ticket.cpp \
    info_database.cpp \
    connection.cpp \
    changetrain.cpp

HEADERS  += mainwindow.h \
    register.h \
    signin.h \
    userpage.h \
    Train.h \
    User.h \
    traininfo.h \
    changepassword.h \
    connection.h \
    info_database.h \
    Ticket.h \
    changetrain.h

FORMS    += mainwindow.ui \
    signin.ui \
    register.ui \
    userpage.ui \
    traininfo.ui \
    changepassword.ui \
    changetrain.ui

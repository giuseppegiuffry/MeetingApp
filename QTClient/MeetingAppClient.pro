#-------------------------------------------------
#
# Project created by QtCreator 2019-11-05T15:19:17
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MeetingAppClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    socket.cpp \
    home.cpp \
    registration.cpp \
    login.cpp \
    del.cpp

HEADERS += \
    socket.h \
    home.h \
    registration.h \
    login.h \
    del.h

FORMS += \
    home.ui \
    registration.ui \
    login.ui \
    del.ui

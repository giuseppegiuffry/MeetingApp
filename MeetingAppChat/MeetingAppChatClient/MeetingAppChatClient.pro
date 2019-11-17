QT += core network gui sql widgets

TARGET = MeetingAppChatClient
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += debug_and_release

SOURCES += \
    clientmain.cpp \
    chatwindow.cpp \
    chatclient.cpp \
    registration.cpp \
    mainwindow.cpp

FORMS += \
    chatwindow.ui \
    registration.ui \
    mainwindow.ui

HEADERS += \
    chatwindow.h \
    chatclient.h \
    registration.h \
    mainwindow.h

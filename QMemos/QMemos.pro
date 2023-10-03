# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = QMemos

QT = core gui widgets network

HEADERS = \
   $$PWD/IniConfig.h \
   $$PWD/mainwindow.h \
   $$PWD/quickmemo.h \
   ../qmc/wrapper.h

SOURCES = \
   $$PWD/IniConfig.cpp \
   $$PWD/main.cpp \
   $$PWD/mainwindow.cpp \
   $$PWD/quickmemo.cpp \
   ../qmc/wrapper.cpp

#INCLUDEPATH = \
#    $$PWD/. \
#    $$PWD/QHotkey/HotkeyTest \
#    $$PWD/QHotkey/QHotkey \
#    $$PWD/test

#DEFINES = 

FORMS += \
    mainwindow.ui \
    quickmemo.ui

RESOURCES  = res/res.qrc


INCLUDEPATH = \
    ../qmc


include(QHotkey/qhotkey.pri)

DESTDIR=../../QMemos

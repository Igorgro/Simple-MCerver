#-------------------------------------------------
#
# Project created by QtCreator 2018-05-06T19:49:14
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simple_mcerver
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
        mainwindow.cpp \
    server_thread.cpp \
    messagequeue.cpp \
    mainwindow_gui.cpp \
    settings.cpp \
    mainwindow_slots.cpp \
    mainwindow_misc.cpp \
    operators.cpp \
    bannedplayers.cpp \
    warndialog.cpp \
    serverproperties.cpp \
    message_processing_thread.cpp \
    spawn_dialog.cpp \
    mod.cpp \
    servermods.cpp

HEADERS += \
        mainwindow.h \
    server_thread.h \
    messagequeue.h \
    settings.h \
    operators.h \
    bannedplayers.h \
    warndialog.h \
    serverproperties.h \
    message_processing_thread.h \
    spawn_dialog.h \
    mod.h \
    servermods.h

FORMS += \
    mainwindow.ui \
    warndialog.ui \
    spawn_dialog.ui

RESOURCES += \
    resources.qrc
RC_FILE = simple_mcerver.rc

LIBS += "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.17134.0\um\x86\kernel32.Lib"
LIBS += $$PWD/lib/libproperties.a
LIBS += $$PWD/lib/libquazip.a

INCLUDEPATH += $$PWD/include

CONFIG += static

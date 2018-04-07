#-------------------------------------------------
#
# Project created by QtCreator 2017-12-06T21:46:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtparanoia
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
        src/main.cc \
        src/app.cc \
        src/track.cc \
        src/audiodisk.cc \
        src/tasks/task.cc \
        src/tasks/cdinfotask.cc \
        src/tasks/paranoiatask.cc \
        src/model/tagtablemodel.cc

HEADERS += \
        inc/app.h \
        inc/track.h \
        inc/audiodisk.h \
        inc/tasks/task.h \
        inc/tasks/cdinfotask.h \
        inc/tasks/paranoiatask.h \
        inc/model/tagtablemodel.h

FORMS += \
        ui/app.ui

INCLUDEPATH += \
        inc/

OBJECTS_DIR = obj
MOC_DIR = obj
LIBS = -lcdio -lcdio_cdda -lcdio_paranoia

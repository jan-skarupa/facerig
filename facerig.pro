QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtbuild
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        src/main.cpp \
        src/ui/mainwindow.cpp \
    src/camera/camera.cpp

HEADERS += \
        src/ui/mainwindow.h \
    src/camera/camera.h

FORMS += \
        src/ui/mainwindow.ui

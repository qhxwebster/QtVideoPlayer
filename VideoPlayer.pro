#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T18:21:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets sql
CONFIG += c++11
TARGET = 01-22-VideoPlayer
TEMPLATE = app
LIBS += -lshell32

SOURCES += main.cpp\
        Widget.cpp \
    VideoWidget.cpp \
    MainSlider.cpp \
    VolumeSlider.cpp \
    ListWidget.cpp \
    BottomWidget.cpp \
    CaptureDialog.cpp \
    InCaptureWidget.cpp \
    InCaptureLabel.cpp \
    FileSystemDialog.cpp \
    FileTreeView.cpp

HEADERS  += Widget.h \
    VideoWidget.h \
    MainSlider.h \
    VolumeSlider.h \
    ListWidget.h \
    BottomWidget.h \
    CaptureDialog.h \
    InCaptureWidget.h \
    InCaptureLabel.h \
    FileSystemDialog.h \
    FileTreeView.h

FORMS    += Widget.ui

RESOURCES += \
    icon.qrc

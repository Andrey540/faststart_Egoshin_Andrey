#-------------------------------------------------
#
# Project created by QtCreator 2015-10-18T13:46:25
#
#-------------------------------------------------

QT     += core gui
CONFIG += c++11
QT     += opengl
LIBS   += -L"C:\\Qt\Tools\QtCreator\bin" -lopengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Walk3D
TEMPLATE = app


SOURCES += main.cpp \
    ui/window3d.cpp \
    nodes/coloredcube.cpp \
    gl/scenenode.cpp \
    gl/basescene.cpp \
    gameapplication.cpp \
    gl/scenecamera.cpp \
    gl/glhelper.cpp \
    ui/rotatecameracontroller.cpp \
    ui/movecameracontroller.cpp \
    scenedeserializer.cpp

HEADERS  += \
    ui/window3d.h \
    gl/scenenode.h \
    nodes/coloredcube.h \
    gl/basescene.h \
    gameapplication.h \
    gl/iscenecamera.h \
    gl/scenecamera.h \
    gl/glhelper.h \
    ui/iinputcontroller.h \
    ui/rotatecameracontroller.h \
    ui/movecameracontroller.h \
    scenedeserializer.h

FORMS    +=

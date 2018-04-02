TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += opengl

HEADERS += \
    app.h \
    item.h \
    world.h

SOURCES += main.cpp \
    app.cpp \
    item.cpp \
    world.cpp \
    imgui-SFML.cpp \
    adds\imgui.cpp \
    adds\imgui_draw.cpp \
    adds\imgui_demo.cpp



unix:!macx: LIBS += -L$$PWD/Box2D/ -lBox2D

INCLUDEPATH += $$PWD/Box2D/Box2Dh
INCLUDEPATH += $$PWD/adds
DEPENDPATH += $$PWD/Box2D/Box2Dh

unix:!macx: PRE_TARGETDEPS += $$PWD/Box2D/libBox2D.a
unix:!macx: LIBS += -L$$PWD/sfml/ -lsfml-audio
unix:!macx: LIBS += -L$$PWD/sfml/ -lsfml-graphics
unix:!macx: LIBS += -L$$PWD/sfml/ -lsfml-system
unix:!macx: LIBS += -L$$PWD/sfml/ -lsfml-window

INCLUDEPATH += $$PWD/sfml/SFML
DEPENDPATH += $$PWD/sfml/SFML

INCLUDEPATH += $$PWD/IMGUI
DEPENDPATH += $$PWD/IMGUI

unix:!macx: LIBS += -L$$PWD/Box2D/ -lBox2D

INCLUDEPATH += $$PWD/SFML
DEPENDPATH += $$PWD/SFML

unix:!macx: PRE_TARGETDEPS += $$PWD/Box2D/libBox2D.a
unix:!macx: LIBS += -L$$PWD/Box2D/ -lBox2D

INCLUDEPATH += $$PWD/Box2D/Box2Dh/Box2D
DEPENDPATH += $$PWD/Box2D/Box2Dh/Box2D

unix:!macx: PRE_TARGETDEPS += $$PWD/Box2D/libBox2D.a

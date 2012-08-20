#-------------------------------------------------
#
# Project created by QtCreator 2012-03-21T13:54:25
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = flowed
TEMPLATE = app


SOURCES += main.cpp\
        femainwindow.cpp \
    fe_flowelement.cpp \
    fe_flowelementhandle.cpp \
    fe_glwidget.cpp

HEADERS  += femainwindow.h \
    fe_flowelement.h \
    fe_flowelementhandle.h \
    fe_glwidget.h

FORMS    += femainwindow.ui

LIBS += -L./akima/src -lakima

QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp

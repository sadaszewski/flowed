# -------------------------------------------------
# Project created by QtCreator 2012-03-21T13:54:25
# -------------------------------------------------
QT += core \
    gui
    # opengl
# CONFIG += debug
TARGET = flowed
TEMPLATE = app
SOURCES += main.cpp \
    femainwindow.cpp \
    fe_flowelement.cpp \
    fe_flowelementhandle.cpp \
    # fe_glwidget.cpp \
    fe_gradientelement.cpp \
    draw_gouraud_triangle.cpp \
    qarrowcue.cpp \
    draw_item_along_bezier.cpp \
    fe_beziercurve.cpp
HEADERS += femainwindow.h \
    fe_flowelement.h \
    fe_flowelementhandle.h \
    # fe_glwidget.h \
    fe_gradientelement.h \
    fe_element.h \
    qarrowcue.h \
    fe_beziercurve.h
FORMS += femainwindow.ui
INCLUDEPATH += nn-c/
LIBS += nn-c/libnn.a \
    -lgfortran \
    -Lakima/src \
    -lakima
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp

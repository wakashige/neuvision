TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

################################################################################
## VTK
include($$PWD/../3rdparty/vtk.pri)

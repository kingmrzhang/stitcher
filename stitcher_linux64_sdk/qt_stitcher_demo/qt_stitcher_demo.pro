TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp

INCLUDEPATH += /usr/local/include/opencv
LIBS += -lopencv_core \
-lopencv_imgproc \
-lopencv_highgui \
../lib/libstitcher.so

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    ../Common/SdustStitcher/SdustStitcher.h \
    stitcher.h

SOURCES += main.cpp \
    ../Common/SdustStitcher/SdustStitcher.cpp \
    stitcher.cpp

INCLUDEPATH += /usr/local/include/opencv
LIBS += -lopencv_core \
-lopencv_imgproc \
-lopencv_highgui \
-lopencv_ml \
-lopencv_video \
-lopencv_features2d \
-lopencv_calib3d \
-lopencv_objdetect \
-lopencv_contrib \
-lopencv_legacy \
-lopencv_flann \
-lopencv_stitching \
-fopenmp
#-lstitcher


TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    readBinaryImageFiles.cpp

INCLUDEPATH += C:\\openCVBuild\\install\\include

LIBS += "C:/openCVBuild/install/x86/mingw/lib/libopencv_core310.dll.a"
LIBS += "C:/openCVBuild/install/x86/mingw/lib/libopencv_highgui310.dll.a"
LIBS += "C:/openCVBuild/install/x86/mingw/lib/libopencv_imgproc310.dll.a"
LIBS += "C:/openCVBuild/install/x86/mingw/lib/libopencv_features2d310.dll.a"
LIBS += "C:/openCVBuild/install/x86/mingw/lib/libopencv_calib3d310.dll.a"
LIBS += "C:/openCVBuild/install/x86/mingw/lib/libopencv_imgcodecs310.dll.a"

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    func1.cpp \
    hgBy4Pts.cpp \
    rotByVanPts.cpp

unix:LIBS += `pkg-config opencv --libs`

win32:INCLUDEPATH+=C:\Qt\OpenCV249MinGw\include\opencv\
                   C:\Qt\OpenCV249MinGw\include\opencv2\
                   C:\Qt\OpenCV249MinGw\include

win32:LIBS+= C:\Qt\OpenCV249MinGw\lib\libopencv_calib3d249.dll.a\
               C:\Qt\OpenCV249MinGw\lib\libopencv_contrib249.dll.a\
               C:\Qt\OpenCV249MinGw\lib\libopencv_core249.dll.a\
               C:\Qt\OpenCV249MinGw\lib\libopencv_features2d249.dll.a\
               C:\Qt\OpenCV249MinGw\lib\libopencv_flann249.dll.a\
               C:\Qt\OpenCV249MinGw\lib\libopencv_gpu249.dll.a\
               C:\Qt\OpenCV249MinGw\lib\libopencv_highgui249.dll.a\
               C:\Qt\OpenCV249MinGw\lib\libopencv_imgproc249.dll.a\
               C:\Qt\OpenCV249MinGw\lib\libopencv_legacy249.dll.a\
               C:\Qt\OpenCV249MinGw\lib\libopencv_ml249.dll.a\
               C:\Qt\OpenCV249MinGw\lib\libopencv_nonfree249.dll.a\
               C:\Qt\OpenCV249MinGw\lib\libopencv_objdetect249.dll.a\
               C:\Qt\OpenCV249MinGw\lib\libopencv_ocl249.dll.a\
               C:\Qt\OpenCV249MinGw\lib\libopencv_video249.dll.a\

HEADERS += \
    func1.h \
    hgBy4Pts.h \
    rotByVanPts.h



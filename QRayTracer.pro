QT -= gui
CONFIG += c++11 console
CONFIG -= app_bundle
SOURCES += \
    src/plane.cpp \
    src/body.cpp \
    src/camera.cpp \
    src/computation.cpp \
    src/material.cpp \
    src/light.cpp \
    src/intersection.cpp \
    src/sphere.cpp \
    src/ray.cpp \
    src/matrix.cpp \
    src/canvas.cpp \
    src/main.cpp \
    src/vector.cpp \
    src/world.cpp
HEADERS += \
    include/body.h \
    include/camera.h \
    include/computation.h \
    include/canvas.h \
    include/color.h \
    include/vector.h \
    include/matrix.h \
    include/ray.h \
    include/sphere.h \
    include/intersection.h \
    include/light.h \
    include/material.h \
    include/world.h \
    include/plane.h
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

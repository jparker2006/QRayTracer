QT -= gui
CONFIG += c++11 console
CONFIG -= app_bundle
SOURCES += \
    src/bodies/smoothtriangle.cpp \
    src/misc/bounds.cpp \
    src/misc/parser.cpp \
#    src/bodies/group.cpp \
    src/bodies/cone.cpp \
    src/bodies/cylinder.cpp \
    src/bodies/cube.cpp \
    src/textile/pattern.cpp \
    src/bodies/plane.cpp \
    src/bodies/body.cpp \
    src/render/camera.cpp \
    src/misc/computation.cpp \
    src/textile/material.cpp \
    src/render/light.cpp \
    src/ray/intersection.cpp \
    src/bodies/sphere.cpp \
    src/ray/ray.cpp \
    src/math/matrix.cpp \
    src/render/canvas.cpp \
    src/render/main.cpp \
    src/math/vector.cpp \
    src/render/world.cpp \
    src/bodies/triangle.cpp \
    src/misc/thread.cpp
HEADERS += \
    include/misc/bounds.h \
#    include/bodies/group.h \
    include/bodies/cone.h \
    include/bodies/cylinder.h \
    include/bodies/cube.h \
    include/bodies/body.h \
    include/render/camera.h \
    include/misc/computation.h \
    include/render/canvas.h \
    include/textile/color.h \
    include/math/vector.h \
    include/math/matrix.h \
    include/ray/ray.h \
    include/bodies/sphere.h \
    include/ray/intersection.h \
    include/render/light.h \
    include/textile/material.h \
    include/render/world.h \
    include/bodies/plane.h \
    include/textile/pattern.h \
    include/bodies/triangle.h \
    include/misc/parser.h \
    include/misc/thread.h \
    include/bodies/smoothtriangle.h
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

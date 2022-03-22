QT -= gui
CONFIG += c++11 console
CONFIG -= app_bundle
SOURCES += \
    src/matrix.cpp \
    src/canvas.cpp \
    src/main.cpp \
    src/vector.cpp
HEADERS += \
    include/canvas.h \
    include/color.h \
    include/vector.h \
    include/matrix.h
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

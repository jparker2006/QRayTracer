QT -= gui
CONFIG += c++11 console
CONFIG -= app_bundle
SOURCES += \
    src/canvas.cpp \
    src/main.cpp \
    src/vector.cpp
HEADERS += \
    include/canvas.h \
    include/vector.h
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    httpdownloader.cpp
LIBS += -lcurl -lgumbo

HEADERS += \
    httpdownloader.h


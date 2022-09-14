TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ga.c \
        nn.c \
        show.c \
        test.c \
        utils.c

HEADERS += \
    ga.h \
    nn.h \
    show.h \
    utils.h

LIBS += -lSDL2

DISTFILES += \
    Makefile

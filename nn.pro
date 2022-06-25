TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
        presenter.c

HEADERS += \
    nn.h \
    presenter.h

LIBS += -lSDL2

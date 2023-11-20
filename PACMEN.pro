QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    colorghosts.cpp \
    game.cpp \
    gameobject.cpp \
    ghost.cpp \
    main.cpp \
    mainwindow.cpp \
    map_generator.cpp \
    pacman.cpp

HEADERS += \
    game.h \
    gameobject.h \
    ghost.h \
    imoveable.h \
    mainwindow.h \
    options.h \
    pacman.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

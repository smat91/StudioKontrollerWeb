QT += network

CONFIG += c++11 console

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += src/main.cpp \
    src/requestmapper.cpp \
    src/datatemplatecontrollerTouchPanel.cpp \
    src/datatemplatecontrollerMainSite.cpp \
    src/gpiocontroller.cpp \
    src/webguiinputcontroller.cpp

DISTFILES += \
    etc/docroot/files/WebGuiStyleSheet.css \
    etc/docroot/files/MainSite.html \
    etc/docroot/files/TouchPanel.html \
    etc/WebApp.ini

HEADERS += \
    src/customdatatypes.h \
    src/requestmapper.h \
    src/datatemplatecontrollerTouchPanel.h \
    src/datatemplatecontrollerMainSite.h \
    src/gpiocontroller.h \
    src/webguiinputcontroller.h

# includes
include(../StudioKontrollerWeb/QtWebApp/httpserver/httpserver.pri)
include(../StudioKontrollerWeb/QtWebApp/templateengine/templateengine.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../pigpio-master/release/ -lpigpiod_if2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../pigpio-master/debug/ -lpigpiod_if2
else:unix: LIBS += -L$$PWD/../pigpio-master/ -lpigpiod_if2

INCLUDEPATH += $$PWD/../pigpio-master
DEPENDPATH += $$PWD/../pigpio-master

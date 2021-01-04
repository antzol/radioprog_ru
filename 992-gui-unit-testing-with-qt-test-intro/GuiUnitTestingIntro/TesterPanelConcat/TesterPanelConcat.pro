#-------------------------------------------------
#
# Project created by QtCreator 2017-12-21T11:03:29
#
#-------------------------------------------------

QT += widgets testlib

TARGET = TestPanelConcat
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=  ../WidgetsLib


CONFIG( debug, debug|release ) {
    LIBSUFFIX = d
    win32:LIBS += -L../WidgetsLib/debug -lWidgetsLib
    win32:PRE_TARGETDEPS += ../WidgetsLib/debug/libWidgetsLib.a
} else {
    LIBSUFFIX =
    win32:LIBS += -L../WidgetsLib/release
    win32:PRE_TARGETDEPS += ../WidgetsLib/release/libWidgetsLib.a
}
unix:LIBS += -L ../WidgetsLib
unix:PRE_TARGETDEPS += ../WidgetsLib/WidgetsLib$${LIBSUFFIX}.a

SOURCES += \
        TestPanelConcat.cpp 

DEFINES += SRCDIR=\\\"$$PWD/\\\"

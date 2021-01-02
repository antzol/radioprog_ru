QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testcalculator.cpp

HEADERS += \
    calculator.h \
    tst_testcalculator.h

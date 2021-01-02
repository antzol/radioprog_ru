#ifndef TST_TESTCALCULATOR_H
#define TST_TESTCALCULATOR_H

#include "calculator.h"

#include <QtTest>

class TestCalculator: public QObject
{
    Q_OBJECT

private slots:
    // -- setup/cleanup --
    void init();

    // -- tests --
    void testConstructor();
    void testSum();

private:
    const int A0 = 0;
    const int B0 = 0;

private:
    Calculator mCalc;
};

#endif // TST_TESTCALCULATOR_H

/****************************************************************************
**
** Copyright (C) 2022 Dinu SV.
**
** This file is part of Livekeys Application.
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
****************************************************************************/

#ifndef MLNODETEST_H
#define MLNODETEST_H

#include <QObject>
#include "testrunner.h"
#include "live/mlnode.h"

class MLNodeTest : public QObject{

    Q_OBJECT
    Q_TEST_RUNNER_SUITE

public:
    MLNodeTest(QObject* parent = 0);
    ~MLNodeTest(){}

private slots:
    void initTestCase();
    void constructorTest();
    void constructorFromInitializerListTest();
    void assignmentTest();
    void accessOperatorTest();
    void base64ToBytesTest();
    void iteratorTest();
    void constIteratorTest();
};

#endif // MLNODETEST_H

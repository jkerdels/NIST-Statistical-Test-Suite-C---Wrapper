/* 
 * File:   RunsTest.h
 * Author: jk
 *
 * Created on 15. August 2010, 16:07
 */

#ifndef RUNSTEST_H
#define	RUNSTEST_H

#include "AbstractTest.h"

class RunsTest : public AbstractTest
{
public:
    RunsTest();
    ~RunsTest();

    double runTest();

private:

};

#endif	/* RUNSTEST_H */


/* 
 * File:   RandomExcursionsTest.h
 * Author: jk
 *
 * Created on 14. Dezember 2010, 00:25
 */

#ifndef RANDOMEXCURSIONSTEST_H
#define	RANDOMEXCURSIONSTEST_H

#include <inttypes.h>
#include "AbstractTest.h"

class RandomExcursionsTest : public AbstractTest
{
public:
    RandomExcursionsTest();
    ~RandomExcursionsTest();

    double runTest();

    bool testWasApplicable();

private:

    bool testOk;

	const char* getTestName() {return "RndExc";}

};

#endif	/* RANDOMEXCURSIONSTEST_H */


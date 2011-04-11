/* 
 * File:   RandomExcursionVariantTest.h
 * Author: jk
 *
 * Created on 14. Dezember 2010, 01:00
 */

#ifndef RANDOMEXCURSIONVARIANTTEST_H
#define	RANDOMEXCURSIONVARIANTTEST_H

#include <inttypes.h>
#include "AbstractTest.h"

class RandomExcursionVariantTest : public AbstractTest
{
public:
    RandomExcursionVariantTest();
    ~RandomExcursionVariantTest();

    double runTest();

    bool testWasApplicable();

	const char* getTestName() {return "RndExcVar";}

private:

    bool testOk;

};

#endif	/* RANDOMEXCURSIONVARIANTTEST_H */


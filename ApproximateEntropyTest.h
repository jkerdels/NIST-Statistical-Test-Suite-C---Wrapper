/* 
 * File:   ApproximateEntropyTest.h
 * Author: jk
 *
 * Created on 13. Dezember 2010, 23:46
 */

#ifndef APPROXIMATEENTROPYTEST_H
#define	APPROXIMATEENTROPYTEST_H

#include <inttypes.h>

#include "AbstractTest.h"

class ApproximateEntropyTest : public AbstractTest
{
public:
    ApproximateEntropyTest(int blockSize = 10);
    ~ApproximateEntropyTest();

    void setBlockSize(int blockSize);
    int getBlockSize();

    double runTest();

	const char* getTestName() {return "ApproxEnt";}

private:

    int m;

};

#endif	/* APPROXIMATEENTROPYTEST_H */


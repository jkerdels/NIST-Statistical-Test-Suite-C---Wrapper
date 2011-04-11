/* 
 * File:   LinearComplexityTest.h
 * Author: jk
 *
 * Created on 13. Dezember 2010, 22:27
 */

#ifndef LINEARCOMPLEXITYTEST_H
#define	LINEARCOMPLEXITYTEST_H

#include <inttypes.h>
#include "AbstractTest.h"

class LinearComplexityTest : public AbstractTest
{
public:
    LinearComplexityTest(bool _autoBlockSize = true, int blockSize = 500);
    ~LinearComplexityTest();

    void setAutoBlockSize(bool enable);
    bool getAutoBlockSize();

    void setBlockSize(int _M);
    int getBlockSize();

    double runTest();

	const char* getTestName() {return "LinCompl";}

private:
    bool autoBlockSize;
    int  M;

};

#endif	/* LINEARCOMPLEXITYTEST_H */


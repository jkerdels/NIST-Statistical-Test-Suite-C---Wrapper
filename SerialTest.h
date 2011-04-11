/* 
 * File:   SerialTest.h
 * Author: jk
 *
 * Created on 13. Dezember 2010, 23:08
 */

#ifndef SERIALTEST_H
#define	SERIALTEST_H

#include <inttypes.h>
#include "AbstractTest.h"

class SerialTest : public AbstractTest
{
public:
    SerialTest(int blockSize = 16);
    ~SerialTest();

    void setBlockSize(int blockSize);
    int  getBlockSize();

    double runTest();

	const char* getTestName() {return "Serial";}

private:
    int m;

    double psi2(int m, int n);

};

#endif	/* SERIALTEST_H */


/* 
 * File:   CumulativeSumsTest.h
 * Author: jk
 *
 * Created on 14. Dezember 2010, 00:01
 */

#ifndef CUMULATIVESUMSTEST_H
#define	CUMULATIVESUMSTEST_H

#include <inttypes.h>
#include "AbstractTest.h"

class CumulativeSumsTest : public AbstractTest
{
public:
    CumulativeSumsTest(int _mode = 0);
    ~CumulativeSumsTest();

    void setMode(int _mode);
    int getMode();

    double runTest();

	const char* getTestName() {return "CumulativeSums";}

private:
    int mode;

};

#endif	/* CUMULATIVESUMSTEST_H */


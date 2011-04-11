/* 
 * File:   FrequencyTest.h
 * Author: jk
 *
 * Created on 15. August 2010, 00:08
 */

#ifndef FREQUENCYTEST_H
#define	FREQUENCYTEST_H

#include "AbstractTest.h"

class FrequencyTest : public AbstractTest
{
public:
    FrequencyTest();
    ~FrequencyTest();

    double runTest();

	const char* getTestName() {return "Frequency";}

private:

};

#endif	/* FREQUENCYTEST_H */


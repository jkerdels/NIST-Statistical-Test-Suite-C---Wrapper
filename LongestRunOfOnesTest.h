/* 
 * File:   LongestRunOfOnesTest.h
 * Author: jk
 *
 * Created on 15. August 2010, 17:13
 */

#ifndef LONGESTRUNOFONESTEST_H
#define	LONGESTRUNOFONESTEST_H

#include "AbstractTest.h"

class LongestRunOfOnesTest : public AbstractTest
{
public:
    LongestRunOfOnesTest();
    ~LongestRunOfOnesTest();

    double runTest();

	const char* getTestName() {return "LongRunOfOnes";}

private:

};

#endif	/* LONGESTRUNOFONESTEST_H */


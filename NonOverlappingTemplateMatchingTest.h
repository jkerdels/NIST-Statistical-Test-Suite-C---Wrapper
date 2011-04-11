/* 
 * File:   NonOverlappingTemplateMatchingTest.h
 * Author: jk
 *
 * Created on 16. August 2010, 20:20
 */

#ifndef NONOVERLAPPINGTEMPLATEMATCHINGTEST_H
#define	NONOVERLAPPINGTEMPLATEMATCHINGTEST_H

#include <inttypes.h>

#include "AbstractTest.h"

class NonOverlappingTemplateMatchingTest : public AbstractTest
{

    static const uint32_t MAXNUMOFTEMPLATES = 148;

public:
    NonOverlappingTemplateMatchingTest();
    ~NonOverlappingTemplateMatchingTest();

    void setTemplateLength(int32_t length);
    int32_t getTemplateLength();

    double runTest();

	bool resultVectorNeeded() {return true;}

	const char* getTestName() {return "NonOvTemplMatch";}

private:

    int32_t m;

};

#endif	/* NONOVERLAPPINGTEMPLATEMATCHINGTEST_H */


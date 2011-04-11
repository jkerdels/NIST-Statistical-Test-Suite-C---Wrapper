/* 
 * File:   OverlappingTemplateMatchingTest.h
 * Author: jk
 *
 * Created on 16. August 2010, 22:00
 */

#ifndef OVERLAPPINGTEMPLATEMATCHINGTEST_H
#define	OVERLAPPINGTEMPLATEMATCHINGTEST_H

#include <inttypes.h>

#include "AbstractTest.h"

class OverlappingTemplateMatchingTest : public AbstractTest
{
public:
    OverlappingTemplateMatchingTest();
    ~OverlappingTemplateMatchingTest();

    void setTemplateLength(int32_t length);
    int32_t getTemplateLength();

    double runTest();

private:

    double Pr(int u, double eta);

    int32_t m;

	const char* getTestName() {return "OvTemplMatch";}

};

#endif	/* OVERLAPPINGTEMPLATEMATCHINGTEST_H */


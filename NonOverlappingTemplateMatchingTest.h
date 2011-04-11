/* 
 * File:   NonOverlappingTemplateMatchingTest.h
 * Author: jk
 *
 * Created on 16. August 2010, 20:20
 */

#ifndef NONOVERLAPPINGTEMPLATEMATCHINGTEST_H
#define	NONOVERLAPPINGTEMPLATEMATCHINGTEST_H

#include <inttypes.h>
#include <vector>

using namespace std;

#include "AbstractTest.h"

class NonOverlappingTemplateMatchingTest : public AbstractTest
{

    static const uint32_t MAXNUMOFTEMPLATES = 148;

public:
    NonOverlappingTemplateMatchingTest(vector<double> *_pValues);
    ~NonOverlappingTemplateMatchingTest();

    void setTemplateLength(int32_t length);
    int32_t getTemplateLength();
    void setResultVector(vector<double> *_pValues);
    vector<double>* getResultVector();

    double runTest();

private:

    int32_t m;
    vector<double> *pValues;

};

#endif	/* NONOVERLAPPINGTEMPLATEMATCHINGTEST_H */


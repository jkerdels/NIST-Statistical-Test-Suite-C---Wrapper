/* 
 * File:   main.cpp
 * Author: jk
 *
 * Created on 14. August 2010, 23:53
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

#include <inttypes.h>
#include <typeinfo>

#include "FrequencyTest.h"
#include "BlockFrequencyTest.h"
#include "RunsTest.h"
#include "LongestRunOfOnesTest.h"
#include "RankTest.h"
#include "DiscreteFourierTransformTest.h"
#include "NonOverlappingTemplateMatchingTest.h"
#include "OverlappingTemplateMatchingTest.h"
#include "MaurersTest.h"
#include "LinearComplexityTest.h"
#include "SerialTest.h"
#include "ApproximateEntropyTest.h"
#include "CumulativeSumsTest.h"
#include "RandomExcursionsTest.h"
#include "RandomExcursionVariantTest.h"

static const uint32_t TestDataSize = 125000;
static const uint32_t NumberOfTrials = 100;
static const double   Alpha = 0.01;

int main(int argc, char** argv)
{

    srand( time(0) );
    uint8_t *testData = new uint8_t[TestDataSize];

    uint32_t nrOfFails = 0;

    uint32_t i,j;

    printf("\n----------\n");

    //vector<double> results;
    RandomExcursionVariantTest curTest;


    nrOfFails = 0;
    printf("Test of %s:\n",typeid(curTest).name());

    int realNrOfTrials = 0;

    for (j = 0; j < NumberOfTrials; ++j) {

        printf("Trial %i\n",j);

        
        for (i = 0; i < TestDataSize; ++i)
            testData[i] = rand();
        

        curTest.setData(testData,TestDataSize);

        double pVal = curTest.runTest();

        realNrOfTrials++;

        if ((pVal < Alpha) && (curTest.testWasApplicable()))
            ++nrOfFails;

    }

    printf("\nNumber of fails: %u\n",nrOfFails);
    printf("Expected number of fails: %f\n",(double)(realNrOfTrials) * Alpha);
    printf("Number of runs per trial: %f\n",(double)(realNrOfTrials) / (double)(NumberOfTrials));

    printf("\n----------\n");

    
    delete[] testData;

    return 0;
}


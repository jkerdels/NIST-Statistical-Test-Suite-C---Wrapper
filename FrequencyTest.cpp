/*
 * File:   FrequencyTest.cpp
 * Author: jk
 *
 * Created on 15. August 2010, 00:08
 */

#include <cmath>
#include <cstdio>

using namespace std;

#include "FrequencyTest.h"

FrequencyTest::FrequencyTest() :
    AbstractTest()
{
}

FrequencyTest::~FrequencyTest()
{
}

double FrequencyTest::runTest()
{
/*
 // original code from NIST:

void
Frequency(int n)
{
	int		i;
	double	f, s_obs, p_value, sum, sqrt2 = 1.41421356237309504880;

	sum = 0.0;
	for ( i=0; i<n; i++ )
		sum += 2*(int)epsilon[i]-1;
	s_obs = fabs(sum)/sqrt(n);
	f = s_obs/sqrt2;
	p_value = erfc(f);

...
}

 */

    seekPos(0);
    uint64_t nob = getNrOfBits();
    if (nob < 100) {
        fprintf(stderr,"FrequencyTest::runTest(): Data should contain at least 100 Bits!\n");
        return 0.0;
    }

    const double sqrt2 = 1.41421356237309504880;

    uint64_t i;
    double sum = 0.0;
    seekPos(0);
    for (i = 0; i < nob; ++i) {
        sum += (double)((2 * getNextBit()) - 1);
    }

    double s_obs = fabs(sum) / sqrt((double)(nob));
    double f = s_obs / sqrt2;

    double p_value = erfc(f);

    return p_value;
}

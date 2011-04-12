/*
 * File:   RunsTest.cpp
 * Author: jk
 *
 * Created on 15. August 2010, 16:07
 */

#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

#include "RunsTest.h"
#include "Cephes.h"

RunsTest::RunsTest() :
    AbstractTest()
{
}


RunsTest::~RunsTest()
{
}

double RunsTest::runTest()
{
/*
 original code:

 	int		S, k;
	double	pi, V, erfc_arg, p_value;

	S = 0;
	for ( k=0; k<n; k++ )
		if ( epsilon[k] )
			S++;
	pi = (double)S / (double)n;

	if ( fabs(pi - 0.5) > (2.0 / sqrt(n)) ) {
		fprintf(stats[TEST_RUNS], "\t\t\t\tRUNS TEST\n");
		fprintf(stats[TEST_RUNS], "\t\t------------------------------------------\n");
		fprintf(stats[TEST_RUNS], "\t\tPI ESTIMATOR CRITERIA NOT MET! PI = %f\n", pi);
		p_value = 0.0;
	}
	else {

		V = 1;
		for ( k=1; k<n; k++ )
			if ( epsilon[k] != epsilon[k-1] )
				V++;

		erfc_arg = fabs(V - 2.0 * n * pi * (1-pi)) / (2.0 * pi * (1-pi) * sqrt(2*n));
		p_value = erfc(erfc_arg);

		fprintf(stats[TEST_RUNS], "\t\t\t\tRUNS TEST\n");
		fprintf(stats[TEST_RUNS], "\t\t------------------------------------------\n");
		fprintf(stats[TEST_RUNS], "\t\tCOMPUTATIONAL INFORMATION:\n");
		fprintf(stats[TEST_RUNS], "\t\t------------------------------------------\n");
		fprintf(stats[TEST_RUNS], "\t\t(a) Pi                        = %f\n", pi);
		fprintf(stats[TEST_RUNS], "\t\t(b) V_n_obs (Total # of runs) = %d\n", (int)V);
		fprintf(stats[TEST_RUNS], "\t\t(c) V_n_obs - 2 n pi (1-pi)\n");
		fprintf(stats[TEST_RUNS], "\t\t    -----------------------   = %f\n", erfc_arg);
		fprintf(stats[TEST_RUNS], "\t\t      2 sqrt(2n) pi (1-pi)\n");
		fprintf(stats[TEST_RUNS], "\t\t------------------------------------------\n");
		if ( isNegative(p_value) || isGreaterThanOne(p_value) )
			fprintf(stats[TEST_RUNS], "WARNING:  P_VALUE IS OUT OF RANGE.\n");

		fprintf(stats[TEST_RUNS], "%s\t\tp_value = %f\n\n", p_value < ALPHA ? "FAILURE" : "SUCCESS", p_value); fflush(stats[TEST_RUNS]);
	}

	fprintf(results[TEST_RUNS], "%f\n", p_value); fflush(results[TEST_RUNS]);
 */
    seekPos(0);
    uint64_t nob = getNrOfBits();
    if (nob < 100) {
        fprintf(stderr,"RunsTest::runTest(): Data should contain at least 100 Bits!\n");
        return 0.0;
    }

    uint64_t S,k;
    double pi, V, erfc_arg, p_value;

    S = 0;
    seekPos(0);
    for (k = 0; k < nob; ++k)
        S += getNextBit();

    pi = (double)(S) / (double)(nob);

    if ( fabs(pi - 0.5) > (2.0 / sqrt((double)(nob))) ) {
        p_value = 0.0;
        return p_value;
    }

    V = 1.0;
    seekPos(0);
    int8_t lastBit = getNextBit();
    for (k = 1; k < nob; ++k){
        int8_t curBit = getNextBit();
        if (curBit != lastBit)
            ++V;
        lastBit = curBit;
    }
    erfc_arg = fabs(V - 2.0 * (double)(nob) * pi * (1.0 - pi)) /
               (2.0 * pi * (1.0 - pi) * sqrt((double)(2*nob)));
    p_value = erfc(erfc_arg);

    return p_value;
}


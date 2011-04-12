/*
 * File:   RandomExcursionVariantTest.cpp
 * Author: jk
 *
 * Created on 14. Dezember 2010, 01:00
 */
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

#include "Cephes.h"
#include "Tools.h"

#include "RandomExcursionVariantTest.h"

RandomExcursionVariantTest::RandomExcursionVariantTest() :
    AbstractTest(),
    testOk(false)
{
}

RandomExcursionVariantTest::~RandomExcursionVariantTest()
{
}

bool RandomExcursionVariantTest::testWasApplicable()
{
    return testOk;
}


double RandomExcursionVariantTest::runTest()
{
/* original code:
void
RandomExcursionsVariant(int n)
{
	int		i, p, J, x, constraint, count, *S_k;
	int		stateX[18] = { -9, -8, -7, -6, -5, -4, -3, -2, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	double	p_value;

	if ( (S_k = (int *)calloc(n, sizeof(int))) == NULL ) {
		fprintf(stats[TEST_RND_EXCURSION_VAR], "\t\tRANDOM EXCURSIONS VARIANT: Insufficent memory allocated.\n");
		return;
	}
	J = 0;
	S_k[0] = 2*(int)epsilon[0] - 1;
	for ( i=1; i<n; i++ ) {
		S_k[i] = S_k[i-1] + 2*epsilon[i] - 1;
		if ( S_k[i] == 0 )
			J++;
	}
	if ( S_k[n-1] != 0 )
		J++;

	fprintf(stats[TEST_RND_EXCURSION_VAR], "\t\t\tRANDOM EXCURSIONS VARIANT TEST\n");
	fprintf(stats[TEST_RND_EXCURSION_VAR], "\t\t--------------------------------------------\n");
	fprintf(stats[TEST_RND_EXCURSION_VAR], "\t\tCOMPUTATIONAL INFORMATION:\n");
	fprintf(stats[TEST_RND_EXCURSION_VAR], "\t\t--------------------------------------------\n");
	fprintf(stats[TEST_RND_EXCURSION_VAR], "\t\t(a) Number Of Cycles (J) = %d\n", J);
	fprintf(stats[TEST_RND_EXCURSION_VAR], "\t\t(b) Sequence Length (n)  = %d\n", n);
	fprintf(stats[TEST_RND_EXCURSION_VAR], "\t\t--------------------------------------------\n");

	constraint = (int)MAX(0.005*pow(n, 0.5), 500);
	if (J < constraint) {
		fprintf(stats[TEST_RND_EXCURSION_VAR], "\n\t\tWARNING:  TEST NOT APPLICABLE.  THERE ARE AN\n");
		fprintf(stats[TEST_RND_EXCURSION_VAR], "\t\t\t  INSUFFICIENT NUMBER OF CYCLES.\n");
		fprintf(stats[TEST_RND_EXCURSION_VAR], "\t\t---------------------------------------------\n");
		for ( i=0; i<18; i++ )
			fprintf(results[TEST_RND_EXCURSION_VAR], "%f\n", 0.0);
	}
	else {
		for ( p=0; p<=17; p++ ) {
			x = stateX[p];
			count = 0;
			for ( i=0; i<n; i++ )
				if ( S_k[i] == x )
					count++;
			p_value = erfc(fabs(count-J)/(sqrt(2.0*J*(4.0*fabs(x)-2))));

			if ( isNegative(p_value) || isGreaterThanOne(p_value) )
				fprintf(stats[TEST_RND_EXCURSION_VAR], "\t\t(b) WARNING: P_VALUE IS OUT OF RANGE.\n");
			fprintf(stats[TEST_RND_EXCURSION_VAR], "%s\t\t", p_value < ALPHA ? "FAILURE" : "SUCCESS");
			fprintf(stats[TEST_RND_EXCURSION_VAR], "(x = %2d) Total visits = %4d; p-value = %f\n", x, count, p_value);
			fprintf(results[TEST_RND_EXCURSION_VAR], "%f\n", p_value); fflush(results[TEST_RND_EXCURSION_VAR]);
		}
	}
	fprintf(stats[TEST_RND_EXCURSION_VAR], "\n"); fflush(stats[TEST_RND_EXCURSION_VAR]);
	free(S_k);
}
 */
    testOk = true;
    seekPos(0);

    uint64_t nob = getNrOfBits();
    if (nob < 1000000) {
        fprintf(stderr,"RandomExcursionVariantTest::runTest(): "
                       "Data should contain at least 1.000.000 Bits!\n");
        return 0.0;
    }

    int		i, p, J, x, constraint, count, *S_k;
    int		stateX[18] = { -9, -8, -7, -6, -5, -4, -3, -2, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    double	p_value, min_p_value;

    if ( (S_k = (int *)calloc(nob, sizeof(int))) == 0 ) {
        fprintf(stderr,"RandomExcursionVariantTest::runTest(): "
                       "Insufficent memory allocated.\n");
        return 0.0;
    }
    J = 0;
    S_k[0] = 2*(int)getBit(0) - 1;
    for ( i=1; i<(int)nob; i++ ) {
            S_k[i] = S_k[i-1] + 2*getBit(i) - 1;
            if ( S_k[i] == 0 )
                    J++;
    }
    if ( S_k[nob-1] != 0 )
            J++;

    constraint = (int)Tools::MAX(0.005*pow(nob, 0.5), 500.0);
    min_p_value = 0.0;
    if (J < constraint) {
        fprintf(stderr,"RandomExcursionsTest::runTest(): "
                       "WARNING: TEST NOT APPLICABLE.  THERE ARE AN INSUFFICIENT NUMBER OF CYCLES.\n");
        testOk = false;
    } else {
        for ( p=0; p<=17; p++ ) {
            x = stateX[p];
            count = 0;
            for ( i=0; i<(int)nob; i++ )
                if ( S_k[i] == x )
                    count++;
            p_value = erfc(fabs(count-J)/(sqrt(2.0*J*(4.0*fabs(x)-2))));
            if (p == 0)
                min_p_value = p_value;
            else
                min_p_value = Tools::MIN(min_p_value,p_value);
        }
    }
    free(S_k);

    return min_p_value;
}


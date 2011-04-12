/*
 * File:   DiscreteFourierTransformTest.cpp
 * Author: jk
 *
 * Created on 15. August 2010, 19:35
 */

#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

#include "DiscreteFourierTransformTest.h"

extern "C" {
    void  __ogg_fdrffti(int n, double *wsave, int *ifac);
    void  __ogg_fdrfftf(int n, double *X, double *wsave, int *ifac);
}

DiscreteFourierTransformTest::DiscreteFourierTransformTest() :
    AbstractTest()
{
}

DiscreteFourierTransformTest::~DiscreteFourierTransformTest()
{
}

double DiscreteFourierTransformTest::runTest()
{
/* original code:
 	double	p_value, upperBound, percentile, N_l, N_o, d, *m, *X, *wsave;
	int		i, count, ifac[15];

	if ( ((X = (double*) calloc(n,sizeof(double))) == NULL) ||
		 ((wsave = (double *)calloc(2*n,sizeof(double))) == NULL) ||
		 ((m = (double*)calloc(n/2+1, sizeof(double))) == NULL) ) {
			fprintf(stats[7],"\t\tUnable to allocate working arrays for the DFT.\n");
			if( X == NULL )
				free(X);
			if( wsave == NULL )
				free(wsave);
			if( m == NULL )
				free(m);
			return;
	}
	for ( i=0; i<n; i++ )
		X[i] = 2*(int)epsilon[i] - 1;

	__ogg_fdrffti(n, wsave, ifac);		// INITIALIZE WORK ARRAYS
	__ogg_fdrfftf(n, X, wsave, ifac);	// APPLY FORWARD FFT

	m[0] = sqrt(X[0]*X[0]);	    // COMPUTE MAGNITUDE

	for ( i=0; i<n/2; i++ )
		m[i+1] = sqrt(pow(X[2*i+1],2)+pow(X[2*i+2],2));
	count = 0;				       // CONFIDENCE INTERVAL
	upperBound = sqrt(2.995732274*n);
	for ( i=0; i<n/2; i++ )
		if ( m[i] < upperBound )
			count++;
	percentile = (double)count/(n/2)*100;
	N_l = (double) count;       // number of peaks less than h = sqrt(3*n)
	N_o = (double) 0.95*n/2.0;
	d = (N_l - N_o)/sqrt(n/4.0*0.95*0.05);
	p_value = erfc(fabs(d)/sqrt(2.0));

	fprintf(stats[TEST_FFT], "\t\t\t\tFFT TEST\n");
	fprintf(stats[TEST_FFT], "\t\t-------------------------------------------\n");
	fprintf(stats[TEST_FFT], "\t\tCOMPUTATIONAL INFORMATION:\n");
	fprintf(stats[TEST_FFT], "\t\t-------------------------------------------\n");
	fprintf(stats[TEST_FFT], "\t\t(a) Percentile = %f\n", percentile);
	fprintf(stats[TEST_FFT], "\t\t(b) N_l        = %f\n", N_l);
	fprintf(stats[TEST_FFT], "\t\t(c) N_o        = %f\n", N_o);
	fprintf(stats[TEST_FFT], "\t\t(d) d          = %f\n", d);
	fprintf(stats[TEST_FFT], "\t\t-------------------------------------------\n");

	fprintf(stats[TEST_FFT], "%s\t\tp_value = %f\n\n", p_value < ALPHA ? "FAILURE" : "SUCCESS", p_value);
	fprintf(results[TEST_FFT], "%f\n", p_value);

	free(X);
	free(wsave);
	free(m);

 */

    seekPos(0);
    uint64_t nob = getNrOfBits();
    if (nob < 1000) {
        fprintf(stderr,"DiscreteFourierTransformTest::runTest(): Data should contain at least 1000 Bits!\n");
        return 0.0;
    }

    double p_value, upperBound, percentile, N_l, N_o, d, *m, *X, *wsave;
    wsave = NULL;
    int64_t i, count;
    int ifac[15];

    if ( ((X     = (double*)calloc(        nob, sizeof(double))) == NULL) ||
         ((wsave = (double*)calloc(      2*nob, sizeof(double))) == NULL) ||
         ((m     = (double*)calloc(nob / 2 + 1, sizeof(double))) == NULL) ) {
        fprintf(stderr,"DiscreteFourierTransformTest::runTest(): "
                       "Unable to allocate working arrays for the DFT!\n");
        if( X == NULL )
            free(X);
        if( wsave == NULL )
            free(wsave);
        if( m == NULL )
            free(m);
        return 0.0;
    }

    seekPos(0);
    for ( i=0; i<(int)nob; i++ )
        X[i] = 2 * getNextBit() - 1;

    __ogg_fdrffti(nob, wsave, ifac);	// INITIALIZE WORK ARRAYS
    __ogg_fdrfftf(nob, X, wsave, ifac);	// APPLY FORWARD FFT

    m[0] = sqrt(X[0]*X[0]);	    // COMPUTE MAGNITUDE

    for ( i=0; i<(int)nob/2; i++ )
        m[i+1] = sqrt(pow(X[2*i+1],2)+pow(X[2*i+2],2));

    count = 0;				       // CONFIDENCE INTERVAL
    upperBound = sqrt(2.995732274*(double)(nob));
    for ( i=0; i<(int)nob/2; i++ )
        if ( m[i] < upperBound )
            count++;
    percentile = (double)count/(double)(nob/2)*100.0;
    N_l = (double) count;       // number of peaks less than h = sqrt(3*n)
    N_o = (double) 0.95*(double)(nob)/2.0;
    d = (N_l - N_o)/sqrt((double)(nob)/4.0*0.95*0.05);
    p_value = erfc(fabs(d)/sqrt(2.0));

    free(X);
    free(wsave);
    free(m);

    return p_value;
}



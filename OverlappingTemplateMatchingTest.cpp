/*
 * File:   OverlappingTemplateMatchingTest.cpp
 * Author: jk
 *
 * Created on 16. August 2010, 22:00
 */
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

#include "Cephes.h"
#include "Matrix.h"

#include "OverlappingTemplateMatchingTest.h"

OverlappingTemplateMatchingTest::OverlappingTemplateMatchingTest() :
    AbstractTest(),
    m(9)
{
}

OverlappingTemplateMatchingTest::~OverlappingTemplateMatchingTest()
{
}

void OverlappingTemplateMatchingTest::setTemplateLength(int32_t length)
{
    m = length;
    if (m < 2) {
        fprintf(stderr,"WARNING in NonOverlappingTemplateMatchingTest::setTemplateLength: "
                       "Parameter length too small, capping to 2");
        m = 2;
    }
    if (m > 21) {
        fprintf(stderr,"WARNING in NonOverlappingTemplateMatchingTest::setTemplateLength: "
                       "Parameter length too big, capping to 21");
        m = 21;
    }
}

int32_t OverlappingTemplateMatchingTest::getTemplateLength()
{
    return m;
}


double OverlappingTemplateMatchingTest::runTest()
{
/* original code:
	int				i, k, match;
	double			W_obs, eta, sum, chi2, p_value, lambda;
	int				M, N, j, K = 5;
	unsigned int	nu[6] = { 0, 0, 0, 0, 0, 0 };
	double			pi[6] = { 0.143783, 0.139430, 0.137319, 0.124314, 0.106209, 0.348945 };
	BitSequence		*sequence;

	M = 1032;
	N = n/M;

	if ( (sequence = (BitSequence *) calloc(m, sizeof(BitSequence))) == NULL ) {
		fprintf(stats[TEST_OVERLAPPING], "\t\t    OVERLAPPING TEMPLATE OF ALL ONES TEST\n");
		fprintf(stats[TEST_OVERLAPPING], "\t\t---------------------------------------------\n");
		fprintf(stats[TEST_OVERLAPPING], "\t\tTEMPLATE DEFINITION:  Insufficient memory, Overlapping Template Matchings test aborted!\n");
	}
	else
		for ( i=0; i<m; i++ )
			sequence[i] = 1;

	lambda = (double)(M-m+1)/pow(2,m);
	eta = lambda/2.0;
	sum = 0.0;
	for ( i=0; i<K; i++ ) {			// Compute Probabilities
		pi[i] = Pr(i, eta);
		sum += pi[i];
	}
	pi[K] = 1 - sum;

	for ( i=0; i<N; i++ ) {
		W_obs = 0;
		for ( j=0; j<M-m+1; j++ ) {
			match = 1;
			for ( k=0; k<m; k++ ) {
				if ( sequence[k] != epsilon[i*M+j+k] )
					match = 0;
			}
			if ( match == 1 )
				W_obs++;
		}
		if ( W_obs <= 4 )
			nu[(int)W_obs]++;
		else
			nu[K]++;
	}
	sum = 0;
	chi2 = 0.0;                                   // Compute Chi Square
	for ( i=0; i<K+1; i++ ) {
		chi2 += pow((double)nu[i] - (double)N*pi[i], 2)/((double)N*pi[i]);
		sum += nu[i];
	}
	p_value = cephes_igamc(K/2.0, chi2/2.0);

	fprintf(stats[TEST_OVERLAPPING], "\t\t    OVERLAPPING TEMPLATE OF ALL ONES TEST\n");
	fprintf(stats[TEST_OVERLAPPING], "\t\t-----------------------------------------------\n");
	fprintf(stats[TEST_OVERLAPPING], "\t\tCOMPUTATIONAL INFORMATION:\n");
	fprintf(stats[TEST_OVERLAPPING], "\t\t-----------------------------------------------\n");
	fprintf(stats[TEST_OVERLAPPING], "\t\t(a) n (sequence_length)      = %d\n", n);
	fprintf(stats[TEST_OVERLAPPING], "\t\t(b) m (block length of 1s)   = %d\n", m);
	fprintf(stats[TEST_OVERLAPPING], "\t\t(c) M (length of substring)  = %d\n", M);
	fprintf(stats[TEST_OVERLAPPING], "\t\t(d) N (number of substrings) = %d\n", N);
	fprintf(stats[TEST_OVERLAPPING], "\t\t(e) lambda [(M-m+1)/2^m]     = %f\n", lambda);
	fprintf(stats[TEST_OVERLAPPING], "\t\t(f) eta                      = %f\n", eta);
	fprintf(stats[TEST_OVERLAPPING], "\t\t-----------------------------------------------\n");
	fprintf(stats[TEST_OVERLAPPING], "\t\t   F R E Q U E N C Y\n");
	fprintf(stats[TEST_OVERLAPPING], "\t\t  0   1   2   3   4 >=5   Chi^2   P-value  Assignment\n");
	fprintf(stats[TEST_OVERLAPPING], "\t\t-----------------------------------------------\n");
	fprintf(stats[TEST_OVERLAPPING], "\t\t%3d %3d %3d %3d %3d %3d  %f ",
		nu[0], nu[1], nu[2], nu[3], nu[4], nu[5], chi2);

	if ( isNegative(p_value) || isGreaterThanOne(p_value) )
		fprintf(stats[TEST_OVERLAPPING], "WARNING:  P_VALUE IS OUT OF RANGE.\n");

	free(sequence);
	fprintf(stats[TEST_OVERLAPPING], "%f %s\n\n", p_value, p_value < ALPHA ? "FAILURE" : "SUCCESS"); fflush(stats[TEST_OVERLAPPING]);
	fprintf(results[TEST_OVERLAPPING], "%f\n", p_value); fflush(results[TEST_OVERLAPPING]);

 */
    seekPos(0);

    uint64_t nob = getNrOfBits();
    if (nob < 1000000) {
        fprintf(stderr,"OverlappingTemplateMatchingTest::runTest(): "
                       "Data should contain at least 1000000 Bits!\n");
        return 0.0;
    }

    int	i, k, match;
    double W_obs, eta, sum, chi2, p_value, lambda;
    int M, N, j, K = 5;
    unsigned int nu[6] = { 0, 0, 0, 0, 0, 0 };
    double pi[6] = { 0.143783, 0.139430, 0.137319, 0.124314, 0.106209, 0.348945 };
    Matrix::BitSequence *sequence;

    M = 1032;
    N = nob / M;

    if ( (sequence = (Matrix::BitSequence *) calloc(m, sizeof(Matrix::BitSequence))) == NULL ) {
        fprintf(stderr,"ERROR in OverlappingTemplateMatchingTest::runTest(): "
                       "Insufficient memory, Overlapping Template Matchings test aborted!\n");
        return 0.0;
    }

    for (i = 0; i < m; ++i)
        sequence[i] = 1;

    lambda = (double)(M - m + 1) / pow(2.0,(double)(m));
    eta = lambda/2.0;
    sum = 0.0;

    for (i = 0; i < K; ++i) {			// Compute Probabilities
        pi[i] = Pr(i, eta);
        sum += pi[i];
    }

    pi[K] = 1.0 - sum;

    for (i = 0; i < N; ++i) {
        W_obs = 0;
        for (j = 0; j < M - m + 1; ++j) {
            match = 1;
            for (k = 0; k < m; ++k) {
                if ( sequence[k] != getBit(i*M+j+k) )
                    match = 0;
            }
            if ( match == 1 )
                W_obs++;
        }
        if ( W_obs <= 4 )
            nu[(int)W_obs]++;
        else
            nu[K]++;
    }
    sum = 0.0;
    chi2 = 0.0;                                   // Compute Chi Square
    for (i = 0; i < K + 1; ++i) {
        chi2 += pow((double)(nu[i]) - (double)(N)*pi[i], 2.0)/((double)(N)*pi[i]);
        sum += nu[i];
    }

    p_value = Cephes::cephes_igamc((double)(K)/2.0, chi2/2.0);

    free(sequence);

    return p_value;
}

double OverlappingTemplateMatchingTest::Pr(int u, double eta)
{
    int l;
    double sum, p;

    if (u == 0) {
        p = exp(-eta);
    } else {
        sum = 0.0;
        for (l = 1; l <= u; ++l)
            sum += exp(-eta-(double)(u)*log(2.0)
                           +(double)(l)*log(eta)
                           -Cephes::cephes_lgam((double)(l+1))
                           +Cephes::cephes_lgam((double)(u))
                           -Cephes::cephes_lgam((double)(l))
                           -Cephes::cephes_lgam((double)(u-l+1)));
        p = sum;
    }
    return p;
}



/*
 * File:   NonOverlappingTemplateMatchingTest.cpp
 * Author: jk
 *
 * Created on 16. August 2010, 20:20
 */

#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

#include "NonOverlappingTemplateMatchingTest.h"
#include "Matrix.h"
#include "Tools.h"
#include "Cephes.h"

NonOverlappingTemplateMatchingTest::NonOverlappingTemplateMatchingTest() :
    AbstractTest(),
    m(9)
{
}


NonOverlappingTemplateMatchingTest::~NonOverlappingTemplateMatchingTest()
{
}

void NonOverlappingTemplateMatchingTest::setTemplateLength(int32_t length)
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

int32_t NonOverlappingTemplateMatchingTest::getTemplateLength()
{
    return m;
}


double NonOverlappingTemplateMatchingTest::runTest()
{
/* original code:
 	int		numOfTemplates[100] = {0, 0, 2, 4, 6, 12, 20, 40, 74, 148, 284, 568, 1116,
						2232, 4424, 8848, 17622, 35244, 70340, 140680, 281076, 562152};
	//----------------------------------------------------------------------------
	//NOTE:  Should additional templates lengths beyond 21 be desired, they must
	//first be constructed, saved into files and then the corresponding
	//number of nonperiodic templates for that file be stored in the m-th
	//position in the numOfTemplates variable.
	//----------------------------------------------------------------------------
	unsigned int	bit, W_obs, nu[6], *Wj = NULL;
	FILE			*fp;
	double			sum, chi2, p_value, lambda, pi[6], varWj;
	int				i, j, jj, k, match, SKIP, M, N, K = 5;
	char			directory[100];
	BitSequence		*sequence = NULL;

	N = 8;
	M = n/N;

	if ( (Wj = (unsigned int*)calloc(N, sizeof(unsigned int))) == NULL ) {
		fprintf(stats[TEST_NONPERIODIC], "\tNONOVERLAPPING TEMPLATES TESTS ABORTED DUE TO ONE OF THE FOLLOWING : \n");
		fprintf(stats[TEST_NONPERIODIC], "\tInsufficient memory for required work space.\n");
		return;
	}
	lambda = (M-m+1)/pow(2, m);
	varWj = M*(1.0/pow(2.0, m) - (2.0*m-1.0)/pow(2.0, 2.0*m));
	sprintf(directory, "templates/template%d", m);

	if ( ((isNegative(lambda)) || (isZero(lambda))) ||
		 ((fp = fopen(directory, "r")) == NULL) ||
		 ((sequence = (BitSequence *) calloc(m, sizeof(BitSequence))) == NULL) ) {
		fprintf(stats[TEST_NONPERIODIC], "\tNONOVERLAPPING TEMPLATES TESTS ABORTED DUE TO ONE OF THE FOLLOWING : \n");
		fprintf(stats[TEST_NONPERIODIC], "\tLambda (%f) not being positive!\n", lambda);
		fprintf(stats[TEST_NONPERIODIC], "\tTemplate file <%s> not existing\n", directory);
		fprintf(stats[TEST_NONPERIODIC], "\tInsufficient memory for required work space.\n");
		if ( sequence != NULL )
			free(sequence);
	}
	else {
		fprintf(stats[TEST_NONPERIODIC], "\t\t  NONPERIODIC TEMPLATES TEST\n");
		fprintf(stats[TEST_NONPERIODIC], "-------------------------------------------------------------------------------------\n");
		fprintf(stats[TEST_NONPERIODIC], "\t\t  COMPUTATIONAL INFORMATION\n");
		fprintf(stats[TEST_NONPERIODIC], "-------------------------------------------------------------------------------------\n");
		fprintf(stats[TEST_NONPERIODIC], "\tLAMBDA = %f\tM = %d\tN = %d\tm = %d\tn = %d\n", lambda, M, N, m, n);
		fprintf(stats[TEST_NONPERIODIC], "-------------------------------------------------------------------------------------\n");
		fprintf(stats[TEST_NONPERIODIC], "\t\tF R E Q U E N C Y\n");
		fprintf(stats[TEST_NONPERIODIC], "Template   W_1  W_2  W_3  W_4  W_5  W_6  W_7  W_8    Chi^2   P_value Assignment Index\n");
		fprintf(stats[TEST_NONPERIODIC], "-------------------------------------------------------------------------------------\n");

		if ( numOfTemplates[m] < MAXNUMOFTEMPLATES )
			SKIP = 1;
		else
			SKIP = (int)(numOfTemplates[m]/MAXNUMOFTEMPLATES);
		numOfTemplates[m] = (int)numOfTemplates[m]/SKIP;

		sum = 0.0;
		for ( i=0; i<2; i++ ) {                    //  Compute Probabilities
			pi[i] = exp(-lambda+i*log(lambda)-cephes_lgam(i+1));
			sum += pi[i];
		}
		pi[0] = sum;
		for ( i=2; i<=K; i++ ) {                   //  Compute Probabilities
			pi[i-1] = exp(-lambda+i*log(lambda)-cephes_lgam(i+1));
			sum += pi[i-1];
		}
		pi[K] = 1 - sum;

		for( jj=0; jj<MIN(MAXNUMOFTEMPLATES, numOfTemplates[m]); jj++ ) {
			sum = 0;

			for ( k=0; k<m; k++ ) {
				fscanf(fp, "%d", &bit);
				sequence[k] = bit;
				fprintf(stats[TEST_NONPERIODIC], "%d", sequence[k]);
			}
			fprintf(stats[TEST_NONPERIODIC], " ");
			for ( k=0; k<=K; k++ )
				nu[k] = 0;
			for ( i=0; i<N; i++ ) {
				W_obs = 0;
				for ( j=0; j<M-m+1; j++ ) {
					match = 1;
					for ( k=0; k<m; k++ ) {
						if ( (int)sequence[k] != (int)epsilon[i*M+j+k] ) {
							match = 0;
							break;
						}
					}
					if ( match == 1 )
						W_obs++;
				}
				Wj[i] = W_obs;
			}
			sum = 0;
			chi2 = 0.0;                                   // Compute Chi Square
			for ( i=0; i<N; i++ ) {
				if ( m == 10 )
					fprintf(stats[TEST_NONPERIODIC], "%3d  ", Wj[i]);
				else
					fprintf(stats[TEST_NONPERIODIC], "%4d ", Wj[i]);
				chi2 += pow(((double)Wj[i] - lambda)/pow(varWj, 0.5), 2);
			}
			p_value = cephes_igamc(N/2.0, chi2/2.0);

			if ( isNegative(p_value) || isGreaterThanOne(p_value) )
				fprintf(stats[TEST_NONPERIODIC], "\t\tWARNING:  P_VALUE IS OUT OF RANGE.\n");

			fprintf(stats[TEST_NONPERIODIC], "%9.6f %f %s %3d\n", chi2, p_value, p_value < ALPHA ? "FAILURE" : "SUCCESS", jj);
			if ( SKIP > 1 )
				fseek(fp, (long)(SKIP-1)*2*m, SEEK_CUR);
			fprintf(results[TEST_NONPERIODIC], "%f\n", p_value); fflush(results[TEST_NONPERIODIC]);
		}
	}

	fprintf(stats[TEST_NONPERIODIC], "\n"); fflush(stats[TEST_NONPERIODIC]);
	if ( sequence != NULL )
		free(sequence);

	free(Wj);
	fclose(fp);

 */

    seekPos(0);
    uint64_t nob = getNrOfBits();
    if (nob < 1000000) {
        fprintf(stderr,"NonOverlappingTemplateMatchingTest::runTest(): "
                       "Data should contain at least 1000000 Bits!\n");
        return 0.0;
    }

    if (pValues == NULL) {
        fprintf(stderr,"NonOverlappingTemplateMatchingTest::runTest(): "
                       "No valid vector<double> for results given!\n");
        return 0.0;
    }


    int numOfTemplates[100] = {0, 0, 2, 4, 6, 12, 20, 40, 74, 148, 284, 568,
                               1116, 2232, 4424, 8848, 17622, 35244, 70340,
                               140680, 281076, 562152};
	//----------------------------------------------------------------------------
	//NOTE:  Should additional templates lengths beyond 21 be desired, they must
	//first be constructed, saved into files and then the corresponding
	//number of nonperiodic templates for that file be stored in the m-th
	//position in the numOfTemplates variable.
	//----------------------------------------------------------------------------
    unsigned int bit, W_obs, nu[6], *Wj = NULL;
    FILE *fp;
    double sum, chi2, p_value, lambda, pi[6], varWj;
    p_value = 0.0;

    int i, j, jj, k, match, SKIP, M, N, K = 5;
    char directory[100];
    Matrix::BitSequence *sequence = NULL;

    N = 8;
    M = nob / N;

    if ( (Wj = (unsigned int*)calloc(N, sizeof(unsigned int))) == NULL ) {
        fprintf(stderr,"ERROR in NonOverlappingTemplateMatchingTest::runTest(): "
                       "Insufficient memory for required work space.\n");
        return 0.0;
    }

    lambda = (double)(M - m + 1) / pow( 2.0 , (double)(m) );

    varWj = (double)(M) * (1.0 / pow(2.0, (double)(m)) - (2.0* (double)(m) - 1.0) / pow(2.0, 2.0*(double)(m)));

    sprintf(directory, "templates/template%d", m);

    if ((Tools::isNegative(lambda)) || (Tools::isZero(lambda))) {
        fprintf(stderr,"ERROR in NonOverlappingTemplateMatchingTest::runTest(): "
                       "Lambda (%f) not being positive.\n", lambda);
        return 0.0;
    }

    if ((fp = fopen(directory, "r")) == NULL) {
        fprintf(stderr,"ERROR in NonOverlappingTemplateMatchingTest::runTest(): "
                       "Template file <%s> not existing.\n", directory);
        return 0.0;
    }

    if ((sequence = (Matrix::BitSequence *) calloc(m, sizeof(Matrix::BitSequence))) == NULL) {
        fprintf(stderr,"ERROR in NonOverlappingTemplateMatchingTest::runTest(): "
                       "Insufficient memory for required work space.\n");
        return 0.0;
    }


    if ( numOfTemplates[m] < (int)MAXNUMOFTEMPLATES )
        SKIP = 1;
    else
        SKIP = (int)(numOfTemplates[m]/MAXNUMOFTEMPLATES);

    numOfTemplates[m] = (int)numOfTemplates[m] / SKIP;

    sum = 0.0;

    for (i = 0; i < 2; ++i) {                    //  Compute Probabilities
        pi[i]  = exp(-lambda + (double)(i) * log(lambda) - Cephes::cephes_lgam((double)(i+1)));
        sum   += pi[i];
    }

    pi[0] = sum;

    for (i = 2; i <= K; ++i) {                   //  Compute Probabilities
        pi[i-1] = exp(-lambda + (double)(i) * log(lambda) - Cephes::cephes_lgam((double)(i+1)));
        sum += pi[i-1];
    }

    pi[K] = 1.0 - sum;

    for(jj = 0; jj < Tools::MIN(MAXNUMOFTEMPLATES, numOfTemplates[m]); ++jj) {
        sum = 0.0;
        for (k = 0; k < m; ++k) {
            int nrOfVars = fscanf(fp, "%d", &bit);
            if (nrOfVars < 1)
                fprintf(stderr,"WARNING in NonOverlappingTemplateMatchingTest::runTest(): "
                               "fscanf did not read value!\n");
            sequence[k] = bit;
        }
	for (k = 0; k <= K; ++k)
            nu[k] = 0;
        for (i = 0; i < N; ++i) {
            W_obs = 0;
            for (j = 0; j < M - m + 1; ++j) {
                match = 1;
                for (k = 0; k < m; ++k) {
                    if ( (int)sequence[k] != (int)getBit(i*M+j+k) ) {
                        match = 0;
                        break;
                    }
                }
                if ( match == 1 )
                    W_obs++;
            }
            Wj[i] = W_obs;
        }

	sum  = 0.0;
	chi2 = 0.0;                                   // Compute Chi Square
	for (i = 0; i < N; ++i) {
            chi2 += pow(((double)Wj[i] - lambda)/pow(varWj, 0.5), 2.0);
        }

	p_value = Cephes::cephes_igamc((double)(N)/2.0, chi2/2.0);

        pValues->push_back(p_value);

        if ( SKIP > 1 )
            fseek(fp, (long)(SKIP-1)*2*m, SEEK_CUR);
    }

    if ( sequence != NULL )
        free(sequence);

    free(Wj);
    fclose(fp);

    return p_value;
}



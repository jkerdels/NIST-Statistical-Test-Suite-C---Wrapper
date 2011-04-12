/*
 * File:   SerialTest.cpp
 * Author: jk
 *
 * Created on 13. Dezember 2010, 23:08
 */
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

#include "Cephes.h"
#include "Tools.h"

#include "SerialTest.h"

SerialTest::SerialTest(int blockSize) :
    AbstractTest(),
    m(blockSize)
{
}


SerialTest::~SerialTest()
{
}

void SerialTest::setBlockSize(int blockSize)
{
    m = blockSize;
}

int SerialTest::getBlockSize()
{
    return m;
}


double SerialTest::runTest()
{
/* original code:
 void
Serial(int m, int n)
{
	double	p_value1, p_value2, psim0, psim1, psim2, del1, del2;

	psim0 = psi2(m, n);
	psim1 = psi2(m-1, n);
	psim2 = psi2(m-2, n);
	del1 = psim0 - psim1;
	del2 = psim0 - 2.0*psim1 + psim2;
	p_value1 = cephes_igamc(pow(2, m-1)/2, del1/2.0);
	p_value2 = cephes_igamc(pow(2, m-2)/2, del2/2.0);

	fprintf(stats[TEST_SERIAL], "\t\t\t       SERIAL TEST\n");
	fprintf(stats[TEST_SERIAL], "\t\t---------------------------------------------\n");
	fprintf(stats[TEST_SERIAL], "\t\t COMPUTATIONAL INFORMATION:		  \n");
	fprintf(stats[TEST_SERIAL], "\t\t---------------------------------------------\n");
	fprintf(stats[TEST_SERIAL], "\t\t(a) Block length    (m) = %d\n", m);
	fprintf(stats[TEST_SERIAL], "\t\t(b) Sequence length (n) = %d\n", n);
	fprintf(stats[TEST_SERIAL], "\t\t(c) Psi_m               = %f\n", psim0);
	fprintf(stats[TEST_SERIAL], "\t\t(d) Psi_m-1             = %f\n", psim1);
	fprintf(stats[TEST_SERIAL], "\t\t(e) Psi_m-2             = %f\n", psim2);
	fprintf(stats[TEST_SERIAL], "\t\t(f) Del_1               = %f\n", del1);
	fprintf(stats[TEST_SERIAL], "\t\t(g) Del_2               = %f\n", del2);
	fprintf(stats[TEST_SERIAL], "\t\t---------------------------------------------\n");

	fprintf(stats[TEST_SERIAL], "%s\t\tp_value1 = %f\n", p_value1 < ALPHA ? "FAILURE" : "SUCCESS", p_value1);
	fprintf(results[TEST_SERIAL], "%f\n", p_value1);

	fprintf(stats[TEST_SERIAL], "%s\t\tp_value2 = %f\n\n", p_value2 < ALPHA ? "FAILURE" : "SUCCESS", p_value2); fflush(stats[TEST_SERIAL]);
	fprintf(results[TEST_SERIAL], "%f\n", p_value2); fflush(results[TEST_SERIAL]);
}
 */
    seekPos(0);
    uint64_t nob = getNrOfBits();
    if (m >= floor(log(nob) / log(2.0))-2.0 ) {
        fprintf(stderr,"SerialTest::runTest(): "
                       "BlockSize (m) too big! It should be m < floor(log2(n))-2\n");
        return 0.0;
    }

    double p_value1, p_value2, psim0, psim1, psim2, del1, del2;

    psim0 = psi2(m, nob);
    psim1 = psi2(m-1, nob);
    psim2 = psi2(m-2, nob);
    del1 = psim0 - psim1;
    del2 = psim0 - 2.0*psim1 + psim2;
    p_value1 = Cephes::cephes_igamc(pow(2, m-1)/2, del1/2.0);
    p_value2 = Cephes::cephes_igamc(pow(2, m-2)/2, del2/2.0);

    return Tools::MIN(p_value1,p_value2);

}


double SerialTest::psi2(int lm, int n)
{
/* original code:
double
psi2(int m, int n)
{
	int				i, j, k, powLen;
	double			sum, numOfBlocks;
	unsigned int	*P;

	if ( (m == 0) || (m == -1) )
		return 0.0;
	numOfBlocks = n;
	powLen = (int)pow(2, m+1)-1;
	if ( (P = (unsigned int*)calloc(powLen,sizeof(unsigned int)))== NULL ) {
		fprintf(stats[TEST_SERIAL], "Serial Test:  Insufficient memory available.\n");
		fflush(stats[TEST_SERIAL]);
		return 0.0;
	}
	for ( i=1; i<powLen-1; i++ )
		P[i] = 0;	  // INITIALIZE NODES
	for ( i=0; i<numOfBlocks; i++ ) {		 // COMPUTE FREQUENCY
		k = 1;
		for ( j=0; j<m; j++ ) {
			if ( epsilon[(i+j)%n] == 0 )
				k *= 2;
			else if ( epsilon[(i+j)%n] == 1 )
				k = 2*k+1;
		}
		P[k-1]++;
	}
	sum = 0.0;
	for ( i=(int)pow(2, m)-1; i<(int)pow(2, m+1)-1; i++ )
		sum += pow(P[i], 2);
	sum = (sum * pow(2, m)/(double)n) - (double)n;
	free(P);

	return sum;
}

 */

    int              i, j, k, powLen;
    double           sum, numOfBlocks;
    unsigned int    *P;

    if ( (lm == 0) || (lm == -1) )
            return 0.0;
    numOfBlocks = n;
    powLen = (int)pow(2, lm+1)-1;
    if ( (P = (unsigned int*)calloc(powLen,sizeof(unsigned int)))== NULL ) {
        fprintf(stderr,"SerialTest::psi2(): "
                       "Insufficient memory available.\n");
        return 0.0;
    }
    for ( i=1; i<powLen-1; i++ )
            P[i] = 0;	  // INITIALIZE NODES
    for ( i=0; i<numOfBlocks; i++ ) {		 // COMPUTE FREQUENCY
            k = 1;
            for ( j=0; j<lm; j++ ) {
                    if ( getBit((i+j)%n) == 0 )
                            k *= 2;
                    else if ( getBit((i+j)%n) == 1 )
                            k = 2*k+1;
            }
            P[k-1]++;
    }
    sum = 0.0;
    for ( i=(int)pow(2, lm)-1; i<(int)pow(2, lm+1)-1; i++ )
            sum += pow(P[i], 2);
    sum = (sum * pow(2, lm)/(double)n) - (double)n;
    free(P);

    return sum;

}

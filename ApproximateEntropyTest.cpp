/*
 * File:   ApproximateEntropyTest.cpp
 * Author: jk
 *
 * Created on 13. Dezember 2010, 23:46
 */
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

#include "Cephes.h"

#include "ApproximateEntropyTest.h"

ApproximateEntropyTest::ApproximateEntropyTest(int blockSize) :
    AbstractTest(),
    m(blockSize)
{
}


ApproximateEntropyTest::~ApproximateEntropyTest()
{
}

void ApproximateEntropyTest::setBlockSize(int blockSize)
{
    m = blockSize;
}

int ApproximateEntropyTest::getBlockSize()
{
    return m;
}


double ApproximateEntropyTest::runTest()
{
/* original code:
void
ApproximateEntropy(int m, int n)
{
	int				i, j, k, r, blockSize, seqLength, powLen, index;
	double			sum, numOfBlocks, ApEn[2], apen, chi_squared, p_value;
	unsigned int	*P;

	fprintf(stats[TEST_APEN], "\t\t\tAPPROXIMATE ENTROPY TEST\n");
	fprintf(stats[TEST_APEN], "\t\t--------------------------------------------\n");
	fprintf(stats[TEST_APEN], "\t\tCOMPUTATIONAL INFORMATION:\n");
	fprintf(stats[TEST_APEN], "\t\t--------------------------------------------\n");
	fprintf(stats[TEST_APEN], "\t\t(a) m (block length)    = %d\n", m);

	seqLength = n;
	r = 0;

	for ( blockSize=m; blockSize<=m+1; blockSize++ ) {
		if ( blockSize == 0 ) {
			ApEn[0] = 0.00;
			r++;
		}
		else {
			numOfBlocks = (double)seqLength;
			powLen = (int)pow(2, blockSize+1)-1;
			if ( (P = (unsigned int*)calloc(powLen,sizeof(unsigned int)))== NULL ) {
				fprintf(stats[TEST_APEN], "ApEn:  Insufficient memory available.\n");
				return;
			}
			for ( i=1; i<powLen-1; i++ )
				P[i] = 0;
			for ( i=0; i<numOfBlocks; i++ ) { // COMPUTE FREQUENCY
				k = 1;
				for ( j=0; j<blockSize; j++ ) {
					k <<= 1;
					if ( (int)epsilon[(i+j) % seqLength] == 1 )
						k++;
				}
				P[k-1]++;
			}
			// DISPLAY FREQUENCY
			sum = 0.0;
			index = (int)pow(2, blockSize)-1;
			for ( i=0; i<(int)pow(2, blockSize); i++ ) {
				if ( P[index] > 0 )
					sum += P[index]*log(P[index]/numOfBlocks);
				index++;
			}
			sum /= numOfBlocks;
			ApEn[r] = sum;
			r++;
			free(P);
		}
	}
	apen = ApEn[0] - ApEn[1];

	chi_squared = 2.0*seqLength*(log(2) - apen);
	p_value = cephes_igamc(pow(2, m-1), chi_squared/2.0);

	fprintf(stats[TEST_APEN], "\t\t(b) n (sequence length) = %d\n", seqLength);
	fprintf(stats[TEST_APEN], "\t\t(c) Chi^2               = %f\n", chi_squared);
	fprintf(stats[TEST_APEN], "\t\t(d) Phi(m)	       = %f\n", ApEn[0]);
	fprintf(stats[TEST_APEN], "\t\t(e) Phi(m+1)	       = %f\n", ApEn[1]);
	fprintf(stats[TEST_APEN], "\t\t(f) ApEn                = %f\n", apen);
	fprintf(stats[TEST_APEN], "\t\t(g) Log(2)              = %f\n", log(2.0));
	fprintf(stats[TEST_APEN], "\t\t--------------------------------------------\n");

	if ( m > (int)(log(seqLength)/log(2)-5) ) {
		fprintf(stats[TEST_APEN], "\t\tNote: The blockSize = %d exceeds recommended value of %d\n", m,
			MAX(1, (int)(log(seqLength)/log(2)-5)));
		fprintf(stats[TEST_APEN], "\t\tResults are inaccurate!\n");
		fprintf(stats[TEST_APEN], "\t\t--------------------------------------------\n");
	}

	fprintf(stats[TEST_APEN], "%s\t\tp_value = %f\n\n", p_value < ALPHA ? "FAILURE" : "SUCCESS", p_value); fflush(stats[TEST_APEN]);
	fprintf(results[TEST_APEN], "%f\n", p_value); fflush(results[TEST_APEN]);
}
 */
    seekPos(0);
    uint64_t nob = getNrOfBits();
    if (m >= floor(log(nob) / log(2.0))-5.0 ) {
        fprintf(stderr,"ApproximateEntropyTest::runTest(): "
                       "BlockSize (m) too big! It should be m < floor(log2(n))-5\n");
        return 0.0;
    }


    int			 i, j, k, r, blockSize, seqLength, powLen, index;
    double		 sum, numOfBlocks, ApEn[2], apen, chi_squared, p_value;
    unsigned int	*P;

    seqLength = nob;
    r = 0;

    for ( blockSize=m; blockSize<=m+1; blockSize++ ) {
            if ( blockSize == 0 ) {
                    ApEn[0] = 0.00;
                    r++;
            }
            else {
                    numOfBlocks = (double)seqLength;
                    powLen = (int)pow(2, blockSize+1)-1;
                    if ( (P = (unsigned int*)calloc(powLen,sizeof(unsigned int)))== 0 ) {
                            fprintf(stderr,"ApproximateEntropyTest::runTest(): "
                                           "Insufficient memory available.\n");
                            return 0.0;
                    }
                    for ( i=1; i<powLen-1; i++ )
                            P[i] = 0;
                    for ( i=0; i<numOfBlocks; i++ ) { // COMPUTE FREQUENCY
                            k = 1;
                            for ( j=0; j<blockSize; j++ ) {
                                    k <<= 1;
                                    if ( (int)getBit((i+j) % seqLength) == 1 )
                                            k++;
                            }
                            P[k-1]++;
                    }
                    // DISPLAY FREQUENCY
                    sum = 0.0;
                    index = (int)pow(2, blockSize)-1;
                    for ( i=0; i<(int)pow(2, blockSize); i++ ) {
                            if ( P[index] > 0 )
                                    sum += P[index]*log(P[index]/numOfBlocks);
                            index++;
                    }
                    sum /= numOfBlocks;
                    ApEn[r] = sum;
                    r++;
                    free(P);
            }
    }
    apen = ApEn[0] - ApEn[1];

    chi_squared = 2.0*seqLength*(log(2) - apen);
    p_value = Cephes::cephes_igamc(pow(2, m-1), chi_squared/2.0);

    return p_value;

}

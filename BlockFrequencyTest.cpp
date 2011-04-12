/*
 * File:   BlockFrequencyTest.cpp
 * Author: jk
 *
 * Created on 15. August 2010, 10:04
 */
#include <cstdio>

using namespace std;

#include "BlockFrequencyTest.h"
#include "Cephes.h"

BlockFrequencyTest::BlockFrequencyTest(bool _autoBlockSize, uint64_t _blockSize) :
    AbstractTest(),
    autoBlockSize(_autoBlockSize),
    blockSize(_blockSize)
{
}

BlockFrequencyTest::~BlockFrequencyTest()
{
}

double BlockFrequencyTest::runTest()
{
    /*
     // original code

void
BlockFrequency(int M, int n)
{
	int		i, j, N, blockSum;
	double	p_value, sum, pi, v, chi_squared;

	N = n/M; 		// # OF SUBSTRING BLOCKS
	sum = 0.0;

	for ( i=0; i<N; i++ ) {
		blockSum = 0;
		for ( j=0; j<M; j++ )
			blockSum += epsilon[j+i*M];
		pi = (double)blockSum/(double)M;
		v = pi - 0.5;
		sum += v*v;
	}
	chi_squared = 4.0 * M * sum;
	p_value = cephes_igamc(N/2.0, chi_squared/2.0);

...

}  */

    seekPos(0);

    uint64_t nob = getNrOfBits();

    if (nob < 100) {
        fprintf(stderr,"BlockFrequencyTest::runTest(): Data should contain at least 100 Bits!\n");
        return 0.0;
    }

    if (autoBlockSize) {
        // using here NIST recommendations
        // let dataSize = blockSize * N;
        // --> M >= 20, M > 0.01 * dataSize and N < 100
        blockSize = (nob / 100) + 1;
        if (blockSize < 20)
            blockSize = 20;
    } else if ((blockSize < 20) || (nob / blockSize >= 100)) {
        fprintf(stderr,"BlockFrequencyTest::runTest(): BlockSize M too small:\n"
                       "  Let n = M * N :\n"
                       "  --> M >= 20, M > 0.01 * n and N < 100\n");
        return 0.0;
    }

    uint64_t i, j, N, blockSum;
    uint64_t M = blockSize;

    double p_value, sum, pi, v, chi_squared;

    N = nob/M; 		// # OF SUBSTRING BLOCKS

    sum = 0.0;
    seekPos(0);
    for (i = 0; i < N; ++i) {
        blockSum = 0;
	for (j = 0; j < M; ++j)
            blockSum += getNextBit();

	pi   = (double)(blockSum)/(double)(M);
	v    = pi - 0.5;
	sum += v*v;
    }
    chi_squared = 4.0 * M * sum;
    p_value = Cephes::cephes_igamc((double)(N)/2.0, chi_squared/2.0);

    return p_value;
}

void BlockFrequencyTest::setAutoBlockSize(bool _autoBlockSize)
{
    autoBlockSize = _autoBlockSize;
}

bool BlockFrequencyTest::getAutoBlockSize()
{
    return autoBlockSize;
}

void BlockFrequencyTest::setBlockSize(uint64_t _blockSize)
{
    blockSize = _blockSize;
}

uint64_t BlockFrequencyTest::getBlockSize()
{
    return blockSize;
}

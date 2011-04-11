/* 
 * File:   BlockFrequencyTest.h
 * Author: jk
 *
 * Created on 15. August 2010, 10:04
 */

#ifndef BLOCKFREQUENCYTEST_H
#define	BLOCKFREQUENCYTEST_H

#include <inttypes.h>
#include "AbstractTest.h"

class BlockFrequencyTest : public AbstractTest
{
public:
    BlockFrequencyTest(bool _autoBlockSize = true, uint64_t _blockSize = 20);
    ~BlockFrequencyTest();

    void setAutoBlockSize(bool _autoBlockSize);
    bool getAutoBlockSize();

    void     setBlockSize(uint64_t _blockSize);
    uint64_t getBlockSize();

    double runTest();
    
	const char* getTestName() {return "BlockFrequency";}

private:

    bool     autoBlockSize;
    uint64_t blockSize;

};

#endif	/* BLOCKFREQUENCYTEST_H */


/* 
 * File:   AbstractTest.h
 * Author: jk
 *
 * Created on 14. August 2010, 23:57
 */

#ifndef ABSTRACTTEST_H
#define	ABSTRACTTEST_H

#include <inttypes.h>
#include <vector>

using namespace std;

class Matrix;

class AbstractTest
{
    friend class Matrix;

    enum DataSrc {
        dsNone = 0,
        dsMemory
    };

public:
    AbstractTest();
    virtual ~AbstractTest();

    // set the data src to a memory location with
    // dataSize Bytes
    void setData(const uint8_t *_data, uint32_t _dataSize);
    void setDataSelfTest();

    // implement this function with the test-function and return
    // the calculated p-value
    // use the protected methods getNrOfBits(), getBit(), seekPos() and
    // getNextBit() to access the data for the test
    virtual double runTest() = 0;

    // some tests are not always applicable, e.g. RandomExcursionsTest
    // use this function to check, if the last runTest() was applicable
    virtual bool testWasApplicable() {return true;}

	// some tests return more than one double,
	// use these functions to set and get the result vector
    void setResultVector(vector<double> *_pValues);
    vector<double>* getResultVector();
	// use this function to check, wether the result vector is needed
	virtual bool resultVectorNeeded() {return false;}

	// implement this function to return the test name
	virtual const char* getTestName() {return "foo";}

protected:
    uint64_t getNrOfBits();
    int8_t   getBit(uint64_t bitIdx);
    void     seekPos(uint64_t bitIdx);
    int8_t   getNextBit();

    vector<double> *pValues;

private:

    // members for dsMemory
    uint8_t  *data;
    uint32_t  dataSize;
    uint32_t  endBlockCnt;
    uint64_t  curBlockVal;
    uint64_t *curBlockPointer;
    uint64_t *endBlockPointer;
    uint8_t   curSubIdx;

    // common members
    DataSrc  dataSrcType;
    uint64_t bitCount;

};

#endif	/* ABSTRACTTEST_H */


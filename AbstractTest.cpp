/*
 * File:   AbstractTest.cpp
 * Author: jk
 *
 * Created on 14. August 2010, 23:57
 */
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>

using namespace std;

#include "AbstractTest.h"

AbstractTest::AbstractTest() :
    dataSrcType(dsNone),
    bitCount(0)
{
}

AbstractTest::~AbstractTest()
{
}

void AbstractTest::setData(const uint8_t *_data, uint32_t _dataSize)
{
    data     = (uint8_t*)(_data);
    dataSize = _dataSize;

    endBlockPointer = (uint64_t*)(data + (dataSize >> 3));
    endBlockCnt     = dataSize &  7;
    curBlockPointer = (uint64_t*)(data);
    curSubIdx       = 0;
    if (curBlockPointer != endBlockPointer)
        curBlockVal = *curBlockPointer;
    else if (endBlockCnt > 0)
        memcpy(&curBlockVal,curBlockPointer,endBlockCnt);
    else
        curBlockVal = 0;

    dataSrcType = dsMemory;
    bitCount    = dataSize * 8;
}

void AbstractTest::setDataSelfTest()
{
    srand(time(0));

    printf("Performing self test on input data:\n");
    uint32_t ds = getNrOfBits() / 8;
    uint8_t *copyData = new uint8_t[ds];
    uint8_t *cdp = copyData;

    printf("* checking seek + nextbit\n");
    seekPos(0);
    uint32_t i,j;
    for (i = 0; i < ds; ++i) {
        uint8_t cv = 0;
        for (j = 0; j < 8; ++j)
            cv = cv | (getNextBit() << j);
        *(cdp++) = cv;
    }
    uint32_t differentBytes = 0;
    for (i = 0; i < ds; ++i)
        if (copyData[i] != data[i])
            differentBytes++;

    printf("  Nr. of different Bytes: %u ",differentBytes);
    if (differentBytes == 0)
        printf("PASSED\n");
    else
        printf("FAILED\n");

    printf("* random access ");

    uint32_t randomByteIdx = rand() % ds;

    uint8_t constructedByte = 0;
    for (i = 0; i < 8; ++i)
        constructedByte |= getBit((randomByteIdx << 3) + i) << i;

    if (constructedByte == data[randomByteIdx])
        printf("PASSED\n");
    else
        printf("FAILED\n");

    delete[] copyData;
}

uint64_t AbstractTest::getNrOfBits()
{
    return bitCount;
}

int8_t AbstractTest::getBit(uint64_t bitIdx)
{
    if (bitIdx >= bitCount) {
        fprintf(stderr,"ERROR in AbstractTest::getBit(): "
                       "bitIdx (%lu) violates bounds (>=%lu)!\n",
                bitIdx,bitCount);
        return -1;
    }
    switch (dataSrcType) {
        case dsMemory : {
            //return (*(data + (bitIdx >> 3)) >> (bitIdx & 7)) & 1;
            // MSB first as in the NIST suite
            return (*(data + (bitIdx >> 3)) >> (7 - (bitIdx & 7))) & 1;
        }
        default : {
            fprintf(stderr,"ERROR in AbstractTest::getBit(): "
                           "data source not set!\n");
            return -1;
        }
    }
}

void AbstractTest::seekPos(uint64_t bitIdx)
{
    if (bitIdx >= bitCount) {
        fprintf(stderr,"ERROR in AbstractTest::seekPos(): "
                       "bitIdx (%lu) violates bounds (>=%lu)!\n",
                bitIdx,bitCount);
        return;
    }
    switch (dataSrcType) {
        case dsMemory : {
            curSubIdx       = bitIdx & 63;
            curBlockPointer = (uint64_t*)(data + (bitIdx >> 3));
            if (curBlockPointer != endBlockPointer)
                curBlockVal = *curBlockPointer;
            else if (endBlockCnt > 0)
                memcpy(&curBlockVal,curBlockPointer,endBlockCnt);
            else
                curBlockVal = 0;
            return;
        }
        default : {
            fprintf(stderr,"ERROR in AbstractTest::seekPos(): "
                           "data source not set!\n");
            return;
        }
    }
}

int8_t AbstractTest::getNextBit()
{
    switch (dataSrcType) {
        case dsMemory : {
            if ((curBlockPointer == endBlockPointer) &&
                (curSubIdx == endBlockCnt * 8)) {
                fprintf(stderr,"ERROR in AbstractTest::getNextBit(): "
                               "end of data!\n");
                return - 1;
            }
            //int8_t nextBit = (curBlockVal >> curSubIdx) & 1;
            // MSB first as in NIST suite
            int8_t nextBit = ((curBlockVal >> (curSubIdx & ~0x7)) >> (7 - (curSubIdx & 7))) & 1;
            curSubIdx = (curSubIdx + 1) & 63;
            if (curSubIdx == 0) {
                if ((++curBlockPointer) != endBlockPointer)
                    curBlockVal = *curBlockPointer;
                else if (endBlockCnt > 0)
                    memcpy(&curBlockVal,curBlockPointer,endBlockCnt);
                else
                    curBlockVal = 0;
            }
            return nextBit;
        }
        default : {
            fprintf(stderr,"ERROR in AbstractTest::getNextBit(): "
                           "data source not set!\n");
            return - 1;
        }
    }
}

void AbstractTest::setResultVector(vector<double> *_pValues)
{
    pValues = _pValues;
}

vector<double>* AbstractTest::getResultVector()
{
    return pValues;
}



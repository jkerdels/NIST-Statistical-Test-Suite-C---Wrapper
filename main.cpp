/*
 * File:   main.cpp
 * Author: jk
 *
 * Created on 11. April 2011, 23:53
 */

#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

#include <inttypes.h>

#include "AbstractTest.h"
#include "FrequencyTest.h"
#include "BlockFrequencyTest.h"
#include "RunsTest.h"
#include "LongestRunOfOnesTest.h"
#include "RankTest.h"
#include "DiscreteFourierTransformTest.h"
#include "NonOverlappingTemplateMatchingTest.h"
#include "OverlappingTemplateMatchingTest.h"
#include "MaurersTest.h"
#include "LinearComplexityTest.h"
#include "SerialTest.h"
#include "ApproximateEntropyTest.h"
#include "CumulativeSumsTest.h"
#include "RandomExcursionsTest.h"
#include "RandomExcursionVariantTest.h"

int main(int argc, char** argv)
{
	// print help if no parameters are provided
	if (argc == 1) {
		printf("Usage: %s [OPTIONS]\n\n",argv[0]);
		printf("Options:\n"
		       "         -i [inputfiles]\n"
			   "            one or more input files with random data to test\n"
			   "            1.000.000 Bits per file recommended to provide\n"
               "            enough data for all tests\n\n"
			   "         -A\n"
               "            run all tests with default parameters\n"
               "            for detailed information please read the excellent\n"
               "            STS manual of NIST\n\n"
			   "         -o [outputfile]\n"
			   "            the results will be formated as columns separated\n"
               "            by a delimiter specified with -d or space if not\n"
               "            specified\n\n"
			   "         -d [delimiter char] (optional)\n"
			   "            specifies the delimiter to use in the output file\n\n");
		return 0;
	}

	// parameter vars
	vector<FILE*> inputfiles;
	char colDelimiter = ' ';
	FILE *outputfile  = NULL;
	bool useDefaultParams = false;

	// parse parameters
	int32_t i = 1;
	while (i < argc) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {

				// get input data
				case 'i' : {
					++i;
					while ((i < argc) && (argv[i][0] != '-')) {
						FILE *tmpfile = fopen(argv[i],"rb");
						if (tmpfile)
							inputfiles.push_back(tmpfile);
						++i;
					}
					--i;
				} break;

				// enable use of default parameters
				case 'A' : {
					useDefaultParams = true;
				} break;

				// get output file
				case 'o' : {
					++i;
					if (i < argc)
						outputfile = fopen(argv[i],"wb");
				} break;

				// get custom delimiter
				case 'd' : {
					++i;
					if (i < argc)
						colDelimiter = argv[i][0];
				} break;

				// unknown parameter
				default : {
					printf("Unknown parameter: %s\n",argv[i]);
				} break;
			}
		}
		++i;
	}

	// check input params

	if ((inputfiles.size() > 0) &&
        (outputfile != NULL) &&
        ((useDefaultParams == true) ||
         (false /* add check for parameter-file later */)))
	{
		// prepare tests
		uint32_t testDataSize = 0;
		uint8_t *testdata     = 0;
		vector<AbstractTest*> tests;
		vector<double> resultVec;
		if (useDefaultParams) {
			// set up default test
			tests.push_back(new FrequencyTest());
			tests.push_back(new BlockFrequencyTest());
			tests.push_back(new RunsTest());
			tests.push_back(new LongestRunOfOnesTest());
			tests.push_back(new RankTest());
			tests.push_back(new DiscreteFourierTransformTest());
			tests.push_back(new NonOverlappingTemplateMatchingTest());
			tests.push_back(new OverlappingTemplateMatchingTest());
			tests.push_back(new MaurersTest());
			tests.push_back(new LinearComplexityTest());
			tests.push_back(new SerialTest());
			tests.push_back(new ApproximateEntropyTest());
			tests.push_back(new CumulativeSumsTest());
			tests.push_back(new RandomExcursionsTest());
			tests.push_back(new RandomExcursionVariantTest());
			// set default test data size to 1.000.000 bits
			testDataSize = 125000;
			testdata = new uint8_t[testDataSize];
			vector<AbstractTest*>::iterator tit;
			for (tit = tests.begin(); tit != tests.end(); ++tit) {
				AbstractTest *curTest = *tit;
				curTest->setData(testdata,testDataSize);
				curTest->setResultVector(&resultVec);
			}
		} else {
			// set up test according to parameter file
		}
		// run tests
		if (testdata) {
			uint32_t inpCnt = 0;
			vector<FILE*>::iterator it;
			for (it = inputfiles.begin(); it != inputfiles.end(); ++it) {
				// read data
				uint32_t offset = 0;
				uint32_t rr     = 0;
				while ((rr < testDataSize) && (!feof(*it))) {
                	rr += fread(testdata+offset,1,testDataSize-rr,*it);
					offset += rr;
				}
				if (rr < testDataSize) {
					printf("Not enough data for input file nr. %u - skipping it.\n",inpCnt);
					continue;
				}
				// process data
				vector<AbstractTest*>::iterator tit;
				if (inpCnt == 0) {
                    for (tit = tests.begin(); tit != tests.end(); ++tit) {
                        AbstractTest *curTest = *tit;
                        if (inpCnt == 0) {
                            if (curTest->resultVectorNeeded()) {
                                resultVec.clear();
                                curTest->runTest();
                                uint32_t j;
                                for (j = 0; j < resultVec.size(); ++j)
                                    fprintf(outputfile,"%s%u%c",curTest->getTestName(),j,colDelimiter);
                            } else {
                                fprintf(outputfile,"%s%c",curTest->getTestName(),colDelimiter);
                            }
                        }
                    }
                    fprintf(outputfile,"\n");
				}
				for (tit = tests.begin(); tit != tests.end(); ++tit) {
					AbstractTest *curTest = *tit;
					resultVec.clear();
					double pValue = curTest->runTest();
					if (curTest->resultVectorNeeded()) {
						uint32_t j;
						if (curTest->testWasApplicable()) {
                            for (j = 0; j < resultVec.size(); ++j)
                                fprintf(outputfile,"%f%c",resultVec[j],colDelimiter);
                        } else {
                            for (j = 0; j < resultVec.size(); ++j)
                                fprintf(outputfile,"***%c",colDelimiter);
                        }
					} else {
                        if (curTest->testWasApplicable())
                            fprintf(outputfile,"%f%c",pValue,colDelimiter);
                        else
                            fprintf(outputfile,"***%c",colDelimiter);
					}
				}
                fprintf(outputfile,"\n");
				++inpCnt;
			}
		}
		// cleanup tests
		if (testdata)
			delete[] testdata;
		vector<AbstractTest*>::iterator tit;
		for (tit = tests.begin(); tit != tests.end(); ++tit) {
			delete *tit;
		}
	}

	// cleanup
	vector<FILE*>::iterator it;
	for (it = inputfiles.begin(); it != inputfiles.end(); ++it) {
		fclose(*it);
	}
	if (outputfile)
		fclose(outputfile);

    return 0;
}



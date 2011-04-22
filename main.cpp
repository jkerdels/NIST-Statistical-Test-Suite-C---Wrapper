/*
 * File:   main.cpp
 * Author: jk
 *
 * Created on 11. April 2011, 23:53
 */

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>

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

const uint32_t NrOfHistBins = 10;

int main(int argc, char** argv)
{
	// print help if no parameters are provided
	if (argc == 1) {
		printf("Usage: %s [OPTIONS]\n\n",argv[0]);
		printf("Options:\n"
		       "         -i [inputfiles]\n"
			   "            One or more input files with random data to test.\n"
			   "            1.000.000 x nrOfRuns (default: 100) Bits per file\n"
			   "            needed to provide enough data for all tests\n\n"
			   "         -o [outputfile]\n"
			   "            The results will be formated as columns separated\n"
               "            by a delimiter specified with -d or space if not\n"
               "            specified\n\n"
			   "         -d [delimiter char] (optional)\n"
			   "            Specifies the delimiter to use in the output file\n\n"
			   "         -s [sample size]\n"
			   "            Specifies the sample size in bits. default: 1.000.000\n\n"
               "         -r [nr of runs]\n"
               "            Specifies the number of runs, i.e. if you have an\n"
               "            alpha value of 0.01 then 10 fails in 1000 runs is the\n"
               "            expected number of fails. default: 100\n\n"
			   "         -a [alpha value]\n"
			   "            Specifies the alpha value which defines the threshold\n"
			   "            at which a random sequence is assumed to be non-random\n"
			   "            if its p-value is below the alpha threshold.\n"
			   "            Default: 0.01\n\n"
			   "         -P\n"
			   "            Print only p-values and do not compare to alpha value (default)\n\n"
			   "         -v\n"
			   "            Verbose output\n\n"
			   "         -t [tests to run]\n"
			   "            Bit vector to specify which test should be run.\n"
			   "            Available tests:\n"
			   "            ---------------------------------------\n"
			   "            00 - frequency\n"
			   "            01 - block frequency\n"
			   "            02 - runs\n"
			   "            03 - longest run of ones\n"
			   "            04 - rank\n"
			   "            05 - discrete fourier transform\n"
			   "            06 - non overlapping template matching\n"
			   "            07 - overlapping template matching\n"
			   "            08 - maurers\n"
			   "            09 - linear complexity\n"
			   "            10 - serial\n"
			   "            11 - approximate entropy\n"
			   "            12 - cumulative sums\n"
			   "            13 - random excursions\n"
			   "            14 - random excursions variant\n"
			   "            ---------------------------------------\n"
			   "            So, for example, if you want to run tests 0,1,5 and 8\n"
			   "            then the bit vector is 100100011\n"
			   "            Default: all tests selected\n\n");
		return 0;
	}
	// parameter vars
	vector<FILE*> inputfiles;
	char colDelimiter = ' ';
	FILE *outputfile  = NULL;
    uint32_t testDataSize = 125000;
    uint32_t nrOfRuns = 100;
    double   alpha = 0.01;
    bool pOnly = true;
    bool verbose = false;
    uint32_t selectedTests = 0xFFFFFFFF;
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

				// get sample size
				case 's' : {
                    ++i;
                    if (i < argc) {
                        int32_t tVal = atoi(argv[i]);
                        if (tVal > 0) {
                            testDataSize = tVal / 8;
                            if ((tVal & 7) > 0)
                                testDataSize++;
                        } else {
                            printf("Invalid size: %i --> using default value\n",tVal);
                        }
                    }
                } break;

				// get number of runs
				case 'r' : {
                    ++i;
                    if (i < argc) {
                        int32_t tVal = atoi(argv[i]);
                        if (tVal > 0) {
                            nrOfRuns = tVal;
                        } else {
                            printf("Invalid number of runs: %i --> using default value\n",tVal);
                        }
                    }
                } break;

				// get alpha value
				case 'a' : {
                    ++i;
                    if (i < argc) {
                        double tVal = atof(argv[i]);
                        if (tVal > 0) {
                            alpha = tVal;
                        } else {
                            printf("Invalid alpha value: %f --> using default value\n",tVal);
                        }
                    }
                } break;

				// enable P-Only
				case 'P' : {
					pOnly = true;
				} break;

				// enable verbose output
				case 'v' : {
					verbose = true;
				} break;

				// get number of runs
				case 't' : {
                    ++i;
                    if (i < argc)
                        selectedTests = strtoul(argv[i],0,2);
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
        (outputfile != NULL))
	{
		// prepare tests
		if (verbose) printf("+ preparing tests.\n");
		uint8_t *testdata = new uint8_t[testDataSize];
		vector<AbstractTest*> tests;
		vector<double> resultVec;
        // set up tests
        if (selectedTests & 0x0001)
            tests.push_back(new FrequencyTest());
        if (selectedTests & 0x0002)
            tests.push_back(new BlockFrequencyTest());
        if (selectedTests & 0x0004)
            tests.push_back(new RunsTest());
        if (selectedTests & 0x0008)
            tests.push_back(new LongestRunOfOnesTest());
        if (selectedTests & 0x0010)
            tests.push_back(new RankTest());
        if (selectedTests & 0x0020)
            tests.push_back(new DiscreteFourierTransformTest());
        if (selectedTests & 0x0040)
            tests.push_back(new NonOverlappingTemplateMatchingTest());
        if (selectedTests & 0x0080)
            tests.push_back(new OverlappingTemplateMatchingTest());
        if (selectedTests & 0x0100)
            tests.push_back(new MaurersTest());
        if (selectedTests & 0x0200)
            tests.push_back(new LinearComplexityTest());
        if (selectedTests & 0x0400)
            tests.push_back(new SerialTest());
        if (selectedTests & 0x0800)
            tests.push_back(new ApproximateEntropyTest());
        if (selectedTests & 0x1000)
            tests.push_back(new CumulativeSumsTest());
        if (selectedTests & 0x2000)
            tests.push_back(new RandomExcursionsTest());
        if (selectedTests & 0x4000)
            tests.push_back(new RandomExcursionVariantTest());
        // set data and result pointer
        vector<AbstractTest*>::iterator tit;
        for (tit = tests.begin(); tit != tests.end(); ++tit) {
            AbstractTest *curTest = *tit;
            curTest->setData(testdata,testDataSize);
            curTest->setResultVector(&resultVec);
        }
        // statistic data
        double *alphaSum = 0;
        double *failSum = 0;
        double *histograms = 0;

        uint32_t nrOfColumns = 0;

        double allAboveAlphaSum = 0;

		// run tests
		if (testdata) {
			uint32_t inpCnt = 0;
			uint32_t inpCnt2 = 0;
			vector<FILE*>::iterator it;
			for (it = inputfiles.begin(); it != inputfiles.end(); ++it) {
                if (verbose) printf("+ processing input file %u\n",inpCnt2);
                uint32_t r;
                for (r = 0; r < nrOfRuns; ++r) {
                    if (verbose) printf("++ run %u\n",r);
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
                                    nrOfColumns += resultVec.size();
                                } else {
                                    nrOfColumns++;
                                    fprintf(outputfile,"%s%c",curTest->getTestName(),colDelimiter);
                                }
                            }
                        }
                        fprintf(outputfile,"all_tests_above_alpha\n");
                        if ((!alphaSum) && (nrOfColumns)) {
                            alphaSum = new double[nrOfColumns];
                            memset(alphaSum,0,sizeof(double)*nrOfColumns);
                        }
                        if ((!failSum) && (nrOfColumns)) {
                            failSum = new double[nrOfColumns];
                            memset(failSum,0,sizeof(double)*nrOfColumns);
                        }
                        if ((!histograms) && (nrOfColumns) && (NrOfHistBins)) {
                            histograms = new double[nrOfColumns*NrOfHistBins];
                            memset(histograms,0,sizeof(double)*nrOfColumns*NrOfHistBins);
                        }

                    }
                    uint32_t testNr = 0;
                    bool allTestsAboveAlpha = true;
                    for (tit = tests.begin(); tit != tests.end(); ++tit) {
                        AbstractTest *curTest = *tit;
                        resultVec.clear();
                        if (verbose) printf("+++ test: %s ",curTest->getTestName());
                        double pValue = curTest->runTest();

                        if (curTest->resultVectorNeeded()) {
                            uint32_t j;
                            if (curTest->testWasApplicable()) {
                                if (verbose) printf("result: vector output omitted here\n");
                                for (j = 0; j < resultVec.size(); ++j) {
                                    if (pOnly)
                                        fprintf(outputfile,"%f%c",resultVec[j],colDelimiter);
                                    else
                                        fprintf(outputfile,"%u%c",(resultVec[j] < alpha) ? 0 : 1,colDelimiter);
                                    if (resultVec[j] < alpha) {
                                        allTestsAboveAlpha = false;
                                    } else {
                                        alphaSum[testNr] += 1;
                                    }
                                    uint32_t idx = (uint32_t)(floor(resultVec[j]*NrOfHistBins));
                                    if (idx >= NrOfHistBins)
                                        idx = NrOfHistBins-1;
                                    histograms[(testNr*NrOfHistBins)+idx] += 1;
                                    testNr++;
                                }
                            } else {
                                if (verbose) printf("result: not applicable\n");
                                for (j = 0; j < resultVec.size(); ++j) {
                                    fprintf(outputfile,"***%c",colDelimiter);
                                    failSum[testNr] += 1;
                                    testNr++;
                                }
                            }
                        } else {
                            if (curTest->testWasApplicable()) {
                                if (verbose) printf("result: %f\n",pValue);
                                if (pOnly)
                                    fprintf(outputfile,"%f%c",pValue,colDelimiter);
                                else
                                    fprintf(outputfile,"%u%c",(pValue < alpha) ? 0 : 1,colDelimiter);
                                if (pValue < alpha) {
                                    allTestsAboveAlpha = false;
                                } else {
                                    alphaSum[testNr] += 1;
                                }
                                uint32_t idx = (uint32_t)(floor(pValue*NrOfHistBins));
                                if (idx >= NrOfHistBins)
                                    idx = NrOfHistBins-1;
                                histograms[(testNr*NrOfHistBins)+idx] += 1;
                                testNr++;
                            } else {
                                if (verbose) printf("result: not applicable\n");
                                fprintf(outputfile,"***%c",colDelimiter);
                                failSum[testNr] += 1;
                                testNr++;
                            }
                        }
                    }

                    if (allTestsAboveAlpha) {
                        fprintf(outputfile,"1\n");
                        allAboveAlphaSum += 1;
                    } else {
                        fprintf(outputfile,"0\n");
                    }
                    ++inpCnt;
                }
                ++inpCnt2;
			}
		}
		// write alphaSums and histograms
        if ((alphaSum) && (failSum)) {
            fprintf(outputfile,"\n# AlphaSums normalized\n");
            uint32_t j;
            for (j = 0; j < nrOfColumns; ++j) {
                double normDiv = (double)(nrOfRuns)-failSum[j];
                if (normDiv != 0)
                    fprintf(outputfile,"%f%c",alphaSum[j]/normDiv,colDelimiter);
                else
                    fprintf(outputfile,"***%c",colDelimiter);
            }
            fprintf(outputfile,"%f\n",allAboveAlphaSum/(double)(nrOfRuns));
        }
		if ((histograms) && (failSum)){
            fprintf(outputfile,"\n# Histograms\n");
            uint32_t j,k;
            for (k = 0; k < NrOfHistBins; ++k) {
                for (j = 0; j < nrOfColumns; ++j) {
                    double normDiv = (double)(nrOfRuns)-failSum[j];
                    if (normDiv != 0)
                        fprintf(outputfile,"%f%c",histograms[(j*NrOfHistBins)+k]/normDiv,colDelimiter);
                    else
                        fprintf(outputfile,"***%c",colDelimiter);
                }
                fprintf(outputfile,"\n");
            }
        }

		if (verbose) printf("+ cleanup\n");
		// cleanup tests
		if (testdata)
			delete[] testdata;
		for (tit = tests.begin(); tit != tests.end(); ++tit) {
			delete *tit;
		}
		if (alphaSum)
            delete[] alphaSum;
		if (failSum)
            delete[] failSum;
		if (histograms)
            delete[] histograms;
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



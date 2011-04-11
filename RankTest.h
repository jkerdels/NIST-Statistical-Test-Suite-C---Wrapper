/* 
 * File:   RankTest.h
 * Author: jk
 *
 * Created on 15. August 2010, 17:44
 */

#ifndef RANKTEST_H
#define	RANKTEST_H

#include "AbstractTest.h"

class RankTest : public AbstractTest
{
public:
    RankTest();
    ~RankTest();

    double runTest();

private:

};

#endif	/* RANKTEST_H */


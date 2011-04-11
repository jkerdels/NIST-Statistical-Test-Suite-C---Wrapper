/* 
 * File:   MaurersTest.h
 * Author: jk
 *
 * Created on 13. Dezember 2010, 21:34
 */

#ifndef MAURERSTEST_H
#define	MAURERSTEST_H

#include <inttypes.h>

#include "AbstractTest.h"

class MaurersTest : public AbstractTest
{
public:
    MaurersTest();
    ~MaurersTest();

    double runTest();

private:

};

#endif	/* MAURERSTEST_H */


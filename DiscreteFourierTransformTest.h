/* 
 * File:   DiscreteFourierTransformTest.h
 * Author: jk
 *
 * Created on 15. August 2010, 19:35
 */

#ifndef DISCRETEFOURIERTRANSFORMTEST_H
#define	DISCRETEFOURIERTRANSFORMTEST_H

#include "AbstractTest.h"

class DiscreteFourierTransformTest : public AbstractTest
{
public:
    DiscreteFourierTransformTest();
    ~DiscreteFourierTransformTest();

    double runTest();

	const char* getTestName() {return "DiscreteFourierTransform";}
    
private:

};

#endif	/* DISCRETEFOURIERTRANSFORMTEST_H */


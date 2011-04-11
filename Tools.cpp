/* 
 * File:   Tools.cpp
 * Author: jk
 * 
 * Created on 16. August 2010, 20:50
 */

#include "Tools.h"

double Tools::MAX(double x, double y)
{
    return (x < y) ? y : x;
}

double Tools::MIN(double x, double y)
{
    return (x > y) ? y : x;
}

bool Tools::isNonPositive(double x)
{
    return (x <= 0.e0);
}

bool Tools::isPositive(double x)
{
    return (x >  0.e0);
}

bool Tools::isNegative(double x)
{
    return (x <  0.e0);
}

bool Tools::isGreaterThanOne(double x)
{
    return (x >  1.e0);
}

bool Tools::isZero(double x)
{
    return (x == 0.e0);
}

bool Tools::isOne(double x)
{
    return (x == 1.e0);
}




int Tools::MAX(int x, int y)
{
    return (x < y) ? y : x;
}

int Tools::MIN(int x, int y)
{
    return (x > y) ? y : x;
}

bool Tools::isNonPositive(int x)
{
    return (x <= 0.e0);
}

bool Tools::isPositive(int x)
{
    return (x >  0.e0);
}

bool Tools::isNegative(int x)
{
    return (x <  0.e0);
}

bool Tools::isGreaterThanOne(int x)
{
    return (x >  1.e0);
}

bool Tools::isZero(int x)
{
    return (x == 0.e0);
}

bool Tools::isOne(int x)
{
    return (x == 1.e0);
}

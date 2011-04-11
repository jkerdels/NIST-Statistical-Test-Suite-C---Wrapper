/* 
 * File:   Tools.h
 * Author: jk
 *
 * Created on 16. August 2010, 20:50
 */

#ifndef TOOLS_H
#define	TOOLS_H

class Tools {
public:

static double MAX(double x, double y);
static double MIN(double x, double y);
static bool   isNonPositive(double x);
static bool   isPositive(double x);
static bool   isNegative(double x);
static bool   isGreaterThanOne(double x);
static bool   isZero(double x);
static bool   isOne(double x);

static int MAX(int x, int y);
static int MIN(int x, int y);
static bool   isNonPositive(int x);
static bool   isPositive(int x);
static bool   isNegative(int x);
static bool   isGreaterThanOne(int x);
static bool   isZero(int x);
static bool   isOne(int x);

private:

};

#endif	/* TOOLS_H */


/* 
 * File:   Cephes.h
 * Author: jk
 *
 * Created on 15. August 2010, 10:54
 */

#ifndef CEPHES_H
#define	CEPHES_H

class Cephes
{

    static const double	rel_error;

    static const double MACHEP;	// 2**-53
    static const double MAXLOG;	// log(MAXNUM)
    static const double MAXNUM;	// 2**1024*(1-MACHEP)
    static const double PI;	// pi, duh!

    static const double big;
    static const double biginv;

    static int sgngam;

public:
    Cephes();
    ~Cephes();
    
    static double cephes_igamc(double a, double x);
    static double cephes_igam(double a, double x);
    static double cephes_lgam(double x);
    static double cephes_p1evl(double x, double *coef, int N);
    static double cephes_polevl(double x, double *coef, int N);
    static double cephes_erf(double x);
    static double cephes_erfc(double x);
    static double cephes_normal(double x);

private:

};

#endif	/* CEPHES_H */


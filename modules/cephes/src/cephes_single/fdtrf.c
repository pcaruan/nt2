/*							fdtrf.c
 *
 *	F distribution
 *
 *
 *
 * SYNOPSIS:
 *
 * int df1, df2;
 * float x, y, cephes_fdtrf();
 *
 * y = cephes_fdtrf( df1, df2, x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the area from zero to x under the F density
 * function (also known as Snedcor's density or the
 * variance ratio density).  This is the density
 * of x = (u1/df1)/(u2/df2), where u1 and u2 are random
 * variables having Chi square distributions with df1
 * and df2 degrees of freedom, respectively.
 *
 * The incomplete beta integral is used, according to the
 * formula
 *
 *	P(x) = incbet( df1/2, df2/2, (df1*x/(df2 + df1*x) ).
 *
 *
 * The arguments a and b are greater than zero, and x
 * x is nonnegative.
 * ACCURACY:
 *
 *        Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE       0,100       5000       2.2e-5      1.1e-6
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * fdtrf domain    a<0, b<0, x<0         0.0
 *
 */
/*							cephes_fdtrcf()
 *
 *	Complemented F distribution
 *
 *
 *
 * SYNOPSIS:
 *
 * int df1, df2;
 * float x, y, cephes_fdtrcf();
 *
 * y = cephes_fdtrcf( df1, df2, x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the area from x to infinity under the F density
 * function (also known as Snedcor's density or the
 * variance ratio density).
 *
 *
 *                      inf.
 *                       -
 *              1       | |  a-1      b-1
 * 1-P(x)  =  ------    |   t    (1-t)    dt
 *            B(a,b)  | |
 *                     -
 *                      x
 *
 * (See fdtr.c.)
 *
 * The incomplete beta integral is used, according to the
 * formula
 *
 *	P(x) = incbet( df2/2, df1/2, (df2/(df2 + df1*x) ).
 *
 *
 * ACCURACY:
 *
 *        Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE       0,100       5000       7.3e-5      1.2e-5
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * fdtrcf domain   a<0, b<0, x<0         0.0
 *
 */
/*							cephes_fdtrif()
 *
 *	Inverse of complemented F distribution
 *
 *
 *
 * SYNOPSIS:
 *
 * float df1, df2, x, y, cephes_fdtrif();
 *
 * x = cephes_fdtrif( df1, df2, y );
 *
 *
 *
 *
 * DESCRIPTION:
 *
 * Finds the F density argument x such that the integral
 * from x to infinity of the F density is equal to the
 * given probability y.
 *
 * This is accomplished using the inverse beta integral
 * function and the relations
 *
 *      z = incbi( df2/2, df1/2, y )
 *      x = df2 (1-z) / (df1 z).
 *
 * Note: the following relations hold for the inverse of
 * the uncomplemented F distribution:
 *
 *      z = incbi( df1/2, df2/2, y )
 *      x = df2 z / (df1 (1-z)).
 *
 *
 *
 * ACCURACY:
 *
 * arithmetic   domain     # trials      peak         rms
 *        Absolute error:
 *    IEEE       0,100       5000       4.0e-5      3.2e-6
 *        Relative error:
 *    IEEE       0,100       5000       1.2e-3      1.8e-5
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * fdtrif domain  y <= 0 or y > 1       0.0
 *                     v < 1
 *
 */


/*
Cephes Math Library Release 2.2:  July, 1992
Copyright 1984, 1987, 1992 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/


#include "mconf.h"

#ifdef ANSIC
float cephes_incbetf(float, float, float);
float cephes_incbif(float, float, float);
#else
float cephes_incbetf(), cephes_incbif();
#endif

#ifdef ANSIC
float cephes_fdtrcf( int ia, int ib, float xx )
#else
float cephes_fdtrcf( ia, ib, xx )
int ia, ib;
double xx;
#endif
{
float x, a, b, w;

x = xx;
if( (ia < 1) || (ib < 1) || (x < 0.0f) )
	{
	cephes_mtherr( "fdtrcf", DOMAIN );
	return( 0.0f );
	}
a = ia;
b = ib;
w = b / (b + a * x);
return( cephes_incbetf( 0.5f*b, 0.5f*a, w ) );
}



#ifdef ANSIC
float cephes_fdtrf( int ia, int ib, int xx )
#else
float cephes_fdtrf( ia, ib, xx )
int ia, ib;
double xx;
#endif
{
float x, a, b, w;

x = xx;
if( (ia < 1) || (ib < 1) || (x < 0.0f) )
	{
	cephes_mtherr( "fdtrf", DOMAIN );
	return( 0.0f );
	}
a = ia;
b = ib;
w = a * x;
w = w / (b + w);
return( cephes_incbetf( 0.5f*a, 0.5f*b, w) );
}


#ifdef ANSIC
float cephes_fdtrif( int ia, int ib, float yy )
#else
float cephes_fdtrif( ia, ib, yy )
int ia, ib;
double yy;
#endif
{
float y, a, b, w, x;

y = yy;
if( (ia < 1) || (ib < 1) || (y <= 0.0f) || (y > 1.0f) )
	{
	cephes_mtherr( "fdtrif", DOMAIN );
	return( 0.0f );
	}
a = ia;
b = ib;
w = cephes_incbif( 0.5f*b, 0.5f*a, y );
x = (b - b*w)/(a*w);
return(x);
}

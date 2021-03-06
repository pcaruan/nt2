/*							cephes_igami()
 *
 *      Inverse of complemented incomplete gamma integral
 *
 *
 *
 * SYNOPSIS:
 *
 * double a, x, p, cephes_igami();
 *
 * x = cephes_igami( a, p );
 *
 * DESCRIPTION:
 *
 * Given p, the function finds x such that
 *
 *  cephes_igamc( a, x ) = p.
 *
 * It is valid in the right-hand tail of the distribution, p < 0.5.
 * Starting with the approximate value
 *
 *         3
 *  x = a t
 *
 *  where
 *
 *  t = 1 - d - cephes_ndtri(p) cephes_sqrt(d)
 * 
 * and
 *
 *  d = 1/9a,
 *
 * the routine performs up to 10 Newton iterations to find the
 * root of cephes_igamc(a,x) - p = 0.
 *
 * ACCURACY:
 *
 * Tested at random a, p in the intervals indicated.
 *
 *                a        p                      Relative error:
 * arithmetic   domain   domain     # trials      peak         rms
 *    IEEE     0.5,100   0,0.5       100000       1.0e-14     1.7e-15
 *    IEEE     0.01,0.5  0,0.5       100000       9.0e-14     3.4e-15
 *    IEEE    0.5,10000  0,0.5        20000       2.3e-13     3.8e-14
 */

/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
*/

#include "mconf.h"

extern double MACHEP, MAXNUM, MAXLOG, MINLOG;
#ifdef ANSIPROT
extern double cephes_igamc ( double, double );
extern double cephes_ndtri ( double );
extern double cephes_exp ( double );
extern double fabs ( double );
extern double cephes_log ( double );
extern double cephes_sqrt ( double );
extern double cephes_lgam ( double );
#else
double cephes_igamc(), cephes_ndtri(), cephes_exp(), fabs(), cephes_log(), cephes_sqrt(), cephes_lgam();
#endif

double cephes_igami( a, y0 )
double a, y0;
{
double x0, x1, x, yl, yh, y, d, lgm, dithresh;
int i, dir;

 if( y0 > 0.5)
 	cephes_mtherr( "igami", PLOSS );

/* bound the solution */
x0 = MAXNUM;
yl = 0;
x1 = 0;
yh = 1.0;
dithresh = 5.0 * MACHEP;

/* approximation to inverse function */
d = 1.0/(9.0*a);
y = ( 1.0 - d - cephes_ndtri(y0) * cephes_sqrt(d) );
x = a * y * y * y;

lgm = cephes_lgam(a);

for( i=0; i<10; i++ )
	{
	if( x > x0 || x < x1 )
		goto ihalve;
	y = cephes_igamc(a,x);
	if( y < yl || y > yh )
		goto ihalve;
	if( y < y0 )
		{
		x0 = x;
		yl = y;
		}
	else
		{
		x1 = x;
		yh = y;
		}
/* compute the derivative of the function at this point */
	d = (a - 1.0) * cephes_log(x) - x - lgm;
	if( d < -MAXLOG )
		goto ihalve;
	d = -cephes_exp(d);
/* compute the step to the next approximation of x */
	d = (y - y0)/d;
	if( fabs(d/x) < MACHEP )
		goto done;
	x = x - d;
	}

/* Resort to interval halving if Newton iteration did not converge. */
ihalve:

d = 0.0625;
if( x0 == MAXNUM )
	{
	if( x <= 0.0 )
		x = 1.0;
	while( x0 == MAXNUM )
		{
		x = (1.0 + d) * x;
		y = cephes_igamc( a, x );
		if( y < y0 )
			{
			x0 = x;
			yl = y;
			break;
			}
		d = d + d;
		}
	}
d = 0.5;
dir = 0;

for( i=0; i<400; i++ )
	{
	x = x1  +  d * (x0 - x1);
	y = cephes_igamc( a, x );
	lgm = (x0 - x1)/(x1 + x0);
	if( fabs(lgm) < dithresh )
		break;
	lgm = (y - y0)/y0;
	if( fabs(lgm) < dithresh )
		break;
	if( x <= 0.0 )
		break;
	if( y >= y0 )
		{
		x1 = x;
		yh = y;
		if( dir < 0 )
			{
			dir = 0;
			d = 0.5;
			}
		else if( dir > 1 )
			d = 0.5 * d + 0.5; 
		else
			d = (y0 - yl)/(yh - yl);
		dir += 1;
		}
	else
		{
		x0 = x;
		yl = y;
		if( dir > 0 )
			{
			dir = 0;
			d = 0.5;
			}
		else if( dir < -1 )
			d = 0.5 * d;
		else
			d = (y0 - yl)/(yh - yl);
		dir -= 1;
		}
	}
if( x == 0.0 )
	cephes_mtherr( "igami", UNDERFLOW );

done:
return( x );
}

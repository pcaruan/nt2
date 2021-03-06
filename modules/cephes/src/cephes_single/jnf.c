/*							jnf.c
 *
 *	Bessel function of integer order
 *
 *
 *
 * SYNOPSIS:
 *
 * int n;
 * float x, y, cephes_jnf();
 *
 * y = cephes_jnf( n, x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns Bessel function of order n, where n is a
 * (possibly negative) integer.
 *
 * The ratio of jn(x) to j0(x) is computed by backward
 * recurrence.  First the ratio jn/jn-1 is found by a
 * continued fraction expansion.  Then the recurrence
 * relating successive orders is applied until j0 or j1 is
 * reached.
 *
 * If n = 0 or 1 the routine for j0 or j1 is called
 * directly.
 *
 *
 *
 * ACCURACY:
 *
 *                      Absolute error:
 * arithmetic   range      # trials      peak         rms
 *    IEEE      0, 15       30000       3.6e-7      3.6e-8
 *
 *
 * Not suitable for large n or x. Use cephes_jvf() instead.
 *
 */

/*							jn.c
Cephes Math Library Release 2.2:  June, 1992
Copyright 1984, 1987, 1992 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/
#include "mconf.h"

extern float MACHEPF;

#ifdef ANSIC
float cephes_j0f(float), cephes_j1f(float);

float cephes_jnf( int n, float xx )
#else
float cephes_j0f(), cephes_j1f();

float cephes_jnf( n, xx )
int n;
double xx;
#endif
{
float x, pkm2, pkm1, pk, xk, r, ans, xinv, sign;
int k;

x = xx;
sign = 1.0;
if( n < 0 )
	{
	n = -n;
	if( (n & 1) != 0 )	/* -1**n */
		sign = -1.0;
	}

if( n == 0 )
	return( sign * cephes_j0f(x) );
if( n == 1 )
	return( sign * cephes_j1f(x) );
if( n == 2 )
	return( sign * (2.0f * cephes_j1f(x) / x  -  cephes_j0f(x)) );

/*
if( x < MACHEPF )
	return( 0.0f );
*/

/* continued fraction */
k = 24;
pk = 2 * (n + k);
ans = pk;
xk = x * x;

do
	{
	pk -= 2.0f;
	ans = pk - (xk/ans);
	}
while( --k > 0 );
/*ans = x/ans;*/

/* backward recurrence */

pk = 1.0f;
/*pkm1 = 1.0f/ans;*/
xinv = 1.0f/x;
pkm1 = ans * xinv;
k = n-1;
r = (float )(2 * k);

do
	{
	pkm2 = (pkm1 * r  -  pk * x) * xinv;
	pk = pkm1;
	pkm1 = pkm2;
	r -= 2.0f;
	}
while( --k > 0 );

r = pk;
if( r < 0 )
	r = -r;
ans = pkm1;
if( ans < 0 )
	ans = -ans;

if( r > ans )  /* if( fabs(pk) > fabs(pkm1) ) */
	ans = sign * cephes_j1f(x)/pk;
else
	ans = sign * cephes_j0f(x)/pkm1;
return( ans );
}

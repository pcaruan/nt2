/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::sum1 function"

#include <nt2/table.hpp>
#include <nt2/include/functions/asum1.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/two.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( asum1_scalar, (float)(double))//NT2_TYPES )
{
  T x = nt2::asum1(T(42));
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::asum1(T(42),1);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::asum1(T(42),0);
  NT2_TEST_EQUAL( x, T(42) );

}

NT2_TEST_CASE_TPL( asum1, (float)(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy( nt2::of_size(1,3) );
  nt2::table<T> sz( nt2::of_size(1,3) );


  for(int j=1;j<=size(sy, 2);j++)
    for(int i=1;i<=size(sy, 1);i++)
      y(i,j) = i - j;

  sy = nt2::asum1(y);
  sz = nt2::sum(nt2::abs(y));
  for(int j=1;j<=size(y, 2);j++)
      NT2_TEST_EQUAL(sz(j), sy(j));
  sy = nt2::asum1(y, 1);
  sz = nt2::sum(nt2::abs(y), 1);
  for(int j=1;j<=size(y, 2);j++)
      NT2_TEST_EQUAL(sz(j), sy(j));
  sy = nt2::asum1(y, 2);
  sz = nt2::sum(nt2::abs(y), 2);
    for(int i=1;i<=size(y, 1);i++)
      NT2_TEST_EQUAL(sz(i), sy(i));
  sy = nt2::asum1(y, 3);
  sz = nt2::sum(nt2::abs(y), 3);
  for(int j=1;j<=size(y, 2);j++)
    for(int i=1;i<=size(y, 1);i++)
      NT2_TEST_EQUAL(sz(i, j), sy(i, j));


  sy = nt2::asum1(y(_));
  sz = nt2::sum(nt2::abs(y(_)));
  display(sy);
  NT2_TEST_EQUAL(sy(1), sz(1));

  {
    nt2::table<T> z = nt2::ones(1, 3, nt2::meta::as_<T>());
    typedef typename nt2::meta::as_integer<T>::type itype;
    nt2::table<itype> z1 = nt2::Two<itype>()*nt2::ones(1, 3, nt2::meta::as_<itype>());
    nt2::table<T> z2 = nt2::rec(z1)*z;
//     nt2::table<T> z3 = if_else(is_eqz(z2), z2, nt2::Two<T>());
//    nt2::table<T> z3 = if_else(is_eqz(z2), z2, nt2::Two<T>()*nt2::ones(1, 3, nt2::meta::as_<T>()));
    {
      nt2::table<T> z, z1, z2;
      z2 =  nt2::zeros(1, 3, nt2::meta::as_<T>());
      z1=  nt2::ones(1, 3, nt2::meta::as_<T>());
      nt2::table<T> z3= nt2::if_else(nt2::is_eqz(z2), z1, z2);
      NT2_DISPLAY(z3);
      nt2::table<T> z4 = nt2::if_else(nt2::is_eqz(z2), z2, nt2::Two<T>());
      NT2_DISPLAY(z4);
    }
  }

}


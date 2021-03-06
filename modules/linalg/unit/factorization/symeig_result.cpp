//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - symeig_result factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/symeig.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/rif.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(symeig_result, NT2_REAL_TYPES)
{
  using nt2::_;
  typedef typename nt2::meta::as_integer<T, signed>::type itype_t;
  typedef nt2::table<T> t_t;
  typedef nt2::table<itype_t> it_t;
  t_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());
  //  b(_, 1) = b(_, 3);
  nt2::details::symeig_result<t_t> f(b, 'V', 'U');

  nt2::display("b     ", b);
  nt2::display("values", f.values());
  t_t w  = f.w();
  nt2::display("w    ", w);
  t_t v = f.v();
  nt2::display("v    ", v);
  t_t c  = f.cond();
  nt2::display("c    ", c);
  it_t r  = f.rank();
  nt2::display("r    ", r);
 //  std::cout << "asbdet       " << f.absdet()<< std::endl;
//   std::cout << "rank         " << f.rank()  << std::endl;
//   t_t bb = nt2::rif(4, 1, nt2::meta::as_<T>());
//   t_t x = f.solve(bb);
//   nt2::display("bb    ", bb);
//   nt2::display("x    ", x);
}

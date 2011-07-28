/*******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SCALAR_FACTORIAL_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SCALAR_FACTORIAL_HPP_INCLUDED
#include <nt2/include/functions/gamma.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/abss.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(tag::factorial_, tag::cpu_,
		      (A0),
		      (scalar_ < arithmetic_<A0> > )
		      )
  {
    typedef A0  result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::result_of<floating(A0)>::type ftype; 
      const ftype r = nt2::gamma(nt2::trunc(nt2::abss(a0))+One<result_type>());
      return r > Valmax<A0>() ? Inf<A0>() : r; 
    }
  };
} }
#endif
//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_TRUNC_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_TRUNC_HPP_INCLUDED

#include <nt2/include/functions/floor.hpp>
#include <nt2/include/functions/ceil.hpp>
#include <nt2/sdk/meta/strip.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for trunc

  /////////////////////////////////////////////////////////////////////////////
  // Compute trunc(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<trunc_,tag::scalar_(tag::arithmetic_),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      if (a0 > 0) return nt2::floor(a0);  else return nt2::ceil(a0); 
    }

  };
} }

#endif
/// Revised by jt the 13/11/2010

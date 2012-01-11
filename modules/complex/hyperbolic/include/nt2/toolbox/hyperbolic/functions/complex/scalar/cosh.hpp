//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_SCALAR_COSH_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_SCALAR_COSH_HPP_INCLUDED
#include <nt2/include/functions/cosh.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/cosh.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <complex>
#include <cmath>

//cosh(x + iy) = cosh(x)cos(y) + i(sinh(x)sin(y)) 
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cosh_, tag::cpu_, (A0)
                            , (scalar_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return std::cosh(a0); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cosh_, tag::cpu_, (A0)
                            , (scalar_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::cos(imag(a0)); 
    }
  };
  
} }

#endif

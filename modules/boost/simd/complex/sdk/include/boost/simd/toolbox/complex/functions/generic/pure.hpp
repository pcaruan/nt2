//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_COMPLEX_FUNCTIONS_GENERIC_PURE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_COMPLEX_FUNCTIONS_GENERIC_PURE_HPP_INCLUDED
#include <boost/simd/toolbox/complex/functions/pure.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/sdk/complex/imaginary.hpp>
#include <boost/simd/sdk/complex/meta/as_real.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::pure_, tag::cpu_, (A0)
                            , (generic_< arithmetic_<A0> >)
                            )
  {
    typedef typename meta::as_imaginary<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& ) const
    {
      return result_type(Zero<A0>()); //TODO this must return a constant of result_type
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::pure_, tag::cpu_, (A0)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };
  
} } }

#endif
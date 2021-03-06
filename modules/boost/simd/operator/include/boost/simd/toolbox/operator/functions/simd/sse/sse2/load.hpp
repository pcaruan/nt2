//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_LOAD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_LOAD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
////////////////////////////////////////////////////////////////////////////////
// load for SSE2 SIMD types
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/toolbox/operator/functions/load.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_ , boost::simd::tag::sse2_
                            , (A0)(A1)(A2)
                            , (iterator_< scalar_< double_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< double_<A2>, boost::simd::tag::sse_ > >))
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&)const
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(a0+a1,sizeof(result_type))
      , "load has been called on a pointer which alignment is not "
        "compatible with current SIMD extension."
      );
      
      result_type
      that = { _mm_load_pd(a0+a1) };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_ , boost::simd::tag::sse2_
                            , (A0)(A1)(A2)
                            , (iterator_< scalar_< single_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< single_<A2>, boost::simd::tag::sse_ > >))
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1,
                                  const A2&)const
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(a0+a1,sizeof(result_type))
      , "load has been called on a pointer which alignment is not "
        "compatible with current SIMD extension."
      );
      
      result_type
      that = { _mm_load_ps(a0+a1) };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_ , boost::simd::tag::sse2_
                            , (A0)(A1)(A2)
                            , (iterator_< scalar_< integer_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< integer_<A2>, boost::simd::tag::sse_ > >))
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1,
                                  const A2&)const
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(a0+a1,sizeof(result_type))
      , "load has been called on a pointer which alignment is not "
        "compatible with current SIMD extension."
      );
      
      result_type
      that = { _mm_load_si128(reinterpret_cast<__m128i const*>(a0 + a1)) };
      return that;
    }
  };

} } }


#include <boost/simd/toolbox/operator/functions/simd/sse/sse2/details/load_offset.hpp>

#endif
#endif

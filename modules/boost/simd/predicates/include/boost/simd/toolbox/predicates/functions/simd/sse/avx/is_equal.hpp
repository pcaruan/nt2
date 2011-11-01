//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_SSE_AVX_IS_EQUAL_TO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_SSE_AVX_IS_EQUAL_TO_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/toolbox/predicates/functions/is_equal.hpp>
#include <boost/simd/sdk/simd/native_cast.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_equal_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                              ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::scalar_of<A0>::type   sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
      svtype a00 = { _mm256_extractf128_si256(a0, 0)};
      svtype a10 = { _mm256_extractf128_si256(a1, 0)};
      svtype  r0 = native_cast<svtype>(eq(a00,a10));
      result_type that  = {_mm256_insertf128_si256(that, r0, 0)};
      svtype a01 = { _mm256_extractf128_si256(a0, 1)};
      svtype a11 = { _mm256_extractf128_si256(a1, 1)};
      svtype r1 = native_cast<svtype>(eq(a01,a11));
      that = native_cast<result_type>(_mm256_insertf128_si256(that, r1, 1));
      return that;
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_equal_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<double_<A0>,boost::simd::tag::avx_>))
                              ((simd_<double_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      result_type that = native_cast<result_type>(_mm256_cmp_pd(a0,a1, _CMP_EQ_OQ));
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_equal_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<single_<A0>,boost::simd::tag::avx_>))
                              ((simd_<single_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      result_type that = native_cast<result_type>(_mm256_cmp_ps(a0,a1, _CMP_EQ_OQ));
      return that;
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_equal_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                              ((simd_<double_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      result_type that = native_cast<result_type>(_mm_cmp_pd(a0,a1, _CMP_EQ_OQ));
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_equal_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                              ((simd_<single_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      result_type that = native_cast<result_type>( _mm_cmp_ps(a0,a1, _CMP_EQ_OQ));
      return that;
    }
  };

} } }

#endif
#endif

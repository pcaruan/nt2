//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_HMSB_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_HMSB_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::hmsb_, tag::cpu_,
                       (A0),
                       ((simd_(tag::arithmetic_<A0>,tag::see_)))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::hmsb_(tag::simd_(tag::arithmetic_, tag::see_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      {
      typedef typename meta::as_integer<typename meta::scalar_of<A0>::type>::type type;
      };

    NT2_FUNCTOR_CALL(1)
    {
      return _mm_movemask_epi8(a0);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::hmsb_, tag::cpu_,
                       (A0),
                       ((simd_(tag::double_<A0>,tag::see_)))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::hmsb_(tag::simd_(tag::double_, tag::see_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      {
      typedef typename meta::as_integer<typename meta::scalar_of<A0>::type>::type type;
      };

    NT2_FUNCTOR_CALL(1){ return _mm_movemask_pd(a0); }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::hmsb_, tag::cpu_,
                       (A0),
                       ((simd_(tag::float_<A0>,tag::see_)))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::hmsb_(tag::simd_(tag::float_, tag::see_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      {
      typedef typename meta::as_integer<typename meta::scalar_of<A0>::type>::type type;
      };

    NT2_FUNCTOR_CALL(1){ return _mm_movemask_ps(a0); }
  };
} }

#endif
// modified by jt the 04/01/2011
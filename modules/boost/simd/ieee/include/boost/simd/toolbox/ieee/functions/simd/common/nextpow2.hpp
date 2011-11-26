//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_NEXTPOW2_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_NEXTPOW2_HPP_INCLUDED
#include <boost/simd/include/constants/half.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/include/functions/seladd.hpp>
#include <boost/simd/include/functions/frexp.hpp>
#include <boost/simd/include/functions/group.hpp>
#include <boost/simd/include/functions/split.hpp>
#include <boost/simd/include/functions/firstbitset.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::nextpow2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type utype;
      return simd::native_cast<A0>(nextpow2(simd::native_cast<utype >(abs(a0))));
      }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::nextpow2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<unsigned_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_floating<A0>::type rtype;
      typedef typename dispatch::meta::as_integer<A0, signed>::type itype;
      rtype m;
      itype p;
      frexp(tofloat(a0), m, p);
      return simd::native_cast<A0>(seladd(boost::simd::is_equal(m, Half<rtype>()), p, Mone<itype>()));
      }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint16_t
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::nextpow2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<uint16_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type  stype;
      typedef typename dispatch::meta::upgrade<stype>::type itype;
      typedef simd::native<itype,X>              ivtype;
      ivtype a0l, a0h;
      split(a0, a0l, a0h);
      return simd::native_cast<A0>(group(nextpow2(a0l),nextpow2(a0h)));
      }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint8_t
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::nextpow2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<uint8_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type  stype;
      typedef typename dispatch::meta::upgrade<stype>::type itype;
      typedef simd::native<itype, X>             ivtype;
      ivtype a0l, a0h;
      split(a0, a0l, a0h);
      return simd::native_cast<A0>(group(nextpow2(a0l),nextpow2(a0h)));
      }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::nextpow2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0>::type int_type;
      A0 m;
      int_type p;
      boost::simd::frexp(abs(a0), m, p);
      return tofloat(seladd(boost::simd::is_equal(m, Half<A0>()), p, Mone<int_type>()));
      }
  };
} } }


#endif

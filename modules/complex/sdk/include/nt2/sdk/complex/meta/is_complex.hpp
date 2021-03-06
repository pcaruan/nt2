//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_COMPLEX_META_IS_COMPLEX_HPP_INCLUDED
#define NT2_SDK_COMPLEX_META_IS_COMPLEX_HPP_INCLUDED

#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/mpl/bool.hpp>
#include <complex>

namespace nt2 { namespace details
{
  template<class T>
  struct is_complex
   : boost::mpl::false_
  {
  };

  template<class T>
  struct is_complex< std::complex<T> >
   : boost::mpl::true_
  {
  };
} }

namespace nt2 { namespace meta
{
  template<class T>
  struct is_complex
    : details::is_complex< typename boost::dispatch::meta::
                           scalar_of<T>::type
                         >
  {
  };
} }

#endif

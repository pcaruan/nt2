//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COLON_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COLON_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/functions/details/colon.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>
#include <nt2/core/container/dsl/details/generative.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <nt2/core/container/table/semantic.hpp>

namespace nt2
{
  namespace tag
  {
    struct colon_ : ext::generative_<colon_>
    {
      typedef ext::generative_<colon_> parent;
    };

    struct relative_colon_ : ext::elementwise_<relative_colon_>
    {
      typedef ext::elementwise_<relative_colon_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::colon_, colon, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::colon_, colon, 3)
}

namespace nt2 { namespace container { namespace ext
{
  //============================================================================
  // Register colon as a generative expression
  //============================================================================
  template<class Domain, class Expr, int N>
  struct generator<tag::colon_,Domain,N,Expr>   : generative_generator<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct size_of<tag::colon_,Domain,N,Expr>     : generative_size_of<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct generator<tag::relative_colon_,Domain,N,Expr>
  {
    typedef expression< typename boost::remove_const<Expr>::type
                      , int
                      >                                   result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };

  template<class Domain, class Expr>
  struct size_of<tag::relative_colon_,Domain,1,Expr>
  {
    typedef _0D result_type;
    BOOST_FORCEINLINE result_type operator()(Expr&) const
    {
      return result_type();
    }
  };

  template<class Domain, class Expr>
  struct size_of<tag::relative_colon_,Domain,2,Expr>
  {
    typedef _0D result_type;
    BOOST_FORCEINLINE result_type operator()(Expr&) const
    {
      return result_type();
    }
  };
} } }

#endif

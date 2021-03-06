//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_FIRST_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_FIRST_INDEX_HPP_INCLUDED

#include <nt2/core/functions/first_index.hpp>
#include <nt2/core/container/dsl.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <nt2/core/container/category.hpp>
#include <nt2/core/functions/first_index.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::first_index_,tag::cpu_
                            , (A0)(A1)
                            , (ast_<A0>)
                              (mpl_integral_< scalar_< integer_<A1> > >)
                            )
  {
    typedef typename boost::mpl::
            at_c< typename A0::index_type::type, A1::value-1>::type
    result_type;

    BOOST_FORCEINLINE result_type operator()(const A0&, const A1&) const
    {
      result_type that;
      return that;
    }
  };
} }

#endif

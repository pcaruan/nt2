//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_GENERATOR_RUN_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_GENERATOR_RUN_HPP_INCLUDED

#include <boost/mpl/if.hpp>
#include <boost/mpl/apply.hpp>
#include <nt2/dsl/functions/run.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // generator terminal with a position in read mode
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(Tag)(State)(Data)(N)
                            , ((node_<A0, generative_<Tag>, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    // The semantic of A0 gives the type to be generated
    typedef typename meta::
            scalar_of < typename  boost::dispatch::meta::
                                  semantic_of<A0&>::type
                      >::type                                         value_t;

    // Data selects if the generative target should be SIMD or not
    typedef typename Data::type                                       target_t;
    typedef typename boost::dispatch::meta::model_of<target_t>::type  m_t;

    // Compute the proper type
    // TODO: Make a proper way to transfer 'SIMD'ness to type
    typedef typename boost::mpl::if_< boost::simd::meta::is_native<target_t>
                                    , typename boost::mpl::apply<m_t,value_t>::type
                                    , value_t
                                    >::type                         result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const&) const
    {
      // We call functor in child1 over current position, size and target
      return  boost::proto::value (boost::proto::child_c<1>(a0))
                                  ( p
                                  , a0.extent()
                                  , meta::as_<result_type>()
                                  );
    }
  };
} }

#endif

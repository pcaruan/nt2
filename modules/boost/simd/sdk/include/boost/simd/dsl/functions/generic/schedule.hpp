//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_GENERIC_SCHEDULE_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_GENERIC_SCHEDULE_HPP_INCLUDED

#include <boost/simd/dsl/functions/schedule.hpp>
#include <boost/simd/dsl/functions/terminal.hpp>
#include <boost/simd/include/functions/assign.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/dispatch/dsl/unpack.hpp>
#include <boost/dispatch/meta/terminal_of_shared.hpp>
#include <boost/dispatch/meta/strip.hpp>

#include <boost/proto/make_expr.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/ref.hpp>

namespace boost { namespace simd { namespace ext
{
  template<class Expr, class State>
  struct unpack_schedule
  {
    typedef dispatch::
            unpack< Expr
                  , dispatch::functor< typename proto::tag_of<Expr>::type, tag::formal_ >
                  , dispatch::with_state<tag::schedule_, State> const
                  >
    transform;

    typedef typename transform::result_type result_type;

    BOOST_FORCEINLINE result_type
    operator()(Expr& expr, State& state) const
    {
      return transform()(expr, dispatch::with_state<tag::schedule_, State>(state));
    }
  };

  //==============================================================================
  // Jump to schedule_assign if assign node
  //==============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)(F)
                                   , ((node_<A0, boost::simd::tag::assign_, mpl::long_<2> >))
                                     (unspecified_<F>)
                                   )
  {
    typedef typename boost::proto::result_of::child_c<A0&, 0>::type child0;
    typedef typename boost::proto::result_of::child_c<A0&, 1>::type child1;
    typedef typename dispatch::meta::call<tag::schedule_assign_(child0, child1, F const&)>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, F const& f) const
    {
      return schedule_assign(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a0), f);
    }
  };

  //==============================================================================
  // Elementwise
  //==============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_assign_, tag::formal_
                                   , (A0)(A1)(T1)(N1)(F)
                                   , (unspecified_<A0>)
                                     ((node_<A1, elementwise_<T1>, N1>))
                                     (unspecified_<F>)
                                   )
  {
    typedef typename unpack_schedule<A0, F const>::result_type                       child0;
    typedef typename unpack_schedule<A1, F const>::result_type                       child1;
    typedef typename dispatch::meta::call<tag::assign_(child0, child1)>::type  result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1, F const& f) const
    {
      return boost::simd::assign(unpack_schedule<A0, F const>()(a0, f), unpack_schedule<A1, F const>()(a1, f));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)(T)(N)(F)
                                   , ((node_<A0, elementwise_<T>, N>))
                                     (unspecified_<F>)
                                   )
  {
    typedef typename unpack_schedule<A0, F const>::result_type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, F const& f) const
    {
      return unpack_schedule<A0, F const>()(a0, f);
    }
  };

  //==============================================================================
  // Reduction
  //==============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_assign_, tag::formal_
                                   , (A0)(A1)(T1)(N1)(F)
                                   , (unspecified_<A0>)
                                     ((node_<A1, unspecified_<T1>, N1>))
                                     (unspecified_<F>)
                                   )
  {
    typedef typename unpack_schedule<A0, F const>::result_type                       child0;
    typedef typename unpack_schedule<A1, F const>::result_type                       child1;
    typedef typename dispatch::meta::call<tag::assign_(child0, child1)>::type  assigned;
    typedef typename dispatch::meta::result_of<F const(assigned)>::type              result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1, F const& f) const
    {
      return f(boost::simd::assign(unpack_schedule<A0, F const>()(a0, f), unpack_schedule<A1, F const>()(a1, f)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)(T)(N)(F)
                                   , ((node_<A0, unspecified_<T>, N>))
                                     (unspecified_<F>)
                                   )
  {
    typedef typename dispatch::meta::semantic_of<A0&>::type             semantic;
    typedef typename dispatch::meta::terminal_of_shared<semantic>::type terminal;
    typedef typename boost::proto::result_of::as_child<terminal>::type& child0;
    typedef typename unpack_schedule<A0, F const>::result_type          unpck;
    typedef typename dispatch::meta::as_ref<unpck>::type                child1;
    typedef typename boost::proto::result_of::
            make_expr< boost::proto::tag::assign
                     , child0, child1
                     >::type                                            assigned;
    typedef typename dispatch::meta::result_of<F const(assigned)>::type result;
    typedef typename dispatch::meta::strip<result>::type                result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, F const& f) const
    {
      typedef boost::reference_wrapper<typename boost::remove_reference<child1>::type> ref;

      terminal term = dispatch::meta::terminal_of_shared<semantic>::make();
      return f(boost::proto::make_expr<boost::proto::tag::assign>( boost::ref(boost::proto::as_child(term))
                                                                 , ref(unpack_schedule<A0, F const>()(a0, f))
                                                                 )
              );
    }
  };

} } }

#endif

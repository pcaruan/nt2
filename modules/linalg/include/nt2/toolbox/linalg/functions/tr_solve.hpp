//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_TR_SOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_TR_SOLVE_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/toolbox/linalg/functions/details/tr_solve.hpp>

//  tr_solve solve linear system a*x=b.
//     x = tr_solve(a,b) solves the linear system a*x=b using
//     lu factorization with partial pivoting. a must be square,

namespace nt2
{
  namespace tag
  {
    namespace solvers
    {
      struct tr_solve_ : ext::unspecified_<solvers::tr_solve_>
      {
        typedef ext::unspecified_<solvers::tr_solve_> parent;
      };
    }

    struct tr_solve_ :  ext::tieable_<tr_solve_>
    {
      typedef ext::tieable_<tr_solve_>  parent;
    };
  }

  /**
   * @brief Perform Tr_solve factorization
   *
   * For any given matrix expression a, and right hand side b performs
   * Tr_solve resolution of
   * said system using the specified output layout for the Tr_solve method.
   *
   * Contrary to the nt2::factorization::tr_solve function which
   * performs a partial evaluation of
   * said resolution, nt2::tr_solve returns a result similar to the Matlab interface,
   * making it useful for Matlab like usage.
   *
   * @param  xpr  Matrix expression
   * @param  b    rigt hand side expression
   *
   * @return A tuple-like type containing the solution and optionnaly the rcond number of the system
   * of the success of the factorization
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::tr_solve_, tr_solve, 5)

  namespace solvers
  {
    /**
     * @brief Initialize a Tr_solve factorization
     *
     * For any given matrix expression, initialize a Tr_solve factorization of
     * said matrix using the specified output layout for the Tr_solve method
     * and return a precomputed factorization object.
     *
     * Contrary to the tr_solve function which performs such a factorization and
     * return a Matlab like output, factorization::tr_solve returns an object
     * containing the initial evaluation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     * @param  ip   Notify if tr_solve should be performed in-place over xpr
     *
     * @return A unspecified type containing the precomputed elements of the
     * Tr_solve factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::solvers::tr_solve_, tr_solve, 5)
//     NT2_FUNCTION_IMPLEMENTATION(tag::solvers::tr_solve_, tr_solve, 6)
//     NT2_FUNCTION_IMPLEMENTATION_TPL(tag::solvers::tr_solve_, tr_solve,(A0&)(A1&)
//                                     (const A2&)(const A3&)(const A4&), 5)
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::solvers::tr_solve_, tr_solve,(A0&)(A1&)
                                    (const A2&)(const A3&)
                                    (const A4&)(const A5&), 6)
      
      
  }
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::tr_solve_,Domain,N,Expr>
  {
    // The size is contained in the first child
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
    typedef typename meta::strip<seq_term>::type::extent_type        result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<0>(e).extent();
    }
  };

  template<class Domain, class Expr>
  struct  size_of<tag::tr_solve_,Domain,1,Expr>
  {
    // The size is contained in the first child
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
    typedef typename meta::strip<seq_term>::type::extent_type        result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<0>(e).extent();
    }
  };

  template<class Domain, int N, class Expr>
  struct  generator<tag::tr_solve_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
    typedef typename boost::dispatch::meta::semantic_of<seq_term>::type sema_t;

    // Rebuild proper expression type with semantic
    typedef expression< typename boost::remove_const<Expr>::type
                      , sema_t
                      >                                     result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };
} } }

#endif

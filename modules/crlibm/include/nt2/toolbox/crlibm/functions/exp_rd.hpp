//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_CRLIBM_FUNCTIONS_EXP_RD_HPP_INCLUDED
#define NT2_TOOLBOX_CRLIBM_FUNCTIONS_EXP_RD_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/crlibm/specific/interface.hpp>

/*!
 * \ingroup crlibm
 * \defgroup crlibm_exp_rd exp_rd
 *
 * \par Description
 * Please for details consult the proper documentation of the external
 * library crlibm.
 * \par
 * The suffix _rd is used to choose the rounding
 * means rouding to \f$-\infty\f$
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/toolbox/crlibm/include/functions/exp_rd.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   namespace crlibm
 *   {
 *     template <class A0>
 *       meta::call<tag::exp_rd_(A0)>::type
 *       exp_rd(const A0 & a0);
 *   }
 * }
 * \endcode
 *
 * \param a0 the unique parameter of exp_rd
 * 
 * \return a value of the same type as the parameter
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 * When calling external library, nt2 simply encapsulates the
 * original proper call to provide easy use.
 * \par
 * Remenber that SIMD implementation is therefore merely
 * mapping the scalar function to each SIMD vectors elements
 * and will not provide acceleration, but ease.
 * \par
 * crlibm library defines functions for double entries only.
 * Nevertheless, they can be called with float entries under nt2 calls
 * to return float outputs.
 *  
**/

namespace nt2 { namespace crlibm { namespace tag
  {
    /*!
     * \brief Define the tag exp_rd_ of functor exp_rd 
     *        in namespace nt2::crlibm::tag for toolbox crlibm
    **/
    struct exp_rd_ : ext::elementwise_<exp_rd_> { typedef ext::elementwise_<exp_rd_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(crlibm::tag::exp_rd_, exp_rd, 1)
} }

#endif

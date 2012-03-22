//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_RELATIVE_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_RELATIVE_INDEX_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::relative_index function
 */

#include <nt2/include/functor.hpp>

namespace nt2 
{
  namespace tag
  {
    struct relative_index_ : tag::formal_
    {
      typedef tag::formal_ parent;
    };
  }

  //============================================================================
  /*!
   * Performs an index translation to be used in indexed access computation
   *
   * \param xpr Indexing expression
   * \param idx Index being computed
   * \return The translated index to access current indexing expression
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::relative_index_, relative_index, 2)
}

#endif
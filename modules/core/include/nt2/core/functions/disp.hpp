//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DISP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DISP_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::disp function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct disp_ : tag::formal_
    {
      typedef tag::formal_ parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::disp_,disp,1)
}

#endif

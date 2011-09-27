//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_POSMIN_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_POSMIN_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_reduction
 * \defgroup posmin posmin function
 *
 * \par Description
 * Returns the index of the first occurence of least element of the SIMD vector
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/posmin.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::posmin_(A0)>::type
 *     posmin(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 is the unique parameter of posmin
 * 
 * \return always a scalar value
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 * This is a reduction operation. As such it has not real interest outside
 * SIMD mode.
 * \par
 * Such an operation has always a scalar result which translate a property.
 * of the whole SIMD vector.
 * \par
 * If usable and used in scalar mode, it reduces to the operation as acting
 * on a one element vector.
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag posmin_ of functor posmin 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct posmin_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::posmin_, posmin, 1)
} }

#endif

// modified by jt the 25/12/2010

//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - saturate_at/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 20/03/2011
/// 
#include <nt2/toolbox/ieee/include/saturate_at.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>

NT2_TEST_CASE_TPL ( saturate_at_unsigned_int__1_0,  NT2_REAL_TYPES)
{
  
  using nt2::saturate_at;
  using nt2::tag::saturate_at_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<saturate_at_<nt2::tag::pi_>(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;
  
  
  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;
  //   std::cout << nt2::type_id < T >() << std::endl; 
  //   std::cout << nt2::type_id < nt2::tag::pi_ >() << std::endl;
  //  std::cout << nt2::type_id < nt2::Pi>() << std::endl;
  //  stypedef T (*func());
  //  std::cout << nt2::type_id <func>() << std::endl;
  
  std::cout << saturate_at<nt2::tag::pi_> (nt2::One<T>()) << std::endl;
  std::cout << saturate_at<nt2::tag::pi_>(T(5)) << std::endl;
  std::cout << saturate_at<nt2::tag::pi_>(T(-5)) << std::endl;
  std::cout << saturate_at<nt2::tag::pi_>(nt2::Nan<T>())<< std::endl;
} // end of test for unsigned_int_

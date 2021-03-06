//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II       
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI       
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_PREFETCH_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_PREFETCH_HPP_INCLUDED

#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/simd/sdk/config/arch.hpp>

////////////////////////////////////////////////////////////////////////////////
// Prefetch data from main memory to the cache for optimized memory accesses 
// integer_L1 : Prefetches into the L1 cache (and the L2 and the L3 cache).
//              Use this for integer data.
// real_L2_L3 : Prefetches into the L2 cache (and the L3 cache); 
//              floating-point data is used from the L2 cache, not the L1 cache.
//              Use this for real data.
// not_frequently_reused : Prefetches into the L2 cache (and the L3 cache);
//              this line will be marked for early displacement. 
//              Use this if you are not going to reuse the cache line frequently.
// not_reused : Prefetches into the L2 cache (but not the L3 cache);
//              this line will be marked for early displacement. 
//              Use this if you are not going to reuse the cache line.
//
// TODO : Discuss for Altivec : 
// https://developer.apple.com/hardwaredrivers/ve/instruction_crossref.html#prefetch
////////////////////////////////////////////////////////////////////////////////

#ifdef BOOST_SIMD_ARCH_X86

namespace boost{ namespace simd{ namespace memory{
  
  enum{integer_L1, real_L2_L3, not_frequently_reused, not_reused}
  
  void prefetch(char* pointer, int const& strategy)
  {
    _mm_prefetch(pointer, strategy);
  }
  
} } } 

#endif

#endif

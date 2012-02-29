//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II       
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI       
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ALGEBRA_FUNCTIONS_BLAS_MM_HPP_INCLUDED
#define NT2_TOOLBOX_ALGEBRA_FUNCTIONS_BLAS_MM_HPP_INCLUDED

#include <nt2/table.hpp>
#include <nt2/core/container/category.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/toolbox/algebra/blas/blas3_b.hpp>
#include <nt2/toolbox/algebra/details/padding.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <boost/preprocessor/cat.hpp>
#include <nt2/sdk/error/assert.hpp>

namespace nt2 {
  namespace details
  {
    template < class ST, class A, class B, class C, class Rstatus> 
      inline void mm_prepare(ST const& A const&, B const&, C const&, Rstatus & r)
      {
      }
  }
  namespace ext
  {
    
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mm_, tag::cpu_, 
                             (A)(SIZEA)(SHA)(STA)
                             (B)(SIZEB)(SHB)(STB)
                             (C)(SIZEC)(SHC)(STC)(Alpha)(Beta)(STATUS), 
                             (unspecified_ < STATUS > )
                             ((table_< floating_<A>, settings<SIZEA,SHA,STA> > ))
                             ((table_< floating_<B>, settings<SIZEB,SHB,STB> > ))
                             ((table_< floating_<C>, settings<SIZEC,SHC,STC> > ))
                             (scalar_ < arithmetic_<Alpha > > )
                             (scalar_ < arithmetic_<Beta > > )
                              )
    {
      typedef void result_type;
      typedef typename C::value_type value_type; 
      
      BOOST_FORCEINLINE result_type operator()( STATUS const& 
                                              , A const& a, B const& b
                                              , C& c
                                              , Alpha const& alpha, Beta const& beta
                                              )
      {
          BOOST_ASSERT_MSG(false, "The current blas matrices forms/storages\
                                   is not supported by any mm blas call");
      }
    };

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mm_, tag::cpu_, 
                             (A)(SIZEA)
                             (B)(SIZEB)
                             (C)(SIZEC)(Alpha)(Beta)(STATUS), 
                             (unspecified_ < STATUS > )
                             ((table_< floating_<A>, settings<SIZEA,rectangular_,conventional_> > ))
                             ((table_< floating_<B>, settings<SIZEB,rectangular_,conventional_> > ))
                             ((table_< floating_<C>, settings<SIZEC,rectangular_,conventional_> > ))
                             (scalar_ < arithmetic_<Alpha > > )
                             (scalar_ < arithmetic_<Beta > > )
                              )
    {
      typedef void result_type;
      typedef typename C::value_type value_type; 
      
      BOOST_FORCEINLINE result_type operator()( STATUS const& 
                                              , A const& a, B const& b
                                              , C& c
                                                , Alpha const& alpha, Beta const& beta
                                                )
      {
        std::cout << "general" << std::endl; 
        const char transa = STATUS::transa; 
        const char transb = STATUS::transb; 
        const long int m = nt2::extent(a0)[transa=='N'?0:1];
        const long int n = nt2::extent(a1)[transb=='N'?1:0];
        const long int k = nt2::extent(a0)[transa=='N'?1:0];
        
        BOOST_ASSERT_MSG( (k == nt2::size(a1, transb=='N'?1:2)),
                          "In matrix-vector product C = al*A�*B�+ be*C (gemm) inner dimensions of A� and B� must match");
        BOOST_ASSERT_MSG( ((m == nt2::size(a2,1))&&(n == nt2::size(a2,2))),
                          "In matrix-vector product C = al*A�*B�+ be*C (gemm) outer dimensions of A� and B� must match C ones");
        
        const value_type alpha = a3; 
        const value_type beta = a4; 
        const long int lda = nt2::details::padding(a0);
        const long int ldb = nt2::details::padding(a1);
        const long int ldc = nt2::details::padding(a2);
        nt2::details::gemm(&transa,&transb,&m,&n,&k,&alpha,a0.begin(),&lda,a1.begin(),&ldb,&beta,a2.begin(),&ldc);
      }
    };
    
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mm_, tag::cpu_, 
                                (A)(SIZEA)
                                (B)(SIZEB)
                                (C)(SIZEC)(Alpha)(Beta)(STATUS), 
                                (unspecified_ < STATUS > )
                                ((table_< floating_<A>, settings<SIZEA,symetric_,conventional_> > ))
                                ((table_< floating_<B>, settings<SIZEB,rectangular_,conventional_> > ))
                                ((table_< floating_<C>, settings<SIZEC,rectangular_,conventional_> > ))
                                (scalar_ < arithmetic_<Alpha > > )
                                (scalar_ < arithmetic_<Beta > > )
                                )
    {
      typedef void result_type;
      typedef typename C::value_type value_type; 
      
      BOOST_FORCEINLINE result_type operator()( STATUS const& 
                                                , A const& a, B const& b
                                                , C& c
                                                , Alpha const& alpha, Beta const& beta
                                                )
      {
        std::cout << "symetric" << std::endl; 
        const char side = STATUS::side; 
        const char uplo = STATUS::uplo; 
        const long int n = nt2::extent(a1)[1];
        const long int m = nt2::extent(a1)[0];
        BOOST_ASSERT_MSG( (is_square(a0)),"In symm calls matrix A must be square");
        
        BOOST_ASSERT_MSG( ( nt2::size(a0,1) == (side=='L')?m:n),
                          "In symm calls inner dimensions, according to side, must match");
        
        const value_type alpha = a3; 
        const value_type beta  = a4; 
        const long int lda = nt2::details::padding(a0);
        const long int ldb = nt2::details::padding(a1);
        const long int ldc = nt2::details::padding(a2);
        nt2::details::symm(&side,&uplo,&m,&n,&alpha,a0.begin(),&lda,a1.begin(),&ldb,&beta,a2.begin(),&ldc);
      }
    };
      
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mm_, tag::cpu_, 
                                (A)(SIZEA)
                                (B)(SIZEB)
                                (C)(SIZEC)(Alpha)(Beta)(STATUS), 
                                (unspecified_ < STATUS > )
                                ((table_< floating_<A>, settings<SIZEA,hermitian_,conventional_> > ))
                                ((table_< floating_<B>, settings<SIZEB,rectangular_,conventional_> > ))
                                ((table_< floating_<C>, settings<SIZEC,rectangular_,conventional_> > ))
                                (scalar_ < arithmetic_<Alpha > > )
                                (scalar_ < arithmetic_<Beta > > )
                                )
    {
      typedef void result_type;
      typedef typename C::value_type value_type; 
      
      BOOST_FORCEINLINE result_type operator()( STATUS const& 
                                                , A const& a, B const& b
                                                , C& c
                                                , Alpha const& alpha, Beta const& beta
                                                )
      {
        std::cout << "hermitian" << std::endl; 
        const char side = STATUS::side; 
        const char uplo = STATUS::uplo; 
        const long int n = nt2::extent(a1)[1];
        const long int m = nt2::extent(a1)[0];
        BOOST_ASSERT_MSG( (is_square(a0)),"In hemm calls matrix A must be square");
        
        BOOST_ASSERT_MSG( ( nt2::size(a0,1) == (side=='L')?m:n) ,
                          "In hemm calls, inner dimensions according to side, must match");
        const value_type alpha = a3; 
        const long int lda = nt2::details::padding(a0);
        const long int ldb = nt2::details::padding(a1);
        const value_type beta = a4; 
        const long int ldc = nt2::details::padding(a2);
        nt2::details::hemm(&side,&uplo,&m,&n,&alpha,a0.begin(),&lda,a1.begin(),&ldb,&beta,a2.begin(),&ldc);
      }
    }; 
  }
}

#endif

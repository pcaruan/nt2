################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

if(NOT NT2_COMPILER_OPTIONS_INCLUDED)
set(NT2_COMPILER_OPTIONS_INCLUDED 1)

set(NT2_FLAGS_TEST "-DNT2_ASSERTS_AS_EXCEPTIONS")
set(NT2_FLAGS_BENCH "-DNT2_DISABLE_ERROR -DNDEBUG")
if(MSVC)
  set(NT2_FLAGS_TEST "${NT2_FLAGS_TEST} /MD /MP /D_SECURE_SCL=1 /D_ITERATOR_DEBUG_LEVEL=1 /Oxt /GF /Gm- /GS- /fp:precise /fp:except- /EHa")
  set(NT2_FLAGS_BENCH "${NT2_FLAGS_BENCH} /MD /MP /D_SECURE_SCL=0 /GL /Oxt /GF /Gm- /GS- /fp:precise /fp:except- /EHs- /EHa- /wd4530")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUXX)
  set(NT2_FLAGS_TEST "${NT2_FLAGS_TEST} ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -D_GLIBCXX_DEBUG=1")
  set(NT2_FLAGS_BENCH "${NT2_FLAGS_BENCH} -O3 -fomit-frame-pointer -fno-exceptions")
else()
  set(NT2_FLAGS_TEST "${NT2_FLAGS_TEST} ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
  set(NT2_FLAGS_BENCH "${NT2_FLAGS_BENCH} ${CMAKE_CXX_FLAGS_RELEASE}")
endif()
set(NT2_FLAGS_TEST ${NT2_FLAGS_TEST} CACHE STRING "Compiler flags for NT2 tests")
set(NT2_FLAGS_BENCH ${NT2_FLAGS_BENCH} CACHE STRING "Compiler flags for NT2 benchmarks")

include(options/nt2.extra.warnings)
add_definitions(${NT2_FLAGS})

if(NOT CMAKE_CONFIGURATION_TYPES)
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
  endif()
  string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE_U)
  message(STATUS "[nt2] Build flags: ${CMAKE_CXX_FLAGS_${BUILD_TYPE_U}}")
endif()

message(STATUS "[nt2] Test flags: ${NT2_FLAGS_TEST}")
message(STATUS "[nt2] Bench flags: ${NT2_FLAGS_BENCH}")

endif()

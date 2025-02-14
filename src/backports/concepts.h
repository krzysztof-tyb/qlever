// Copyright 2024, University of Freiburg
// Chair of Algorithms and Data Structures
// Author: Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>

#pragma once

#include <concepts/concepts.hpp>

#include "backports/cppTemplate2.h"
#ifndef QLEVER_CPP_17
#include <concepts>
#endif

// Define the following macros:
//
// `QL_CONCEPT_OR_NOTHING(arg)`: expands to `arg` in C++20 mode, and to
// nothing in C++17 mode. It can be used to easily opt out of concepts that are
// only used for documentation and increased safety and not for overload
// resolution.
//
// `QL_CONCEPT_OR_TYPENAME(arg)`: expands to `arg` in C++20 mode, and to
// `typename` in C++17 mode.
//
// `CPP_lambda(capture)(arg)(requires ...)`: Expands lambda to use
//  `requires` in C++20 mode and `std::enable_if_t` in C++17 mode.
//
// Example usages:
//
// `QL_CONCEPT_OR_NOTHING(std::view) auto x = someFunction();`
//
// `QL_CONCEPT_OR_NOTHING(SameAsAny<int, float>)`
//
// `void f(QL_CONCEPT_OR_NOTHING(std::view) auto x) {...}`
//
// `template <QL_CONCEPT_OR_TYPENAME(ql::same_as<int>) T> void f(){...}`
//
// `auto myLambda = CPP_lambda(someCapture)(someArg)(requires
// ranges::same_as<decltype(someArg), int>) {...}`
//
// NOTE: The macros are variadic to allow for commas in the argument, like in
// the second example above.

// Additionally define the macros `CPP_template_2` and `CPP_and_2` that can
// be used to constrain member functions of classes where the outer class
// has already been constrained with `CPP_template`. For a detailed example, see
// the `test/backports/ConceptsTest.cpp` file.

#ifdef QLEVER_CPP_17
#define QL_CONCEPT_OR_NOTHING(...)
#define QL_CONCEPT_OR_TYPENAME(...) typename
#define CPP_template_2 CPP_template_2_SFINAE
#define CPP_and_2 CPP_and_2_sfinae
#define CPP_and_def CPP_and_sfinae_def
#define CPP_and_2_def CPP_and_2_def_sfinae
#define CPP_variadic_template CPP_template_NO_DEFAULT_SFINAE
#define CPP_member_def CPP_member_def_sfinae

#define CPP_lambda CPP_lambda_sfinae

#define CPP_lambda_mut CPP_lambda_mut_sfinae

#define CPP_lambda_sfinae(...)     \
  CPP_PP_IGNORE_CXX2A_COMPAT_BEGIN \
  [__VA_ARGS__] CPP_LAMBDA_SFINAE_ARGS

#define CPP_lambda_mut_sfinae(...) \
  CPP_PP_IGNORE_CXX2A_COMPAT_BEGIN \
  [__VA_ARGS__] CPP_LAMBDA_MUT_SFINAE_ARGS

#define CPP_LAMBDA_SFINAE_ARGS(...) \
    (__VA_ARGS__ CPP_LAMBDA_SFINAE_AUX_

#define CPP_LAMBDA_MUT_SFINAE_ARGS(...) \
    (__VA_ARGS__ CPP_LAMBDA_MUT_SFINAE_AUX_

#define CPP_LAMBDA_SFINAE_AUX_WHICH_(FIRST, ...) \
  CPP_PP_EVAL(CPP_PP_CHECK, FIRST)

#define CPP_LAMBDA_SFINAE_AUX_(...)                       \
  CPP_PP_CAT(CPP_LAMBDA_SFINAE_AUX_,                      \
             CPP_LAMBDA_SFINAE_AUX_WHICH_(__VA_ARGS__, )) \
  (__VA_ARGS__)

#define CPP_LAMBDA_MUT_SFINAE_AUX_(...)                   \
  CPP_PP_CAT(CPP_LAMBDA_SFINAE_AUX_,                      \
             CPP_LAMBDA_SFINAE_AUX_WHICH_(__VA_ARGS__, )) \
  (__VA_ARGS__) mutable

#define CPP_LAMBDA_SFINAE_AUX_0(...) ,                           \
    std::enable_if_t<                                            \
        CPP_PP_CAT(CPP_LAMBDA_SFINAE_AUX_3_, __VA_ARGS__)        \
        >* = nullptr)

#define CPP_LAMBDA_SFINAE_AUX_3_requires

#else
#define QL_CONCEPT_OR_NOTHING(...) __VA_ARGS__
#define QL_CONCEPT_OR_TYPENAME(...) __VA_ARGS__
#define CPP_template_2 CPP_template
#define CPP_and_2 CPP_and
#define CPP_and_def CPP_and
#define CPP_and_2_def CPP_and
#define CPP_variadic_template CPP_template
#define CPP_member_def CPP_member

#define CPP_lambda(...) [__VA_ARGS__] CPP_LAMBDA_ARGS

#define CPP_lambda_mut(...) [__VA_ARGS__] CPP_LAMBDA_ARGS_MUT

#define CPP_LAMBDA_ARGS(...) (__VA_ARGS__) CPP_LAMBDA_AUX_

#define CPP_LAMBDA_ARGS_MUT(...) (__VA_ARGS__) mutable CPP_LAMBDA_AUX_

#define CPP_LAMBDA_AUX_(...) \
  CPP_PP_CAT(CPP_LAMBDA_AUX_, CPP_LAMBDA_AUX_WHICH_(__VA_ARGS__, ))(__VA_ARGS__)

#define CPP_LAMBDA_AUX_WHICH_(FIRST, ...) CPP_PP_EVAL(CPP_PP_CHECK, FIRST)

#define CPP_LAMBDA_AUX_0(...) __VA_ARGS__

#endif

// The namespace `ql::concepts` includes concepts that are contained in the
// C++20 standard as well as in `range-v3`.
namespace ql::concepts {

#ifdef QLEVER_CPP_17
using namespace ::concepts;
#else
using namespace std;
#endif

}  // namespace ql::concepts

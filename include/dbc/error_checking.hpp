///////////////////////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright (c) 2021 SoultatosStefanos
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef DBC_ERROR_CHECKING_H
#define DBC_ERROR_CHECKING_H

#include "error_handling.hpp"
#include "error_reporting.hpp"

/**
 * @defgroup error_checking Error Checking
 * @ {
 *
 * DBC comes with certain compilation options to configure its assertions accross the different
 * contracts.
 *
 * @par DBC_ASSERT_LEVEL_NONE
 *  All assertions have no runtime effect. Precondtion, postcondition and invariants checks are
 *  turned to noops.
 *
 * @par DBC_ASSERT_LEVEL_PRECONDITIONS
 *  Only precondition checks are monitored. Hence, the REQUIRE checker is the only checker that is
 *  not turned to a noop.
 *
 * @par DBC_ASSERT_LEVEL_POSTCONDITIONS
 *  Both preconditions and postconditions, validated with the REQUIRE and ENSURE macros, are
 *  monitored. Invariant checks are turned to noops.
 *
 * @par DBC_ASSERT_LEVEL_INVARIANTS
 *  All assertions are monitored.
 *
 * Additionally each DBC assertion is overloaded, in order to provide a developer friendly error
 * message.
 */

#define DBC_ASSERT_IMPL(type, expr, msg)                                                           \
    if (!(expr)) dbc::details::handle(DBC_GET_CONTEXT(type, expr, msg));

#if defined(DBC_ASSERT_LEVEL_NONE) // assertions have no run-time effect.

#if defined(DBC_ASSERT_LEVEL_REQUIRE) || defined(DBC_ASSERT_LEVEL_ENSURE) ||                       \
    defined(DBC_ASSERT_LEVEL_INVARIANT)
#error "Multiple DBC assert levels defined"
#endif

#define DBC_REQUIRE1(expr) void(0)
#define DBC_REQUIRE2(expr, msg) void(0)

#define DBC_ENSURE1(expr) void(0)
#define DBC_ENSURE2(expr, msg) void(0)

#define DBC_INVARIANT1(expr) void(0)
#define DBC_INVARIANT2(expr, msg) void(0)

#elif defined(DBC_ASSERT_LEVEL_PRECONDITIONS) // monitor preconditions only

#if defined(DBC_ASSERT_LEVEL_NONE) || defined(DBC_ASSERT_LEVEL_ENSURE) ||                          \
    defined(DBC_ASSERT_LEVEL_INVARIANT)
#error "Multiple DBC assert levels defined"
#endif

#define DBC_REQUIRE1(expr) DBC_ASSERT_IMPL(dbc::contract::precondition, expr, "")
#define DBC_REQUIRE2(expr, msg) DBC_ASSERT_IMPL(dbc::contract::precondition, expr, msg)

#define DBC_ENSURE1(expr) void(0)
#define DBC_ENSURE2(expr, msg) void(0)

#define DBC_INVARIANT1(expr) void(0)
#define DBC_INVARIANT2(expr, msg) void(0)

#elif defined(DBC_ASSERT_LEVEL_POSTCONDITIONS) // monitor preconditions and postconditions

#if defined(DBC_ASSERT_LEVEL_REQUIRE) || defined(DBC_ASSERT_LEVEL_NONE) ||                         \
    defined(DBC_ASSERT_LEVEL_INVARIANT)
#error "Multiple DBC assert levels defined"
#endif

#define DBC_REQUIRE1(expr) DBC_ASSERT_IMPL(dbc::contract::precondition, expr, "")
#define DBC_REQUIRE2(expr, msg) DBC_ASSERT_IMPL(dbc::contract::precondition, expr, msg)

#define DBC_ENSURE1(expr) DBC_ASSERT_IMPL(dbc::contract::postcondition, expr, "")
#define DBC_ENSURE2(expr, msg) DBC_ASSERT_IMPL(dbc::contract::postcondition, expr, msg)

#define DBC_INVARIANT1(expr) void(0)
#define DBC_INVARIANT2(expr, msg) void(0)

#elif defined(DBC_ASSERT_LEVEL_INVARIANTS) // monitor preconditions, postconditions and invariants

#if defined(DBC_ASSERT_LEVEL_REQUIRE) || defined(DBC_ASSERT_LEVEL_ENSURE) ||                       \
    defined(DBC_ASSERT_LEVEL_NONE)
#error "Multiple DBC assert levels defined"
#endif

#define DBC_REQUIRE1(expr) DBC_ASSERT_IMPL(dbc::contract::precondition, expr, "")
#define DBC_REQUIRE2(expr, msg) DBC_ASSERT_IMPL(dbc::contract::precondition, expr, msg)

#define DBC_ENSURE1(expr) DBC_ASSERT_IMPL(dbc::contract::postcondition, expr, "")
#define DBC_ENSURE2(expr, msg) DBC_ASSERT_IMPL(dbc::contract::postcondition, expr, msg)

#define DBC_INVARIANT1(expr) DBC_ASSERT_IMPL(dbc::contract::invariant, expr, "")
#define DBC_INVARIANT2(expr, msg) DBC_ASSERT_IMPL(dbc::contract::invariant, expr, msg)

#endif

#define DBC_EXPAND(x) x                       // MSVC workaround
#define DBC_GET_MACRO(_1, _2, NAME, ...) NAME // Macro overloading trick

#define REQUIRE(...) DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_REQUIRE2, DBC_REQUIRE1)(__VA_ARGS__))

#define ENSURE(...) DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_ENSURE2, DBC_ENSURE1)(__VA_ARGS__))

#define INVARIANT(...)                                                                             \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_INVARIANT2, DBC_INVARIANT1)(__VA_ARGS__))

/** @} */

#endif // DBC_ERROR_CHECKING_H
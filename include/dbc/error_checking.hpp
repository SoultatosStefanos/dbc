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
 * Each DBC assertion comes in three variants.
 *
 * @par Critical variant
 *  Used for critical assumptions that must always be verified. Most applications do not benefit
 * from this variant. E.g INVARIANT_CRITICAL, REQUIRE_CRITICAL, ENSURE_CRITICAL.
 *
 * @par Regular variant
 *  Most assertions fall in this category. Regular assumptions, whose complexity is constant should
 *  be verified like this. E.g INVARIANT, REQUIRE, ENSURE.
 *
 * @par Safe variant
 *  This variant should be used to assert for complex assumptions, that can slow down an
 * application. Typically useful for inline functions and checks of linear, or greater,
 * complexities. E.g INVARIANT_SAFE, REQUIRE_SAFE, ENSURE_SAFE.
 *
 * Additionally each DBC assertion is overloaded, in order to provide a developer friendly error
 * message.
 */

#define DBC_ASSERT_IMPL(type, expr, msg)                                                           \
    if (!(expr)) dbc::details::handle(DBC_GET_CONTEXT(type, expr, msg));

#if defined(DBC_ASSERT_LEVEL_NONE) // turn of all checkers

// Forbid multiple defined levels
#if defined(DBC_ASSERT_LEVEL_CRITICAL) || defined(DBC_ASSERT_LEVEL_ASSERT) ||                      \
    defined(DBC_ASSERT_LEVEL_SAFE)
#error "Multiple DBC assert levels defined"
#endif

#define DBC_ASSERT_CRITICAL(type, expr, msg) void(0)
#define DBC_ASSERT(type, expr, msg) void(0)
#define DBC_ASSERT_SAFE(type, expr, msg) void(0)

#elif defined(DBC_ASSERT_LEVEL_CRITICAL) // assert only for critical assumptions

// Forbid multiple defined levels
#if defined(DBC_ASSERT_LEVEL_NONE) || defined(DBC_ASSERT_LEVEL_ASSERT) ||                          \
    defined(DBC_ASSERT_LEVEL_SAFE)
#error "Multiple DBC assert levels defined"
#endif

#define DBC_ASSERT_CRITICAL(type, expr, msg) DBC_ASSERT_IMPL(type, expr, msg)
#define DBC_ASSERT(type, expr, msg) void(0)
#define DBC_ASSERT_SAFE(type, expr, msg) void(0)

#elif defined(DBC_ASSERT_LEVEL_ASSERT) // assert for critical and regular assumptions

// Forbid multiple defined levels
#if defined(DBC_ASSERT_LEVEL_NONE) || defined(DBC_ASSERT_LEVEL_CRITICAL) ||                        \
    defined(DBC_ASSERT_LEVEL_SAFE)
#error "Multiple DBC assert levels defined"
#endif

#define DBC_ASSERT_CRITICAL(type, expr, msg) DBC_ASSERT_IMPL(type, expr, msg)
#define DBC_ASSERT(type, expr, msg) DBC_ASSERT_IMPL(type, expr, msg)
#define DBC_ASSERT_SAFE(type, expr, msg) void(0)

#elif defined(DBC_ASSERT_LEVEL_SAFE) // assert for critical, regular and expensive assumptions

// Forbid multiple defined levels
#if defined(DBC_ASSERT_LEVEL_NONE) || defined(DBC_ASSERT_LEVEL_CRITICAL) ||                        \
    defined(DBC_ASSERT_LEVEL_ASSERT)
#error "Multiple DBC assert levels defined"
#endif

#define DBC_ASSERT_CRITICAL(type, expr, msg) DBC_ASSERT_IMPL(type, expr, msg)
#define DBC_ASSERT(type, expr, msg) DBC_ASSERT_IMPL(type, expr, msg)
#define DBC_ASSERT_SAFE(type, expr, msg) DBC_ASSERT_IMPL(type, expr, msg)

#endif

#define DBC_INVARIANT_CRITICAL1(expr) DBC_ASSERT_CRITICAL(dbc::contract::invariant, expr, "")
#define DBC_INVARIANT_CRITICAL2(expr, msg) DBC_ASSERT_CRITICAL(dbc::contract::invariant, expr, msg)

#define DBC_INVARIANT1(expr) DBC_ASSERT(dbc::contract::invariant, expr, "")
#define DBC_INVARIANT2(expr, msg) DBC_ASSERT(dbc::contract::invariant, expr, msg)

#define DBC_INVARIANT_SAFE1(expr) DBC_ASSERT_SAFE(dbc::contract::invariant, expr, "")
#define DBC_INVARIANT_SAFE2(expr, msg) DBC_ASSERT_SAFE(dbc::contract::invariant, expr, msg)

#define DBC_REQUIRE_CRITICAL1(expr) DBC_ASSERT_CRITICAL(dbc::contract::precondition, expr, "")
#define DBC_REQUIRE_CRITICAL2(expr, msg) DBC_ASSERT_CRITICAL(dbc::contract::precondition, expr, msg)

#define DBC_REQUIRE1(expr) DBC_ASSERT(dbc::contract::precondition, expr, "")
#define DBC_REQUIRE2(expr, msg) DBC_ASSERT(dbc::contract::precondition, expr, msg)

#define DBC_REQUIRE_SAFE1(expr) DBC_ASSERT_SAFE(dbc::contract::precondition, expr, "")
#define DBC_REQUIRE_SAFE2(expr, msg) DBC_ASSERT_SAFE(dbc::contract::precondition, expr, msg)

#define DBCENSURE_CRITICAL1(expr) DBC_ASSERT_CRITICAL(dbc::contract::postcondition, expr, "")
#define DBCENSURE_CRITICAL2(expr, msg) DBC_ASSERT_CRITICAL(dbc::contract::postcondition, expr, msg)

#define DBC_ENSURE1(expr) DBC_ASSERT(dbc::contract::postcondition, expr, "")
#define DBC_ENSURE2(expr, msg) DBC_ASSERT(dbc::contract::postcondition, expr, msg)

#define DBC_ENSURE_SAFE1(expr) DBC_ASSERT_SAFE(dbc::contract::postcondition, expr, "")
#define DBC_ENSURE_SAFE2(expr, msg) DBC_ASSERT_SAFE(dbc::contract::postcondition, expr, msg)

#define DBC_EXPAND(x) x                       // MSVC workaround
#define DBC_GET_MACRO(_1, _2, NAME, ...) NAME // Macro overloading trick

#define INVARIANT_CRITICAL(...)                                                                    \
    DBC_EXPAND(                                                                                    \
        DBC_GET_MACRO(__VA_ARGS__, DBC_INVARIANT_CRITICAL2, DBC_INVARIANT_CRITICAL1)(__VA_ARGS__))

#define INVARIANT(...)                                                                             \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_INVARIANT2, DBC_INVARIANT1)(__VA_ARGS__))

#define INVARIANT_SAFE(...)                                                                        \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_INVARIANT_SAFE2, DBC_INVARIANT_SAFE1)(__VA_ARGS__))

#define REQUIRE_CRITICAL(...)                                                                      \
    DBC_EXPAND(                                                                                    \
        DBC_GET_MACRO(__VA_ARGS__, DBC_REQUIRE_CRITICAL2, DBC_REQUIRE_CRITICAL1)(__VA_ARGS__))

#define REQUIRE(...) DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_REQUIRE2, DBC_REQUIRE1)(__VA_ARGS__))

#define REQUIRE_SAFE(...)                                                                          \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_REQUIRE_SAFE2, DBC_REQUIRE_SAFE1)(__VA_ARGS__))

#define ENSURE_CRITICAL(...)                                                                       \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBCENSURE_CRITICAL2, DBCENSURE_CRITICAL1)(__VA_ARGS__))

#define ENSURE(...) DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_ENSURE2, DBC_ENSURE1)(__VA_ARGS__))

#define ENSURE_SAFE(...)                                                                           \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_ENSURE_SAFE2, DBC_ENSURE_SAFE1)(__VA_ARGS__))

/** @} */

#endif // DBC_ERROR_CHECKING_H
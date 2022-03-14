/**
 * @file dbc.hpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Distributes public macros that facilitate a simple, developer time,
 * design by contract support.
 * @version 3.0
 * @date 2021-10-29S
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "details/dbc_private.hpp"
#include <iostream>

#if defined(DBC_ABORT)

#define DBC_ASSERT1(type, condition)                                           \
    dbc::details::abort({type, #condition, __FUNCTION__, __FILE__, __LINE__});

#define DBC_ASSERT2(type, condition, message)                                  \
    dbc::details::abort(                                                       \
        {type, #condition, __FUNCTION__, __FILE__, __LINE__, message});

#elif defined(DBC_TERMINATE)

#define DBC_ASSERT1(type, condition)                                           \
    dbc::details::terminate(                                                   \
        {type, #condition, __FUNCTION__, __FILE__, __LINE__});

#define DBC_ASSERT2(type, condition, message)                                  \
    dbc::details::terminate(                                                   \
        {type, #condition, __FUNCTION__, __FILE__, __LINE__, message});

#elif defined(DBC_THROW)

#define DBC_ASSERT1(type, condition)                                           \
    dbc::details::raise({type, #condition, __FUNCTION__, __FILE__, __LINE__});

#define DBC_ASSERT2(type, condition, message)                                  \
    dbc::details::raise(                                                       \
        {type, #condition, __FUNCTION__, __FILE__, __LINE__, message});

#elif defined(DBC_NOTHROW)

#define DBC_ASSERT1(type, condition)          (void(0))
#define DBC_ASSERT2(type, condition, message) (void(0))

#else

#define DBC_ASSERT1(type, condition)          (void(0))
#define DBC_ASSERT2(type, condition, message) (void(0))

#endif

#define DBC_INVARIANT1(condition)                                              \
    DBC_ASSERT1("Invariant violation: ", condition)
#define DBC_INVARIANT2(condition, message)                                     \
    DBC_ASSERT2("Invariant violation: ", condition, message)

#define DBC_PRECONDITION1(condition)                                           \
    DBC_ASSERT1("Precondition violation: ", condition)
#define DBC_PRECONDITION2(condition, message)                                  \
    DBC_ASSERT2("Precondition violation: ", condition, message)

#define DBC_POSTCONDITION1(condition)                                          \
    DBC_ASSERT1("Postcondition violation: ", condition)
#define DBC_POSTCONDITION1(condition, message)                                 \
    DBC_ASSERT2("Postcondition violation: ", condition, message)

// litle trick to emulate function overloading via preprocessing magic
#define DBC_EXPAND(x)                    x
#define DBC_GET_MACRO(_1, _2, NAME, ...) NAME

/**
 * @brief Macro to assert a class/loop invariant.
 *
 */
#define INVARIANT(...)                                                         \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_INVARIANT2,                      \
                             DBC_INVARIANT1)(__VA_ARGS__))

/**
 * @brief Macro to assert a precondition.
 *
 */
#define PRECONDITION(...)                                                      \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_PRECONDITION2,                   \
                             DBC_PRECONDITION1)(__VA_ARGS__))

/**
 * @brief Macro to assert a postcondition.
 *
 */
#define POSTCONDITION(...)                                                     \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_POSTCONDITION2,                  \
                             DBC_POSTCONDITION1)(__VA_ARGS__))

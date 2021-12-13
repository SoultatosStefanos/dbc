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

#include <iostream>

#ifdef NDEBUG

#define DBC_INVARIANT1(condition)              (void(0))
#define DBC_INVARIANT2(condition, message)     (void(0))

#define DBC_PRECONDITION1(condition)           (void(0))
#define DBC_PRECONDITION2(condition, message)  (void(0))

#define DBC_POSTCONDITION1(condition)          (void(0))
#define DBC_POSTCONDITION2(condition, message) (void(0))

#else

#define DBC_FAIL(context, condition, message)                                  \
    do {                                                                       \
        std::cerr << context << " (" << #condition << "), "                    \
                  << "function: " << __FUNCTION__ << ", file: " << __FILE__    \
                  << ", line: " << __LINE__ << "." << '\n'                     \
                  << message << '\n';                                          \
        std::terminate();                                                      \
    }                                                                          \
    while(0)

#define DBC_INVARIANT1(condition)                                              \
    do {                                                                       \
        if(!(condition)) DBC_FAIL("Invariant violation:", condition, "");      \
    }                                                                          \
    while(0)

#define DBC_INVARIANT2(condition, message)                                     \
    do {                                                                       \
        if(!(condition)) DBC_FAIL("Invariant violation:", condition, message); \
    }                                                                          \
    while(0)

#define DBC_PRECONDITION1(condition)                                           \
    do {                                                                       \
        if(!(condition)) DBC_FAIL("Precondition violation:", condition, "");   \
    }                                                                          \
    while(0)

#define DBC_PRECONDITION2(condition, message)                                  \
    do {                                                                       \
        if(!(condition))                                                       \
            DBC_FAIL("Precondition violation:", condition, message);           \
    }                                                                          \
    while(0)

#define DBC_POSTCONDITION1(condition)                                          \
    do {                                                                       \
        if(!(condition)) DBC_FAIL("Postcondition violation:", condition, "");  \
    }                                                                          \
    while(0)

#define DBC_POSTCONDITION2(condition, message)                                 \
    do {                                                                       \
        if(!(condition))                                                       \
            DBC_FAIL("Postcondition violation:", condition, message);          \
    }                                                                          \
    while(0)

#endif

#define DBC_EXPAND(x)                    x
#define DBC_GET_MACRO(_1, _2, NAME, ...) NAME

#define INVARIANT(...)                                                         \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_INVARIANT2,                      \
                             DBC_INVARIANT1)(__VA_ARGS__))

#define PRECONDITION(...)                                                      \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_PRECONDITION2,                   \
                             DBC_PRECONDITION1)(__VA_ARGS__))

#define POSTCONDITION(...)                                                     \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_POSTCONDITION2,                  \
                             DBC_POSTCONDITION1)(__VA_ARGS__))

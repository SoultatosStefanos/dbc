/**
 * @file dbc.hpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Distributes public macros that facilitate a simple, developer time,
 * design by contract support, plus a generic contract violation exception.
 * @version 4.0
 * @date 2021-10-29S
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <iostream>

namespace dbc::details {

// debug info, concerning the location where the contract violation took
// place
struct violation_context {
    std::string type;
    std::string condition;
    std::string function;
    std::string file;
    int line;
    std::string message;
};

// formulate a violation context error message
[[nodiscard]] inline auto
make_violation_message(const violation_context& context)
{
    return context.type + " (" + context.condition + "), " + "function: "
           + context.function + ", file: " + context.file + ", line: "
           + std::to_string(context.line) + "." + '\n' + context.message;
}

// log a violation context error message to std::cerr
inline void log_violation_message(const violation_context& context)
{
    std::cerr << make_violation_message(context) << '\n';
}

} // namespace dbc::details

#if defined(DBC_ABORT)

namespace dbc::details {

// log a violation context error message and abort
[[noreturn]] inline void abort(const violation_context& context) noexcept

{
    log_violation_message(context);
    std::abort();
}

} // namespace dbc::details

#define DBC_ASSERT1(type, condition)                                           \
    do {                                                                       \
        if(!(condition))                                                       \
            dbc::details::abort(                                               \
                {type, #condition, __FUNCTION__, __FILE__, __LINE__, ""});     \
    }                                                                          \
    while(0)

#define DBC_ASSERT2(type, condition, message)                                  \
    do {                                                                       \
        if(!(condition))                                                       \
            dbc::details::abort({type, #condition, __FUNCTION__, __FILE__,     \
                                 __LINE__, message});                          \
    }                                                                          \
    while(0)

#elif defined(DBC_TERMINATE)

namespace dbc::details {

// log a violation context error message and terminate
[[noreturn]] inline void terminate(const violation_context& context) noexcept

{
    log_violation_message(context);
    std::terminate();
}

} // namespace dbc::details

#define DBC_ASSERT1(type, condition)                                           \
    do {                                                                       \
        if(!(condition))                                                       \
            dbc::details::terminate(                                           \
                {type, #condition, __FUNCTION__, __FILE__, __LINE__, ""});     \
    }                                                                          \
    while(0)

#define DBC_ASSERT2(type, condition, message)                                  \
    do {                                                                       \
        if(!(condition))                                                       \
            dbc::details::terminate({type, #condition, __FUNCTION__, __FILE__, \
                                     __LINE__, message});                      \
    }                                                                          \
    while(0)

#elif defined(DBC_THROW)

namespace dbc {

/**
 * @brief Generic contract violation exception, covers pre/post condition plus
 * invariant violations
 *
 */
class contract_violation : public std::logic_error {
public:
    contract_violation(const std::string& what_arg): std::logic_error(what_arg)
    {}
};

namespace details {

// simply abstracts a throw with a context error message
inline void raise(const violation_context& context)
{
    throw contract_violation(make_violation_message(context));
}

} // namespace details

} // namespace dbc

#define DBC_ASSERT1(type, condition)                                           \
    do {                                                                       \
        if(!(condition))                                                       \
            dbc::details::raise(                                               \
                {type, #condition, __FUNCTION__, __FILE__, __LINE__, ""});     \
    }                                                                          \
    while(0)

#define DBC_ASSERT2(type, condition, message)                                  \
    do {                                                                       \
        if(!(condition))                                                       \
            dbc::details::raise({type, #condition, __FUNCTION__, __FILE__,     \
                                 __LINE__, message});                          \
    }

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
#define DBC_POSTCONDITION2(condition, message)                                 \
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

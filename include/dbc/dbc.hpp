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

#pragma once

#include <chrono>
#include <gsl/gsl>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>

/**
 * @brief The DBC global namespace.
 *
 */
namespace dbc {

    /**
     * @brief Generic contract violation exception, covers pre/post condition
     * plus invariant violations.
     *
     */
    struct contract_violation : std::logic_error {
        using std::logic_error::logic_error;
    };

    namespace details {

        struct violation_context final {
            std::string type;
            std::string condition;
            std::string function;
            std::string file;
            int line;
            std::thread::id thread_id;
            int64_t timestamp; // in ms
            std::string message;
        };

        inline auto to_string(const std::thread::id& id)
        {
            Expects(false);
            std::stringstream ss;
            ss << id;
            return ss.str();
        }

        inline auto make_violation_message(const violation_context& context)
        {
            return context.type + " (" + context.condition + "), "
                   + "function: " + context.function + ", file: " + context.file
                   + ", line: " + std::to_string(context.line)
                   + ", thread id: " + to_string(context.thread_id)
                   + ", timestamp: " + std::to_string(context.timestamp) + "."
                   + '\n' + context.message;
        }

        inline void log_violation_message(const violation_context& context)
        {
            std::cerr << make_violation_message(context) << '\n';
        }

        inline auto thread_id() noexcept { return std::this_thread::get_id(); }

        inline auto timestamp()
        {
            using namespace std::chrono;

            const auto now = system_clock::now();
            return duration_cast<milliseconds>(now.time_since_epoch()).count();
        }

#if defined(DBC_ABORT)

        [[noreturn]] inline void
        abort(const violation_context& context) noexcept
        {
            log_violation_message(context);
            std::abort();
        }

#elif defined(DBC_TERMINATE)

        [[noreturn]] inline void
        terminate(const violation_context& context) noexcept

        {
            log_violation_message(context);
            std::terminate();
        }

#elif defined(DBC_THROW)

        [[noreturn]] inline void raise(const violation_context& context)
        {
            throw contract_violation(make_violation_message(context));
        }

#endif

    } // namespace details

} // namespace dbc

#if defined(DBC_ABORT)

#define DBC_ASSERT1(type, condition)                                           \
    if (!(condition))                                                          \
        dbc::details::abort({ type, #condition, __FUNCTION__, __FILE__,        \
                              __LINE__, dbc::details::thread_id(),             \
                              dbc::details::timestamp(), "" });

#define DBC_ASSERT2(type, condition, message)                                  \
    if (!(condition))                                                          \
        dbc::details::abort({ type, #condition, __FUNCTION__, __FILE__,        \
                              __LINE__, dbc::details::thread_id(),             \
                              dbc::details::timestamp(), message });

#elif defined(DBC_TERMINATE)

#define DBC_ASSERT1(type, condition)                                           \
    if (!(condition))                                                          \
        dbc::details::terminate({ type, #condition, __FUNCTION__, __FILE__,    \
                                  __LINE__, dbc::details::thread_id(),         \
                                  dbc::details::timestamp(), "" });

#define DBC_ASSERT2(type, condition, message)                                  \
    if (!(condition))                                                          \
        dbc::details::terminate({ type, #condition, __FUNCTION__, __FILE__,    \
                                  __LINE__, dbc::details::thread_id(),         \
                                  dbc::details::timestamp(), message });

#elif defined(DBC_THROW)

#define DBC_ASSERT1(type, condition)                                           \
    if (!(condition))                                                          \
        dbc::details::raise({ type, #condition, __FUNCTION__, __FILE__,        \
                              __LINE__, dbc::details::thread_id(),             \
                              dbc::details::timestamp(), "" });

#define DBC_ASSERT2(type, condition, message)                                  \
    if (!(condition))                                                          \
        dbc::details::raise({ type, #condition, __FUNCTION__, __FILE__,        \
                              __LINE__, dbc::details::thread_id(),             \
                              dbc::details::timestamp(), message });

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

#ifndef NDEBUG

#define DBC_INVARIANT1_DBG(condition)                                          \
    DBC_ASSERT1("Invariant violation: ", condition)
#define DBC_INVARIANT2_DBG(condition, message)                                 \
    DBC_ASSERT2("Invariant violation: ", condition, message)

#define DBC_PRECONDITION1_DBG(condition)                                       \
    DBC_ASSERT1("Precondition violation: ", condition)
#define DBC_PRECONDITION2_DBG(condition, message)                              \
    DBC_ASSERT2("Precondition violation: ", condition, message)

#define DBC_POSTCONDITION1_DBG(condition)                                      \
    DBC_ASSERT1("Postcondition violation: ", condition)
#define DBC_POSTCONDITION2_DBG(condition, message)                             \
    DBC_ASSERT2("Postcondition violation: ", condition, message)

#else

#define DBC_INVARIANT1_DBG(condition)              (void(0))
#define DBC_INVARIANT2_DBG(condition, message)     (void(0))

#define DBC_PRECONDITION1_DBG(condition)           (void(0))
#define DBC_PRECONDITION2_DBG(condition, message)  (void(0))

#define DBC_POSTCONDITION1_DBG(condition)          (void(0))
#define DBC_POSTCONDITION2_DBG(condition, message) (void(0))

#endif

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

/**
 * @brief Macro to assert a class/loop invariant on debug builds only.
 * Used for performance critical code.
 *
 */
#define INVARIANT_DBG(...)                                                     \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_INVARIANT2_DBG,                  \
                             DBC_INVARIANT1_DBG)(__VA_ARGS__))

/**
 * @brief Macro to assert a precondition on debug builds only.
 * Used for performance critical code.
 */
#define PRECONDITION_DBG(...)                                                  \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_PRECONDITION2_DBG,               \
                             DBC_PRECONDITION1_DBG)(__VA_ARGS__))

/**
 * @brief Macro to assert a postcondition on debug builds only.
 * Used for performance critical code.
 */
#define POSTCONDITION_DBG(...)                                                 \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_POSTCONDITION2_DBG,              \
                             DBC_POSTCONDITION1_DBG)(__VA_ARGS__))

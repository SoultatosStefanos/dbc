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

#include <array>
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>

/**
 * @brief The DBC global namespace.
 *
 */
namespace dbc {

    /**
     * @brief A contract type (Precondition, Postcondition, Invariant).
     *
     */
    enum class contract_type { precondition = 0, postcondition, invariant };

    /**
     * @brief Returns a string view representation of a contract type.
     *
     * @param type the contract type from which to formulate the string view
     *
     * @return a string view representation of a contract type
     *
     * @throws std::invalid_argument if the type is non enumerated
     */
    constexpr auto to_string_view(contract_type type)
    {
        using namespace std::literals;
        using enum contract_type;

        switch (type) {
        case precondition:
            return "Precondition"sv;
        case postcondition:
            return "Postcondition"sv;
        case invariant:
            return "Invariant"sv;
        default:
            throw std::invalid_argument(
                "unknown enum value: "
                + std::to_string(static_cast<int>(type)));

            return ""sv;
        }
    }

    /**
     * @brief Debug info, consisting of the context where a contract violation
     * took place.
     *
     */
    struct violation_context {
        /** @brief The type of the contract violation. (pre/post/inv) */
        contract_type type;

        /** @brief The boolean expression that failed. */
        std::string_view condition;

        /** @brief The function where the violation took place. */
        std::string_view function;

        /** @brief The file where the violation took place. */
        std::string_view file;

        /** @brief The line where the violation took place. */
        int32_t line;

        /** @brief The id of the thread that is responsible for the violation.*/
        std::string thread_id;

        /** @brief The timestamp (ms) where the violation took place. */
        int64_t timestamp;

        /** @brief An optional explanatory error message about the violation.*/
        std::string_view message;
    };

    inline auto operator==(const violation_context& lhs,
                           const violation_context& rhs)
    {
        return lhs.type == rhs.type and lhs.condition == rhs.condition
               and lhs.file == rhs.file and lhs.function == rhs.function
               and lhs.line == rhs.line and lhs.message == rhs.message
               and lhs.thread_id == rhs.thread_id
               and lhs.timestamp == rhs.timestamp;
    }

    inline auto operator!=(const violation_context& lhs,
                           const violation_context& rhs)
    {
        return !(lhs == rhs);
    }

    inline auto operator<<(std::ostream& os, const violation_context& context)
        -> auto&
    {
        return os << to_string_view(context.type) << " violation: ("
                  << context.condition << "), "
                  << "function: " << context.function
                  << ", file: " << context.file << ", line: " << context.line
                  << ", thread id: " << context.thread_id
                  << ", timestamp: " << context.timestamp << "." << '\n'
                  << context.message;
    }

    /**
     * @brief Returns a string representation of a violation context.
     *
     * @param context the context from which to formulate the string
     * representation
     *
     * @return a string representation of a violation context
     */
    inline auto to_string(const violation_context& context)
    {
        return std::string(to_string_view(context.type)) + " violation: ("
               + std::string(context.condition) + "), "
               + "function: " + std::string(context.function)
               + ", file: " + std::string(context.file)
               + ", line: " + std::to_string(context.line)
               + ", thread id: " + context.thread_id
               + ", timestamp: " + std::to_string(context.timestamp) + "."
               + '\n' + std::string(context.message);
    }

    namespace details {

        // Returns this cuurent thread id
        inline auto get_thread_id()
        {
            const auto id = std::this_thread::get_id();
            std::stringstream ss;
            ss << id;
            return ss.str();
        }

        // Returns the current timestamp, since the first epoch, in ms
        inline auto get_timestamp()
        {
            using namespace std::chrono;

            const auto now = system_clock::now();
            return duration_cast<milliseconds>(now.time_since_epoch()).count();
        }

    } // namespace details

#if defined(DBC_ABORT)

    namespace details {

        // Logs the violation info to std::cerr and aborts.
        [[noreturn]] inline void abort_handler(const violation_context& c)
        {
            std::cerr << to_string(c) << '\n';
            std::abort();
        }

    } // namespace details

#define DBC_ASSERT1(type, condition)                                           \
    if (!(condition))                                                          \
        dbc::details::abort_handler({ type, #condition, __FUNCTION__,          \
                                      __FILE__, __LINE__,                      \
                                      dbc::details::get_thread_id(),           \
                                      dbc::details::get_timestamp(), "" });

#define DBC_ASSERT2(type, condition, message)                                  \
    if (!(condition))                                                          \
        dbc::details::abort_handler(                                           \
            { type, #condition, __FUNCTION__, __FILE__, __LINE__,              \
              dbc::details::get_thread_id(), dbc::details::get_timestamp(),    \
              message });

#elif defined(DBC_TERMINATE)

    namespace details {

        // Logs the violation info to std::cerr and terminates.
        [[noreturn]] inline void terminate_handler(const violation_context& c)
        {
            std::cerr << to_string(c) << '\n';
            std::terminate();
        }

    } // namespace details

#define DBC_ASSERT1(type, condition)                                           \
    if (!(condition))                                                          \
        dbc::details::terminate_handler(                                       \
            { type, #condition, __FUNCTION__, __FILE__, __LINE__,              \
              dbc::details::get_thread_id(), dbc::details::get_timestamp(),    \
              "" });

#define DBC_ASSERT2(type, condition, message)                                  \
    if (!(condition))                                                          \
        dbc::details::terminate_handler(                                       \
            { type, #condition, __FUNCTION__, __FILE__, __LINE__,              \
              dbc::details::get_thread_id(), dbc::details::get_timestamp(),    \
              message });

#elif defined(DBC_THROW)

    /**
     * @brief A contract violation error.
     *
     */
    class contract_violation : public std::logic_error {
    public:
        /** @brief Converts a contract violation to s string. */
        using converter = std::function<std::string(const violation_context&)>;

        /**
         * @brief Constructs the contract violation by a context.
         *
         * @param context the contract violation context.
         * @param f a converter function that formulates a string from the
         * context, defaults to dbc::to_string and must not be empty
         *
         * @throws std::invalid_argument if the converter is empty
         */
        explicit contract_violation(const violation_context& context,
                                    const converter& f = to_string)
            : logic_error(std::invoke(filter(f), context)), m_context(context)
        {}

        /**
         * @brief Returns the contract violation context.
         *
         * @return the contract violation context
         */
        auto context() const -> const violation_context& { return m_context; };

    protected:
        /**
         * @brief Assures that a converter function is not empty.
         *
         * @param f the converter function, must not be empty
         *
         * @return the converter function if it's not empty
         *
         * @throws std::invalid_argument if the converter is empty
         */
        auto filter(const converter& f) const -> converter
        {
            if (!f) throw std::invalid_argument("empty converter");
            return f;
        }

    private:
        violation_context m_context;
    };

    namespace details {

        // Throws a contract_violation with the violation context
        [[noreturn]] inline void throw_handler(const violation_context& c)
        {
            throw contract_violation(c);
        }

    } // namespace details

#define DBC_ASSERT1(type, condition)                                           \
    if (!(condition))                                                          \
        dbc::details::throw_handler({ type, #condition, __FUNCTION__,          \
                                      __FILE__, __LINE__,                      \
                                      dbc::details::get_thread_id(),           \
                                      dbc::details::get_timestamp(), "" });

#define DBC_ASSERT2(type, condition, message)                                  \
    if (!(condition))                                                          \
        dbc::details::throw_handler(                                           \
            { type, #condition, __FUNCTION__, __FILE__, __LINE__,              \
              dbc::details::get_thread_id(), dbc::details::get_timestamp(),    \
              message });

#elif defined(DBC_CUSTOM)

    /** @brief A violation context handler function. */
    using violation_handler = std::function<void(const violation_context&)>;

    namespace details {

        // Returns the violation handler
        inline auto get_handler() -> auto&
        {
            static violation_handler handler = [](const auto&) {}; // noop
            return handler;
        }

        // Invokes the set handler with the context
        inline void handle(const violation_context& context)
        {
            assert(get_handler());
            get_handler()(context);
        }

    } // namespace details

    /**
     * @brief Sets the global contract violation handler.
     *
     * @param f the global contract violation handler, not empty
     *
     * @throws std::invalid_argument if the violation handler function is empty
     */
    inline void set_violation_handler(const violation_handler& f)
    {
        if (!f) throw std::invalid_argument("empty violation handler");
        details::get_handler() = f;
    }

#define DBC_ASSERT1(type, condition)                                           \
    if (!(condition))                                                          \
        dbc::details::handle({ type, #condition, __FUNCTION__, __FILE__,       \
                               __LINE__, dbc::details::get_thread_id(),        \
                               dbc::details::get_timestamp(), "" });

#define DBC_ASSERT2(type, condition, message)                                  \
    if (!(condition))                                                          \
        dbc::details::handle({ type, #condition, __FUNCTION__, __FILE__,       \
                               __LINE__, dbc::details::get_thread_id(),        \
                               dbc::details::get_timestamp(), message });

#else

#define DBC_ASSERT1(type, condition)          (void(0))
#define DBC_ASSERT2(type, condition, message) (void(0))

#endif

#define DBC_INVARIANT1(condition)                                              \
    DBC_ASSERT1(dbc::contract_type::invariant, condition)
#define DBC_INVARIANT2(condition, message)                                     \
    DBC_ASSERT2(dbc::contract_type::invariant, condition, message)

#define DBC_PRECONDITION1(condition)                                           \
    DBC_ASSERT1(dbc::contract_type::precondition, condition)
#define DBC_PRECONDITION2(condition, message)                                  \
    DBC_ASSERT2(dbc::contract_type::precondition, condition, message)

#define DBC_POSTCONDITION1(condition)                                          \
    DBC_ASSERT1(dbc::contract_type::postcondition, condition)
#define DBC_POSTCONDITION2(condition, message)                                 \
    DBC_ASSERT2(dbc::contract_type::postcondition, condition, message)

#ifndef NDEBUG

#define DBC_INVARIANT1_DBG(condition) DBC_INVARIANT1(condition)
#define DBC_INVARIANT2_DBG(condition, message)                                 \
    DBC_INVARIANT2(condition, message)

#define DBC_PRECONDITION1_DBG(condition) DBC_PRECONDITION1(condition)
#define DBC_PRECONDITION2_DBG(condition, message)                              \
    DBC_PRECONDITION2(condition, message)

#define DBC_POSTCONDITION1_DBG(condition) DBC_POSTCONDITION1(condition)
#define DBC_POSTCONDITION2_DBG(condition, message)                             \
    DBC_POSTCONDITION2(condition, message)

#else

#define DBC_INVARIANT1_DBG(condition)              (void(0))
#define DBC_INVARIANT2_DBG(condition, message)     (void(0))

#define DBC_PRECONDITION1_DBG(condition)           (void(0))
#define DBC_PRECONDITION2_DBG(condition, message)  (void(0))

#define DBC_POSTCONDITION1_DBG(condition)          (void(0))
#define DBC_POSTCONDITION2_DBG(condition, message) (void(0))

#endif

} // namespace dbc

// Macro overloading via pre-processor magic
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

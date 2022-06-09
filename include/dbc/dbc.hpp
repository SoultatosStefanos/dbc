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

#ifndef DBC_H
#define DBC_H

#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <thread>

#define DBC_API

// PURPOSE: Provide build-specific, runtime-configurable, Design By Contract style, assertion
// macros, with powerful debugging capabilities. Macros: DBC_REQUIRE, DBC_ENSURE, DBC_INVARIANT

namespace dbc
{

// ------------------------- Error Reporting ---------------------------------------------- //

/** @defgroup error_reporting Error Reporting
 *  @{
 */

/**
 * @brief A Design By Contract contract enumeration.
 *
 */
DBC_API enum class contract { precondition = 0, postcondition, invariant };

/**
 * @brief Returns an std::string_view representation of a dbc::contract.
 *
 * @param type the contract
 *
 * @return an std::string_view representation of a dbc::contract, or an empty string literal if the
 * contract type is not enumerated to a dbc pre/post condition or invariant
 */
DBC_API constexpr auto to_string_view(contract type) noexcept
{
    using namespace std::literals;
    using enum contract;

    switch (type)
    {
    case precondition:
        return "Precondition"sv;
    case postcondition:
        return "Postcondition"sv;
    case invariant:
        return "Invariant"sv;
    default:
        return ""sv;
    }
}

/**
 * @brief An aggregate containing the context of a contract violation.
 * Provides useful debug info concerning the contract type, the reported failed condition, the
 * function, file, line, thread, timestamp and an optional, developer friendly, error message.
 *
 */
DBC_API struct violation_context
{
    contract type;
    std::string_view condition; // a boolean expression string_view representation, always false
    std::string decomposition;  // the decomposition of the boolean expression
    std::string_view function;
    std::string_view file;
    int32_t line;
    std::size_t thread_id; // hashed to a unique size_t
    int64_t timestamp;
    std::string_view message;

    auto operator==(const violation_context&) const noexcept -> bool = default;
    auto operator!=(const violation_context&) const noexcept -> bool = default;
};

/**
 * @brief Operator << overload for a dbc::violation_context.
 *
 * Example output:
 *
 * \verbatim
 * Design By Contract VIOLATION:
 * Invariant:
 *   8 == x
 * with expansion:
 *   8 == 99
 * Function: main, file: path_to_buzz/buzz.cpp, line: 100
 * Thread id: 1659603145605012203, timestamp(ms): 1650122348195
 * \endverbatim
 *
 */
DBC_API inline auto operator<<(std::ostream& os, const violation_context& context) -> std::ostream&
{
    return os << "Design By Contract VIOLATION:\n"
              << to_string_view(context.type) << ":\n  " << context.condition
              << "\nwith expansion:\n  " << context.decomposition
              << "\nFunction: " << context.function << ", file: " << context.file
              << ", line: " << context.line << "\nThread id: " << context.thread_id
              << ", timestamp(ms): " << context.timestamp << '\n'
              << context.message << '\n';
}

namespace details
{
    // Returns the current thread id, hashed.
    /// @private
    inline auto thread_id() noexcept
    {
        using namespace std;

        return hash<thread::id>()(this_thread::get_id());
    }

    // Returns the current timestamp in ms.
    /// @private
    inline auto timestamp()
    {
        using namespace std::chrono;

        const auto until_now = system_clock::now().time_since_epoch();
        return duration_cast<milliseconds>(until_now).count();
    }

    // Produces a violation context.
    /// @private
    inline auto make_context(contract type, std::string_view condition,
                             const std::string& decomposition, std::string_view function,
                             std::string_view file, int32_t line, std::string_view message)
    {
        return violation_context{type, condition,   decomposition, function, file,
                                 line, thread_id(), timestamp(),   message};
    }

    //
    // Credits to: https://theheisenbugblog.wordpress.com/2014/09/06/c-expression-decomposition/
    //

    struct lhs_decomposer; // fwd declaration

    // Decomposes a boolean expression, given its left hand side operand
    // Makes use of the operator overloads to deduce the right hand operand and the operation.
    class rhs_decomposer
    {
    public:
        template <typename T>
        explicit rhs_decomposer(const T& lhs)
        {
            ss << lhs;
        }

        template <typename T>
        auto operator==(const T& rhs) -> const auto&
        {
            ss << " == " << rhs;
            return *this;
        }

        template <typename T>
        auto operator!=(const T& rhs) -> const auto&
        {
            ss << " != " << rhs;
            return *this;
        }

        template <typename T>
        auto operator<(const T& rhs) -> const auto&
        {
            ss << " < " << rhs;
            return *this;
        }

        template <typename T>
        auto operator>(const T& rhs) -> const auto&
        {
            ss << " > " << rhs;
            return *this;
        }

        template <typename T>
        auto operator<=(const T& rhs) -> const auto&
        {
            ss << " <= " << rhs;
            return *this;
        }

        template <typename T>
        auto operator>=(const T& rhs) -> const auto&
        {
            ss << " >= " << rhs;
            return *this;
        }

        // Returns an std::string decomposition of the boolean expression, of the form:
        //"'lhs' 'operation' 'rhs'""
        auto decomposition() const -> auto { return ss.str(); }

    private:
        std::stringstream ss;
    };

    // Hepler struct, forwards a left hand side opperand to a right hand side decomposer
    struct lhs_decomposer
    {
        template <typename T>
        auto operator->*(const T& lhs) const -> auto
        {
            return rhs_decomposer{lhs};
        }
    };

} // namespace details

/** @} */

} // namespace dbc

// Utility macro to obtain an std::string decomposition of a boolean expression
#define DBC_DECOMPOSE(expr)                                                                        \
    ([]() -> dbc::details::lhs_decomposer { return {}; }()->*expr).decomposition()

// Utility macro to obtain __FUNCTION__, __FILE__ and __LINE__
#define DBC_GET_CONTEXT(type, condition, message)                                                  \
    dbc::details::make_context(type, #condition, DBC_DECOMPOSE(condition), __FUNCTION__, __FILE__, \
                               __LINE__, message)

// ---------------------------------------------------------------------------------------- //

// ------------------------- Error Handling ----------------------------------------------- //

namespace dbc
{

/** @defgroup error_handling Error Handling
 *  @{
 */

/**
 * @brief A violation context, error handler, function alias.
 *
 */
DBC_API using violation_handler = std::function<void(const violation_context&)>;

/**
 * @brief A generic contract violation exception.
 * Encapsulates preconditions, postconditions and invariants violations.
 *
 */
DBC_API class contract_violation : public std::logic_error
{
public:
    explicit contract_violation(const violation_context& context)
        : logic_error{context.message.data()}, m_context{context}
    {}

    /**
     * @brief Returns a read access to the violation context that was handled from this instance.
     *
     * @return a read access to the violation context that was handled from this instance
     */
    auto context() const noexcept -> const auto& { return m_context; };

private:
    violation_context m_context;
};

/**
 * @brief Handles a dbc::violation_context by aborting. Logs the violation to std::cerr.
 *
 * @note This is the default error handler.
 *
 * @param context the violation context to handle
 */
DBC_API [[noreturn]] inline void abort_handler(const violation_context& context)
{
    std::cerr << context << '\n';
    std::abort();
}

/**
 * @brief Handles a dbc::violation_context by throwing a dbc::contract_violation error.
 *
 * @param context the violation context to handle
 */
DBC_API [[noreturn]] inline void throw_handler(const violation_context& context)
{
    throw contract_violation{context};
}

namespace details
{
    // Returns the violation handler function.
    /// @private
    inline auto handler() noexcept -> auto&
    {
        static violation_handler handler = abort_handler;
        return handler;
    }

    // Forwards the reported violation to the set violation handler.
    /// @private
    inline void handle(const violation_context& context) { handler()(context); }

} // namespace details

/**
 * @brief Sets the global violation error handler function.
 * Any reported contract violations will be handled from this function.
 *
 * @param handler the violation handler function
 */
DBC_API inline void set_violation_handler(const violation_handler& handler) noexcept
{
    details::handler() = handler;
}

/** @} */

} // namespace dbc

// ---------------------------------------------------------------------------------------- //

// ------------------------- Error Checking ----------------------------------------------- //

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
 *  Only precondition checks are monitored. Hence, the DBC_REQUIRE checker is the only checker that
 * is not turned to a noop.
 *
 * @par DBC_ASSERT_LEVEL_POSTCONDITIONS
 *  Both preconditions and postconditions, validated with the DBC_REQUIRE and DBC_ENSURE macros, are
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

#if defined(DBC_ASSERT_LEVEL_PRECONDITIONS) || defined(DBC_ASSERT_LEVEL_POSTCONDITIONS) ||         \
    defined(DBC_ASSERT_LEVEL_INVARIANTS)
#error "Multiple DBC assert levels defined"
#endif

#define DBC_REQUIRE1(expr) void(0)
#define DBC_REQUIRE2(expr, msg) void(0)

#define DBC_ENSURE1(expr) void(0)
#define DBC_ENSURE2(expr, msg) void(0)

#define DBC_INVARIANT1(expr) void(0)
#define DBC_INVARIANT2(expr, msg) void(0)

#elif defined(DBC_ASSERT_LEVEL_PRECONDITIONS) // monitor preconditions only

#if defined(DBC_ASSERT_LEVEL_NONE) || defined(DBC_ASSERT_LEVEL_POSTCONDITIONS) ||                  \
    defined(DBC_ASSERT_LEVEL_INVARIANTS)
#error "Multiple DBC assert levels defined"
#endif

#define DBC_REQUIRE1(expr) DBC_ASSERT_IMPL(dbc::contract::precondition, expr, "")
#define DBC_REQUIRE2(expr, msg) DBC_ASSERT_IMPL(dbc::contract::precondition, expr, msg)

#define DBC_ENSURE1(expr) void(0)
#define DBC_ENSURE2(expr, msg) void(0)

#define DBC_INVARIANT1(expr) void(0)
#define DBC_INVARIANT2(expr, msg) void(0)

#elif defined(DBC_ASSERT_LEVEL_POSTCONDITIONS) // monitor preconditions and postconditions

#if defined(DBC_ASSERT_LEVEL_PRECONDITIONS) || defined(DBC_ASSERT_LEVEL_NONE) ||                   \
    defined(DBC_ASSERT_LEVEL_INVARIANTS)
#error "Multiple DBC assert levels defined"
#endif

#define DBC_REQUIRE1(expr) DBC_ASSERT_IMPL(dbc::contract::precondition, expr, "")
#define DBC_REQUIRE2(expr, msg) DBC_ASSERT_IMPL(dbc::contract::precondition, expr, msg)

#define DBC_ENSURE1(expr) DBC_ASSERT_IMPL(dbc::contract::postcondition, expr, "")
#define DBC_ENSURE2(expr, msg) DBC_ASSERT_IMPL(dbc::contract::postcondition, expr, msg)

#define DBC_INVARIANT1(expr) void(0)
#define DBC_INVARIANT2(expr, msg) void(0)

#elif defined(DBC_ASSERT_LEVEL_INVARIANTS) // monitor preconditions, postconditions and invariants

#if defined(DBC_ASSERT_LEVEL_PRECONDITIONS) || defined(DBC_ASSERT_LEVEL_POSTCONDITIONS) ||         \
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

#define DBC_REQUIRE(...)                                                                           \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_REQUIRE2, DBC_REQUIRE1)(__VA_ARGS__))

#define DBC_ENSURE(...)                                                                            \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_ENSURE2, DBC_ENSURE1)(__VA_ARGS__))

#define DBC_INVARIANT(...)                                                                         \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_INVARIANT2, DBC_INVARIANT1)(__VA_ARGS__))

/** @} */

// ---------------------------------------------------------------------------------------- //

#endif // DBC_H
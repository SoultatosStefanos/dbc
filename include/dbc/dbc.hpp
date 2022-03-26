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

#include <cassert>     // for assert
#include <chrono>      // for system_clock, duration_cast, miliseconds
#include <functional>  // for function, invoke
#include <iostream>    // for cout
#include <sstream>     // for stringstream
#include <stdexcept>   // for logic_error, invalid_argument
#include <string>      // for string
#include <string_view> // for string_view
#include <thread>      // for get_id

namespace dbc
{

enum class contract_type
{
    precondition = 0,
    postcondition,
    invariant
};

constexpr auto to_string_view(contract_type type)
{
    using namespace std::literals;
    using enum contract_type;

    switch (type)
    {
    case precondition:
        return "Precondition"sv;
    case postcondition:
        return "Postcondition"sv;
    case invariant:
        return "Invariant"sv;
    default:
        throw std::invalid_argument("unknown enum value");
        assert(false); // how did we get here?
        return ""sv;   // to please the compiler
    }
}

// violation_context
//
// Debug info concerning a contract violation.
//
struct violation_context
{
    contract_type type;
    std::string_view condition;
    std::string_view function;
    std::string_view file;
    int32_t line;
    std::string thread_id;
    int64_t timestamp; // in ms
    std::string_view message;
};

inline auto operator==(const violation_context& lhs, const violation_context& rhs)
{
    return lhs.type == rhs.type and lhs.condition == rhs.condition and lhs.file == rhs.file and
           lhs.function == rhs.function and lhs.line == rhs.line and lhs.message == rhs.message and
           lhs.thread_id == rhs.thread_id and lhs.timestamp == rhs.timestamp;
}

inline auto operator!=(const violation_context& lhs, const violation_context& rhs)
{
    return !(lhs == rhs);
}

// provide overload that takes advantage of the std::string_view's efficiency
inline auto operator<<(std::ostream& os, const violation_context& context) -> auto&
{
    return os << to_string_view(context.type) << " violation: (" << context.condition << "), "
              << "function: " << context.function << ", file: " << context.file
              << ", line: " << context.line << ", thread id: " << context.thread_id
              << ", timestamp: " << context.timestamp << "." << '\n'
              << context.message;
}

// a useful violation string representation
inline auto to_string(const violation_context& context)
{
    return std::string(to_string_view(context.type)) + " violation: (" +
           std::string(context.condition) + "), " + "function: " + std::string(context.function) +
           ", file: " + std::string(context.file) + ", line: " + std::to_string(context.line) +
           ", thread id: " + context.thread_id +
           ", timestamp: " + std::to_string(context.timestamp) + "." + '\n' +
           std::string(context.message);
}

namespace details
{
    inline auto get_thread_id() // this thread
    {
        const auto id = std::this_thread::get_id();
        std::stringstream ss;
        ss << id;
        return ss.str();
    }

    inline auto get_timestamp() // in ms
    {
        using namespace std::chrono;

        const auto now = system_clock::now();
        return duration_cast<milliseconds>(now.time_since_epoch()).count();
    }
} // namespace details

#if defined(DBC_ABORT)

#if defined(DBC_TERMINATE) || defined(DBC_THROW) || defined(DBC_CUSTOM)
#error Definition of multiple DBC flags
#endif

namespace details
{
    [[noreturn]] inline void abort_handler(const violation_context& c)
    {
        std::cerr << to_string(c) << '\n';
        std::abort();
    }
} // namespace details

#define DBC_ASSERT1(type, condition)                                                               \
    if (!(condition))                                                                              \
        dbc::details::abort_handler({type, #condition, __FUNCTION__, __FILE__, __LINE__,           \
                                     dbc::details::get_thread_id(), dbc::details::get_timestamp(), \
                                     ""});

#define DBC_ASSERT2(type, condition, message)                                                      \
    if (!(condition))                                                                              \
        dbc::details::abort_handler({type, #condition, __FUNCTION__, __FILE__, __LINE__,           \
                                     dbc::details::get_thread_id(), dbc::details::get_timestamp(), \
                                     message});

#elif defined(DBC_TERMINATE)

#if defined(DBC_ABORT) || defined(DBC_THROW) || defined(DBC_CUSTOM)
#error Definition of multiple DBC flags
#endif

namespace details
{
    [[noreturn]] inline void terminate_handler(const violation_context& c)
    {
        std::cerr << to_string(c) << '\n';
        std::terminate();
    }
} // namespace details

#define DBC_ASSERT1(type, condition)                                                               \
    if (!(condition))                                                                              \
        dbc::details::terminate_handler({type, #condition, __FUNCTION__, __FILE__, __LINE__,       \
                                         dbc::details::get_thread_id(),                            \
                                         dbc::details::get_timestamp(), ""});

#define DBC_ASSERT2(type, condition, message)                                                      \
    if (!(condition))                                                                              \
        dbc::details::terminate_handler({type, #condition, __FUNCTION__, __FILE__, __LINE__,       \
                                         dbc::details::get_thread_id(),                            \
                                         dbc::details::get_timestamp(), message});

#elif defined(DBC_THROW)

#if defined(DBC_ABORT) || defined(DBC_TERMINATE) || defined(DBC_CUSTOM)
#error Definition of multiple DBC flags
#endif

// contract_violation
//
// Expresses a DBC contract (pre|post|inv) violation error.
//
class contract_violation : public std::logic_error
{
public:
    using converter = std::function<std::string(const violation_context&)>;

    explicit contract_violation(const violation_context& context, const converter& f = to_string)
        : logic_error(std::invoke(filter(f), context)), m_context(context)
    {}

    auto context() const -> const violation_context& { return m_context; };

protected:
    [[nodiscard]] static auto filter(const converter& f) -> converter
    {
        if (!f) throw std::invalid_argument("empty converter");
        return f;
    }

private:
    violation_context m_context;
};

namespace details
{
    [[noreturn]] inline void throw_handler(const violation_context& c)
    {
        throw contract_violation(c);
    }
} // namespace details

#define DBC_ASSERT1(type, condition)                                                               \
    if (!(condition))                                                                              \
        dbc::details::throw_handler({type, #condition, __FUNCTION__, __FILE__, __LINE__,           \
                                     dbc::details::get_thread_id(), dbc::details::get_timestamp(), \
                                     ""});

#define DBC_ASSERT2(type, condition, message)                                                      \
    if (!(condition))                                                                              \
        dbc::details::throw_handler({type, #condition, __FUNCTION__, __FILE__, __LINE__,           \
                                     dbc::details::get_thread_id(), dbc::details::get_timestamp(), \
                                     message});

#elif defined(DBC_CUSTOM)

#if defined(DBC_ABORT) || defined(DBC_TERMINATE) || defined(DBC_THROW)
#error Definition of multiple DBC flags
#endif

using violation_handler = std::function<void(const violation_context&)>;

namespace details
{
    inline auto get_handler() -> auto&
    {
        static violation_handler handler = [](const auto&) {}; // noop default handler
        return handler;
    }

    inline void handle(const violation_context& context)
    {
        assert(get_handler());
        std::invoke(get_handler(), context);
    }
} // namespace details

inline void set_violation_handler(const violation_handler& f)
{
    assert(details::get_handler());
    if (!f) throw std::invalid_argument("empty violation handler");
    details::get_handler() = f;
    assert(details::get_handler());
}

#define DBC_ASSERT1(type, condition)                                                               \
    if (!(condition))                                                                              \
        dbc::details::handle({type, #condition, __FUNCTION__, __FILE__, __LINE__,                  \
                              dbc::details::get_thread_id(), dbc::details::get_timestamp(), ""});

#define DBC_ASSERT2(type, condition, message)                                                      \
    if (!(condition))                                                                              \
        dbc::details::handle({type, #condition, __FUNCTION__, __FILE__, __LINE__,                  \
                              dbc::details::get_thread_id(), dbc::details::get_timestamp(),        \
                              message});

#else

#define DBC_ASSERT1(type, condition) (void(0))
#define DBC_ASSERT2(type, condition, message) (void(0))

#endif

#define DBC_INVARIANT1(condition) DBC_ASSERT1(dbc::contract_type::invariant, condition)
#define DBC_INVARIANT2(condition, message)                                                         \
    DBC_ASSERT2(dbc::contract_type::invariant, condition, message)

#define DBC_PRECONDITION1(condition) DBC_ASSERT1(dbc::contract_type::precondition, condition)
#define DBC_PRECONDITION2(condition, message)                                                      \
    DBC_ASSERT2(dbc::contract_type::precondition, condition, message)

#define DBC_POSTCONDITION1(condition) DBC_ASSERT1(dbc::contract_type::postcondition, condition)
#define DBC_POSTCONDITION2(condition, message)                                                     \
    DBC_ASSERT2(dbc::contract_type::postcondition, condition, message)

#ifndef NDEBUG

#define DBC_INVARIANT1_DBG(condition) DBC_INVARIANT1(condition)
#define DBC_INVARIANT2_DBG(condition, message) DBC_INVARIANT2(condition, message)

#define DBC_PRECONDITION1_DBG(condition) DBC_PRECONDITION1(condition)
#define DBC_PRECONDITION2_DBG(condition, message) DBC_PRECONDITION2(condition, message)

#define DBC_POSTCONDITION1_DBG(condition) DBC_POSTCONDITION1(condition)
#define DBC_POSTCONDITION2_DBG(condition, message) DBC_POSTCONDITION2(condition, message)

#else

#define DBC_INVARIANT1_DBG(condition) (void(0))
#define DBC_INVARIANT2_DBG(condition, message) (void(0))

#define DBC_PRECONDITION1_DBG(condition) (void(0))
#define DBC_PRECONDITION2_DBG(condition, message) (void(0))

#define DBC_POSTCONDITION1_DBG(condition) (void(0))
#define DBC_POSTCONDITION2_DBG(condition, message) (void(0))

#endif

} // namespace dbc

#define DBC_EXPAND(x) x                       // macro overloading via pre-processor magic
#define DBC_GET_MACRO(_1, _2, NAME, ...) NAME // macro overloading via pre-processor magic

#define INVARIANT(...)                                                                             \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_INVARIANT2, DBC_INVARIANT1)(__VA_ARGS__))

#define PRECONDITION(...)                                                                          \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_PRECONDITION2, DBC_PRECONDITION1)(__VA_ARGS__))

#define POSTCONDITION(...)                                                                         \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_POSTCONDITION2, DBC_POSTCONDITION1)(__VA_ARGS__))

#define INVARIANT_DBG(...)                                                                         \
    DBC_EXPAND(DBC_GET_MACRO(__VA_ARGS__, DBC_INVARIANT2_DBG, DBC_INVARIANT1_DBG)(__VA_ARGS__))

#define PRECONDITION_DBG(...)                                                                      \
    DBC_EXPAND(                                                                                    \
        DBC_GET_MACRO(__VA_ARGS__, DBC_PRECONDITION2_DBG, DBC_PRECONDITION1_DBG)(__VA_ARGS__))

#define POSTCONDITION_DBG(...)                                                                     \
    DBC_EXPAND(                                                                                    \
        DBC_GET_MACRO(__VA_ARGS__, DBC_POSTCONDITION2_DBG, DBC_POSTCONDITION1_DBG)(__VA_ARGS__))

#endif // DBC_H
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
#include <iostream>    // for cerr, ostream
#include <stdexcept>   // for logic_error, invalid_argument
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
// Debug info concerning a contract violation aggregate.
//
struct violation_context
{
    contract_type type;
    std::string_view condition;
    std::string_view function;
    std::string_view file;
    int32_t line;
    std::size_t thread_id; // a unique id hash
    int64_t timestamp;     // in ms
    std::string_view message;

    constexpr auto operator==(const violation_context&) const -> bool = default;
    constexpr auto operator!=(const violation_context&) const -> bool = default;
};

// provide overload that takes advantage of the std::string_view's efficiency
inline auto operator<<(std::ostream& os, const violation_context& context) -> auto&
{
    return os << to_string_view(context.type) << " violation: (" << context.condition << "), "
              << "function: " << context.function << ", file: " << context.file
              << ", line: " << context.line << ", thread id: " << context.thread_id
              << ", timestamp (ms): " << context.timestamp << "." << '\n'
              << context.message;
}

namespace details
{
    inline auto thread_id() noexcept // this thread
    {
        using namespace std;

        return hash<thread::id>()(this_thread::get_id());
    }

    inline auto timestamp() // in ms
    {
        using namespace std::chrono;

        const auto until_now = system_clock::now().time_since_epoch(); // since the 90's
        return duration_cast<milliseconds>(until_now).count();
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
        std::cerr << c << '\n';
        assert(std::cerr.good());
        std::abort();
    }
} // namespace details

#define DBC_ASSERT(type, condition, message)                                                       \
    if (!(condition))                                                                              \
        dbc::details::abort_handler({type, #condition, __FUNCTION__, __FILE__, __LINE__,           \
                                     dbc::details::thread_id(), dbc::details::timestamp(),         \
                                     message});

#elif defined(DBC_TERMINATE)

#if defined(DBC_ABORT) || defined(DBC_THROW) || defined(DBC_CUSTOM)
#error Definition of multiple DBC flags
#endif

namespace details
{
    [[noreturn]] inline void terminate_handler(const violation_context& c)
    {
        std::cerr << c << '\n';
        assert(std::cerr.good());
        std::terminate();
    }
} // namespace details

#define DBC_ASSERT(type, condition, message)                                                       \
    if (!(condition))                                                                              \
        dbc::details::terminate_handler({type, #condition, __FUNCTION__, __FILE__, __LINE__,       \
                                         dbc::details::thread_id(), dbc::details::timestamp(),     \
                                         message});

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
    explicit contract_violation(const violation_context& context)
        : logic_error{"DBC contract violation"}, m_context{context}
    {}

    // context
    //
    // Returns relevant debug info concerning where/when the contract violation took place.
    //
    // E.g function, thread, line, etc
    //
    auto context() const -> const auto& { return m_context; };

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

#define DBC_ASSERT(type, condition, message)                                                       \
    if (!(condition))                                                                              \
        dbc::details::throw_handler({type, #condition, __FUNCTION__, __FILE__, __LINE__,           \
                                     dbc::details::thread_id(), dbc::details::timestamp(),         \
                                     message});

#elif defined(DBC_CUSTOM)

#if defined(DBC_ABORT) || defined(DBC_TERMINATE) || defined(DBC_THROW)
#error Definition of multiple DBC flags
#endif

using violation_handler = std::function<void(const violation_context&)>;

namespace details
{
    inline auto handler() -> auto&
    {
        static violation_handler h = [](const auto&) {}; // noop default handler
        return h;
    }

    inline void handle(const violation_context& context)
    {
        assert(handler());
        std::invoke(handler(), context);
        assert(handler());
    }
} // namespace details

inline void set_violation_handler(const violation_handler& f)
{
    assert(details::handler());
    if (!f) throw std::invalid_argument("empty violation handler");
    details::handler() = f;
    assert(details::handler());
}

#define DBC_ASSERT(type, condition, message)                                                       \
    if (!(condition))                                                                              \
        dbc::details::handle({type, #condition, __FUNCTION__, __FILE__, __LINE__,                  \
                              dbc::details::thread_id(), dbc::details::timestamp(), message});

#else

#define DBC_ASSERT(type, condition, message) (void(0))

#endif

#define DBC_INVARIANT2(condition, message)                                                         \
    DBC_ASSERT(dbc::contract_type::invariant, condition, message)
#define DBC_INVARIANT1(condition) DBC_INVARIANT2(condition, "")

#define DBC_PRECONDITION2(condition, message)                                                      \
    DBC_ASSERT(dbc::contract_type::precondition, condition, message)
#define DBC_PRECONDITION1(condition) DBC_PRECONDITION2(condition, "")

#define DBC_POSTCONDITION2(condition, message)                                                     \
    DBC_ASSERT(dbc::contract_type::postcondition, condition, message)
#define DBC_POSTCONDITION1(condition) DBC_POSTCONDITION2(condition, "")

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
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

#ifndef DBC_ERROR_REPORTING_H
#define DBC_ERROR_REPORTING_H

#include <cassert>
#include <iostream>
#include <string_view>

namespace dbc
{

/** @defgroup error_reporting Error Reporting
 *  @{
 */

/**
 * @brief A Design By Contract contract enumeration.
 *
 */
enum class contract
{
    precondition = 0,
    postcondition,
    invariant
};

/**
 * @brief Returns an std::string_view representation of a dbc::contract.
 *
 * @param type the contract
 *
 * @return an std::string_view representation of a dbc::contract, or an empty string literal if the
 * contract type is not enumerated to a dbc pre/post condition or invariant
 */
constexpr auto to_string_view(contract type) noexcept
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
struct violation_context // TODO add lhs and rhs operands and decompose
{
    contract type;
    std::string_view condition; // a boolean expression string_view representation, always false
    std::string_view function;
    std::string_view file;
    int32_t line;
    std::size_t thread_id; // hashed to a unique size_t
    int64_t timestamp;
    std::string_view message;

    constexpr auto operator==(const violation_context&) const noexcept -> bool = default;
    constexpr auto operator!=(const violation_context&) const noexcept -> bool = default;
};

/**
 * @brief Operator << overload for a dbc::violation_context.
 *
 * Example output:
 *
 * 'Invariant violation: (false), function: my_func, file: path/my_file.cpp, line: 10, thread id:
 * 2583751165195653633, timestamp (ms): 1649421780602.
 * Error message!'
 */
auto operator<<(std::ostream& os, const violation_context& context) -> std::ostream&;
// TODO Colors!

namespace details
{
    // Produces a violation context.
    auto make_context(contract type, std::string_view condition, std::string_view function,
                      std::string_view file, int32_t line, std::string_view message)
        -> violation_context;

} // namespace details

} // namespace dbc

// Utility macro to obtain __FUNCTION__, __FILE__ and __LINE__
#define DBC_GET_CONTEXT(type, condition, message)                                                  \
    dbc::details::make_context(type, #condition, __FUNCTION__, __FILE__, __LINE__, message)

/** @} */

#endif // DBC_ERROR_REPORTING_H
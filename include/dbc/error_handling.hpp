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

#ifndef DBC_ERROR_HANDLING_H
#define DBC_ERROR_HANDLING_H

#include "error_reporting.hpp"
#include <functional>
#include <stdexcept>

namespace dbc
{

/** @defgroup error_handling Error Handling
 *  @{
 */

/**
 * @brief A violation context, error handler, function alias.
 *
 */
using violation_handler = std::function<void(const violation_context&)>;

/**
 * @brief Sets the global violation error handler function.
 * Any reported contract violations will be handled from this function.
 *
 * @param handler the violation handler function
 */
void set_violation_handler(const violation_handler& handler);

/**
 * @brief A generic contract violation exception.
 * Encapsulates preconditions, postconditions and invariants violations.
 *
 */
class contract_violation : public std::logic_error
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
[[noreturn]] void abort_handler(const violation_context& context);

/**
 * @brief Handles a dbc::violation_context by throwing a dbc::contract_violation error.
 *
 * @param context the violation context to handle
 */
[[noreturn]] inline void throw_handler(const violation_context& context)
{
    throw contract_violation{context};
}

namespace details
{
    // Forwards the reported violation to the set violation handler.
    void handle(const violation_context& context);

} // namespace details

} // namespace dbc

/** @} */

#endif // DBC_ERROR_HANDLING_H
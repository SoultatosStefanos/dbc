/**
 * @file dbc_private.hpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

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

// log a violation context error message and terminate
[[noreturn]] inline void terminate(const violation_context& context) noexcept

{
    log_violation_message(context);
    std::terminate();
}

// log a violation context error message and abort
[[noreturn]] inline void abort(const violation_context& context) noexcept

{
    log_violation_message(context);
    std::abort();
}

// generic contract violation exception, covers pre/post condition plus
// invariant violations
class contract_violation : public std::logic_error {
public:
    contract_violation(const std::string& what_arg): std::logic_error(what_arg)
    {}
};

// simply abstracts a throw with a context error message
inline void raise(const violation_context& context)
{
    throw contract_violation(make_violation_message(context));
}

} // namespace dbc::details
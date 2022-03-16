/**
 * @file sample4.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a code sample that showcases how DBC can be configured to
 * make a call to std::terminate and take advantage of a terminate hook.
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#define DBC_TERMINATE 1

#include "dbc/dbc.hpp"
#include <string>

// showcase of DBC working with custom handlers.

void bar(const char* str)
{
    PRECONDITION(str != nullptr);
}

extern auto make_error_msg() -> std::string;
extern void log_error_to_file(const std::string& msg);

void handle_terminate()
{
    const auto msg = make_error_msg();
    log_error_to_file(msg);
}

auto main() -> int
{
    std::set_terminate(handle_terminate);

    bar("ok"); // ok
    bar(nullptr); // time to recover

    return 0;
}

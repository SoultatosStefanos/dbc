/**
 * @file sample4.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a code sample that makes use of the dbc library.
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "dbc/dbc.hpp"
#include <string>

#define DBC_TERMINATE 1

// showcase of DBC working with custom handlers.

void bar(const char* str)
{
    PRECONDITION(str != nullptr);
}

extern auto make_error_msg() -> std::string;
extern void log_error_to_file(const std::string& msg);
extern void recover();

void recover_gracefully()
{
    const auto msg = make_error_msg();
    log_error_to_file(msg);
    recover();
}

auto main() -> int
{
    std::set_terminate(recover_gracefully);

    bar("ok"); // ok
    bar(nullptr); // time to recover

    return 0;
}

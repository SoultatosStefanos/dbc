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

#define DBC_CUSTOM 1

#include "dbc/dbc.hpp"

namespace {

    auto make_encoded_error_message(const dbc::violation_context& context)
    {
        auto str = dbc::to_string(context); // this is provided
        // preprocessing perhaps
        return str;
    }

    extern void show_message(const std::string& msg);
    extern void save_remaining_data();
    [[noreturn]] extern void urgent_exit();

    void fatal_error(const dbc::violation_context& context)
    {
        const auto msg = make_encoded_error_message(context);
        show_message(msg);
        save_remaining_data();
        urgent_exit(); // if this wasn't called, the program would continue,
                       // resulting to (possibly) undefined behavior.
    }

} // namespace

auto main() -> int
{
    dbc::set_violation_handler(fatal_error); // configure handler here

    PRECONDITION(false); // this will make a call to the fatal_error function

    return 0;
}

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

#define DBC_THROW 1

#include "dbc/dbc.hpp"
#include <iostream>

// showcase of DBC working with defensive programming.

auto read_int(std::istream& in) -> int
{
    PRECONDITION(in.good(), "Invalid input stream!");

    auto i{ 0 };
    in >> i;

    POSTCONDITION(in.good());
    return i;
}

extern void reboot();
extern void log(const std::string& error);

void recover_gracefully(const std::string& error)
{
    log(error);
    reboot();
}

auto main() -> int
{
    try {
        const auto i = read_int(std::cin);
    } catch (const dbc::contract_violation& e) { // catch contract violation
        recover_gracefully(e.what());

        return EXIT_SUCCESS;
    } catch (...) {
        std::cerr << "Unexpected error!\n";

        return EXIT_FAILURE;
    }
    return 0;
}

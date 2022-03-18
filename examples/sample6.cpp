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

#define DBC_ABORT 1

#include "dbc/dbc.hpp"
#include <iostream>
#include <string>

class performance_critical_balanced_tree {
public:
    void foo(const std::string& cmd)
    {
        INVARIANT_DBG(is_balanced()); // O(nlog(n))
        PRECONDITION_DBG(cmd == valid_cmd(), "Found: " + cmd); // O(n)

        // impl

        POSTCONDITION_DBG(info() == valid_info(), "Found: " + info()); // O(n)
        INVARIANT_DBG(is_balanced(), "What??"); // O(nlog(n))
    }
private:
    auto is_balanced() const -> bool;
    auto info() const -> std::string;
    auto valid_cmd() const -> std::string;
    auto valid_info() const -> std::string;
};
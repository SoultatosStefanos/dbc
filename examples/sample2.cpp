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

#define DBC_ABORT 1

#include "dbc/dbc.hpp"

namespace
{

// Showcase of encapsulation with dbc.
// Class invariant: v must be positive.
class x
{
public:
    auto var() const -> int
    {
        INVARIANT(v > 0);
        return v;
    }

    void set_var(int _v)
    {
        INVARIANT(v > 0);
        PRECONDITION(_v > 0); // same as
        // for more debug info
        PRECONDITION(_v > 0, "found _v == " + std::to_string(var()));

        v = _v;

        POSTCONDITION(v == _v); // same as
        // for more  info
        POSTCONDITION(v == _v, "v is actually: " + std::to_string(var()));
        INVARIANT(v > 0);
    }

private:
    int v{2};
};

} // namespace
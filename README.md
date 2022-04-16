# A simple Design By Contract C++ framework


## Introduction

DBC is a simple, flexible, C++ library, that facilitates support for a defensive variation of the
Design By Contract framework, by making use of public assertion macros.

* DBC is **flexible**. Depending on the build option, (DBC_ASSERT_LEVEL_NONE, 
DBC_ASSERT_LEVEL_PRECONDITIONS, DBC_ASSERT_LEVEL_POSTCONDITIONS, DBC_ASSERT_LEVEL_INVARIANTS), 
client code can choose what types of contracts to evaluate. In addition, the error handling 
mechanism can be configured at runtime.

* DBC is **debug friendly**. It's assertions are overloaded, in order to provide
human friendly error messages. In addition, in case of a contract violation,
user friendly debug info, (including the file, function and much more) is
forwarded, plus it features boolean expression decomposition, in order to automatically output the
operands of a false boolean expression.

* DBC is **efficient**. It utilizes mostly std::string_view objects and primitive 
types for error reporting, while its assertions can be completely turned off.


## Usage at a glance

This example illustrates how the public dbc assertions can be used. It 
configures the dbc environment to emulate the assertion mechanism, by aborting
on debug builds and doing nothing on release builds.

~~~~~~~~~~cpp

#ifndef NDEBUG
#define DBC_ASSERT_LEVEL_INVARIANTS
#else
#define DBC_ASSERT_LEVEL_NONE
#endif

#include "dbc/dbc.hpp"
#include <string>

static auto flag{4};

extern auto running() -> bool;
extern void bar();

void foo(int x, int y)
{
    REQUIRE(x >= 0);
    REQUIRE(y == 0);

    flag = x + y;

    while (running())
    {
        INVARIANT(running());

        bar();

        INVARIANT(running());
    }

    ENSURE(flag >= 0);
}

int main() {
    dbc::set_violation_handler(dbc::abort_handler);
}

~~~~~~~~~~

More [examples](https://github.com/SoultatosStefanos/dbc/tree/master/examples) 
are available.


### Copyright and Licensing

```

MIT License

Copyright (c) 2021 SoultatosStefanos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

```

## Contributors

Soultatos Stefanos

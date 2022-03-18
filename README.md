# A simple Design By Contract C++ framework

## Introduction

DBC is a simple, flexible, header-only, C++ library, that facilitates support
for the Design By Contract framework, by making use of public assertion
macros.

* DBC is **small** and **simple to use**. It consists of a single header file.

* DBC is **flexible**. Depending on the build option, contract violations can 
abort, terminate, throw, or do nothing (default). In addition, DBC includes 
specific assertion macros that are enabled exclusively at debug builds, and can
be used for performance critical code.

* DBC is **debug friendly**. It's assertions are overloaded, in order to provide
human friendly error messages. In addition, in case of a contract violation,
user friendly debug info is forwarded or logged.

More details can be read [here](docs/assertions.md), [here](docs/classes.md),
[here](docs/flags.md) and [here](docs/samples.md).


## Usage at a glance

DBC can be as simple to use, as copying and pasting the header file found at: 
dbc/dbc.hpp to your project.

This example illustrates how the public dbc assertions can be used. It 
configures the dbc environment to emulate the assertion mechanism, by aborting
on debug builds and doing nothing on release builds.

~~~~~~~~~~cpp

#ifndef NDEBUG
#define DBC_ABORT 1
#endif

#include "dbc/dbc.hpp"

static auto flag{4};

extern auto running() -> bool;
extern void bar();

void foo(int x, int y)
{
    PRECONDITION(x >= 0);
    PRECONDITION(y == 0, "Found y: " << y);

    flag = x + y;

    while(running()) {
        INVARIANT(running());

        bar();

        INVARIANT(running());
    }

    POSTCONDITION(flag >= 0);
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

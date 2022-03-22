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

// notice no #define here

#ifdef DBC_ABORT
#undef DBC_ABORT
#endif

#ifdef DBC_THROW
#undef DBC_THROW
#endif

#ifdef DBC_TERMINATE
#undef DBC_TERMINATE
#endif

#include "dbc/dbc.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace dbc::tests
{
    TEST(Invariants, Will_not_terminate_or_abort)
    {
        INVARIANT(true);
        INVARIANT(true, "Error message");
        INVARIANT(false);
        INVARIANT(false, "Error message");
    }

    TEST(Invariants, Will_not_throw)
    {
        ASSERT_NO_THROW(INVARIANT(true));
        ASSERT_NO_THROW(INVARIANT(true, ""));
        ASSERT_NO_THROW(INVARIANT(false));
        ASSERT_NO_THROW(INVARIANT(false, ""));
    }

    TEST(Preconditions, Will_not_terminate_or_abort)
    {
        PRECONDITION(true);
        PRECONDITION(true, "Error message");
        PRECONDITION(false);
        PRECONDITION(false, "Error message");
    }

    TEST(Preconditions, Will_not_throw)
    {
        ASSERT_NO_THROW(PRECONDITION(true));
        ASSERT_NO_THROW(PRECONDITION(true, ""));
        ASSERT_NO_THROW(PRECONDITION(false));
        ASSERT_NO_THROW(PRECONDITION(false, ""));
    }

    TEST(Postconditions, Will_not_terminate_or_abort)
    {
        POSTCONDITION(true);
        POSTCONDITION(true, "Error message");
        POSTCONDITION(false);
        POSTCONDITION(false, "Error message");
    }

    TEST(Postconditions, Will_not_throw)
    {
        ASSERT_NO_THROW(POSTCONDITION(true));
        ASSERT_NO_THROW(POSTCONDITION(true, ""));
        ASSERT_NO_THROW(POSTCONDITION(false));
        ASSERT_NO_THROW(POSTCONDITION(false, ""));
    }
} // namespace dbc::tests

auto main(int argc, char* argv[]) -> int
{
    try {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::InitGoogleMock(&argc, argv);

        return RUN_ALL_TESTS();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';

        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unexpected error!\n";

        return EXIT_FAILURE;
    }
}
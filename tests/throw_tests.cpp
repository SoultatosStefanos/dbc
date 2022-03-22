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
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace dbc::tests {

    TEST(Invariants, Will_not_throw_if_true)
    {
        EXPECT_NO_THROW(INVARIANT(true));
        EXPECT_NO_THROW(INVARIANT(true, "Error message"));
    }

    TEST(Invariants, Will_throw_a_contract_violation_if_false)
    {
        EXPECT_THROW(INVARIANT(false), dbc::contract_violation);
        EXPECT_THROW(INVARIANT(false, "Error!"), dbc::contract_violation);
    }

    TEST(Preconditions, Will_not_throw_if_true)
    {
        EXPECT_NO_THROW(PRECONDITION(true));
        EXPECT_NO_THROW(PRECONDITION(true, "Error message"));
    }

    TEST(Preconditions, Will_throw_a_contract_violation_if_false)
    {
        EXPECT_THROW(PRECONDITION(false), dbc::contract_violation);
        EXPECT_THROW(PRECONDITION(false, "Error!"), dbc::contract_violation);
    }

    TEST(Postconditions, Will_not_throw_if_true)
    {
        EXPECT_NO_THROW(POSTCONDITION(true));
        EXPECT_NO_THROW(POSTCONDITION(true, "Error message"));
    }

    TEST(Postconditions, Will_throw_a_contract_violation_if_false)
    {
        EXPECT_THROW(POSTCONDITION(false), dbc::contract_violation);
        EXPECT_THROW(POSTCONDITION(false, "Error!"), dbc::contract_violation);
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
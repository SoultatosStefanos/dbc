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

#define DBC_ASSERT_LEVEL_INVARIANTS

#include "dbc/dbc.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace
{

class Given_a_set_handler : public testing::Test
{
protected:
    void SetUp() override { dbc::set_violation_handler(handler.AsStdFunction()); }
    void TearDown() override { dbc::set_violation_handler(noop); }

    using mock_handler = testing::NiceMock<testing::MockFunction<dbc::violation_handler>>;

    mock_handler handler;
    dbc::violation_handler noop;
};

TEST_F(Given_a_set_handler, Precondition_asserts_dont_call_the_handler_if_true)
{
    EXPECT_CALL(handler, Call(testing::_)).Times(0);

    DBC_REQUIRE(true);
}

TEST_F(Given_a_set_handler, Precondition_asserts_call_the_handler_if_false)
{
    EXPECT_CALL(handler, Call(testing::_)).Times(1);

    DBC_REQUIRE(false);
}

TEST_F(Given_a_set_handler, Postcondition_asserts_dont_call_the_handler_if_true)
{
    EXPECT_CALL(handler, Call(testing::_)).Times(0);

    DBC_ENSURE(true);
}

TEST_F(Given_a_set_handler, Postcondition_asserts_call_the_handler_if_false)
{
    EXPECT_CALL(handler, Call(testing::_)).Times(1);

    DBC_ENSURE(false);
}

TEST_F(Given_a_set_handler, Invariant_asserts_dont_call_the_handler_if_true)
{
    EXPECT_CALL(handler, Call(testing::_)).Times(0);

    DBC_INVARIANT(true);
}

TEST_F(Given_a_set_handler, Invariant_asserts_call_the_handler_if_false)
{
    EXPECT_CALL(handler, Call(testing::_)).Times(1);

    DBC_INVARIANT(false);
}

} // namespace

auto main(int argc, char* argv[]) -> int
{
    try
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::InitGoogleMock(&argc, argv);

        return RUN_ALL_TESTS();
    } catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';

        return EXIT_FAILURE;
    } catch (...)
    {
        std::cerr << "Unexpected error!\n";

        return EXIT_FAILURE;
    }
}
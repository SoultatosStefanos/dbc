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

#define DBC_CUSTOM 1

#include "dbc/dbc.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace dbc::tests
{

class Given_a_set_handler : public testing::Test
{
protected:
    void SetUp() override { dbc::set_violation_handler(mock.AsStdFunction()); }

    void TearDown() override
    {
        dbc::set_violation_handler([](const auto&) {}); // reset
    }

    testing::NiceMock<testing::MockFunction<violation_handler>> mock;
};

#ifdef NDEBUG // Release build test cases

TEST_F(Given_a_set_handler, On_release_a_debug_invariant_will_never_call_the_handler)
{
    EXPECT_CALL(mock, Call(testing::_)).Times(0);

    INVARIANT_DBG(false);
    INVARIANT_DBG(false, "seriously");
}

TEST_F(Given_a_set_handler, On_release_a_debug_precondition_will_never_call_the_handler)
{
    EXPECT_CALL(mock, Call(testing::_)).Times(0);

    PRECONDITION_DBG(false);
    PRECONDITION_DBG(false, "seriously");
}

TEST_F(Given_a_set_handler, On_release_a_debug_postcondition_will_never_call_the_handler)
{
    EXPECT_CALL(mock, Call(testing::_)).Times(0);

    POSTCONDITION_DBG(false);
    POSTCONDITION_DBG(false, "seriously");
}

class Given_a_predicate_on_release : public testing::Test
{
protected:
    testing::NiceMock<testing::MockFunction<bool()>> mock;
};

TEST_F(Given_a_predicate_on_release, A_debug_only_invariant_will_not_call_the_predicate)
{
    EXPECT_CALL(mock, Call()).Times(0);

    INVARIANT_DBG(mock()); // since this will inline to void(0) (noop)
}

TEST_F(Given_a_predicate_on_release, A_debug_only_precondition_will_not_call_the_predicate)
{
    EXPECT_CALL(mock, Call()).Times(0);

    PRECONDITION_DBG(mock()); // since this will inline to void(0) (noop)
}

TEST_F(Given_a_predicate_on_release, A_debug_only_postcondition_will_not_call_the_predicate)
{
    EXPECT_CALL(mock, Call()).Times(0);

    POSTCONDITION_DBG(mock()); // since this will inline to void(0) (noop)
}

#else // Debug build test cases

TEST_F(Given_a_set_handler,
       On_debug_a_debug_invariant_will_call_the_handler_given_a_false_condition)
{
    EXPECT_CALL(mock, Call(testing::_)).Times(1);

    INVARIANT_DBG(false);
}

TEST_F(Given_a_set_handler,
       On_debug_a_debug_invariant_will_not_call_the_handler_given_a_true_condition)
{
    EXPECT_CALL(mock, Call(testing::_)).Times(0);

    INVARIANT_DBG(true);
}

TEST_F(Given_a_set_handler,
       On_debug_a_debug_precondition_will_call_the_handler_given_a_false_condition)
{
    EXPECT_CALL(mock, Call(testing::_)).Times(1);

    PRECONDITION_DBG(false);
}

TEST_F(Given_a_set_handler,
       On_debug_a_debug_precondition_will_not_call_the_handler_given_a_true_condition)
{
    EXPECT_CALL(mock, Call(testing::_)).Times(0);

    PRECONDITION_DBG(true);
}

TEST_F(Given_a_set_handler,
       On_debug_a_debug_postcondition_will_call_the_handler_given_a_false_condition)
{
    EXPECT_CALL(mock, Call(testing::_)).Times(1);

    POSTCONDITION_DBG(false);
}

TEST_F(Given_a_set_handler,
       On_debug_a_debug_postcondition_will_not_call_the_handler_given_a_true_condition)
{
    EXPECT_CALL(mock, Call(testing::_)).Times(0);

    POSTCONDITION_DBG(true);
}

#endif

} // namespace dbc::tests

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
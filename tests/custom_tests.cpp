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
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <cassert>

namespace dbc::tests {

    TEST(Set_violation_handler,
         Throws_an_invalid_argument_if_the_handler_is_empty)
    {
        dbc::violation_handler h;
        assert(!h);

        ASSERT_THROW(dbc::set_violation_handler(h), std::invalid_argument);
    }

    class Given_a_set_custom_violation_handler : public testing::Test {
    public:
        void SetUp() override
        {
            dbc::set_violation_handler(mock_handler.AsStdFunction());
        }

        void TearDown() override
        {
            dbc::set_violation_handler([](const auto&) {});
        }

    protected:
        testing::NiceMock<testing::MockFunction<violation_handler>>
            mock_handler;
    };

    TEST_F(Given_a_set_custom_violation_handler,
           A_true_invariant_assertion_will_not_call_the_handler)
    {
        EXPECT_CALL(mock_handler, Call(testing::_)).Times(0);

        INVARIANT(true);
    }

    TEST_F(Given_a_set_custom_violation_handler,
           A_true_precondition_assertion_will_not_call_the_handler)
    {
        EXPECT_CALL(mock_handler, Call(testing::_)).Times(0);

        PRECONDITION(true);
    }

    TEST_F(Given_a_set_custom_violation_handler,
           A_true_postcondition_assertion_will_not_call_the_handler)
    {
        EXPECT_CALL(mock_handler, Call(testing::_)).Times(0);

        POSTCONDITION(true);
    }

    TEST_F(Given_a_set_custom_violation_handler,
           A_false_invariant_assertion_will_call_the_handler)
    {
        EXPECT_CALL(mock_handler, Call(testing::_)).Times(1);

        INVARIANT(false);
    }

    TEST_F(Given_a_set_custom_violation_handler,
           A_false_precondition_assertion_will_call_the_handler)
    {
        EXPECT_CALL(mock_handler, Call(testing::_)).Times(1);

        PRECONDITION(false);
    }

    TEST_F(Given_a_set_custom_violation_handler,
           A_false_postcondition_assertion_will_call_the_handler)
    {
        EXPECT_CALL(mock_handler, Call(testing::_)).Times(1);

        POSTCONDITION(false);
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
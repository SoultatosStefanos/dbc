/**
 * @file terminate_tests.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains test cases that validate the dbc assertions behavior when the
 * DBC_TERMINATE macro is defined.
 * @version 0.1
 * @date 2022-03-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#define DBC_TERMINATE 1

#include "dbc/dbc.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace dbc::tests {

TEST(Invariants, Will_not_terminate_if_true)
{
    INVARIANT(true);
    INVARIANT(true, "Error message");
}

TEST(Invariants, Will_terminate_if_false)
{
    EXPECT_DEATH(INVARIANT(false), "");
    EXPECT_DEATH(INVARIANT(false, "Error message"), "");
}

TEST(Preconditions, Will_not_terminate_if_true)
{
    PRECONDITION(true);
    PRECONDITION(true, "Error message");
}

TEST(Preconditions, Will_terminate_if_false)
{
    EXPECT_DEATH(PRECONDITION(false), "");
    EXPECT_DEATH(PRECONDITION(false, "Error message"), "");
}

TEST(Postconditions, Will_not_terminate_if_true)
{
    POSTCONDITION(true);
    POSTCONDITION(true, "Error message");
}

TEST(Postconditions, Will_terminate_if_false)
{
    EXPECT_DEATH(POSTCONDITION(false), "");
    EXPECT_DEATH(POSTCONDITION(false, "Error message"), "");
}

} // namespace dbc::tests

auto main(int argc, char* argv[]) -> int
{
    try {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::InitGoogleMock(&argc, argv);

        return RUN_ALL_TESTS();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';

        return EXIT_FAILURE;
    }
    catch(...) {
        std::cerr << "Unexpected error!\n";

        return EXIT_FAILURE;
    }
}
/**
 * @file throw_tests.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains test cases that validate the dbc assertions behavior when the
 * DBC_THROW macro is defined.
 * @version 0.1
 * @date 2022-03-14
 *
 * @copyright Copyright (c) 2022
 *
 */
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
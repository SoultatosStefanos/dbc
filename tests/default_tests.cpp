/**
 * @file default_tests.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains test cases that validate the dbc assertions behavior when no
 * macro is defined.
 * @version 0.1
 * @date 2022-03-14
 *
 * @copyright Copyright (c) 2022
 *
 */

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

namespace dbc::tests {

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
    PRECONDITION(INVARIANT(true));
    PRECONDITION(INVARIANT(true, ""));
    PRECONDITION(INVARIANT(false));
    PRECONDITION(INVARIANT(false, ""));
}

TEST(POSTCONDITION, Will_not_terminate_or_abort)
{
    POSTCONDITION(true);
    POSTCONDITION(true, "Error message");
    POSTCONDITION(false);
    POSTCONDITION(false, "Error message");
}

TEST(POSTCONDITION, Will_not_throw)
{
    POSTCONDITION(INVARIANT(true));
    POSTCONDITION(INVARIANT(true, ""));
    POSTCONDITION(INVARIANT(false));
    POSTCONDITION(INVARIANT(false, ""));
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
/**
 * @file sample1.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a code sample that emulates the assertion mechanism, while
 * showcasing a simple use case of a function defining a pre and post condition.
 * @version 2.0
 * @date 2021-10-29
 *
 * @copyright Copyright (c) 2021
 *
 */

#define DBC_ABORT 1

#include "dbc/dbc.hpp"

namespace {

//
// Precondition: the integers are non negative
// Postcondition: the returned value is non negative
//
int sum_non_negative(int a, int b)
{
    PRECONDITION(a >= 0 and b >= 0);
    auto sum = a + b;
    POSTCONDITION(sum >= 0);
    return sum;
}

} // namespace
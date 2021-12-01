/**
 * @file sample1.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a code sample that makes use of the dbc library.
 * @version 2.0
 * @date 2021-10-29
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "dbc/dbc.hpp"

namespace {

//
// Precondition: the integers are non negative
// Postcondition: the returned value is non negative
//
int sum_non_negative_ints(const int a, const int b)
{
    Dbc::require(a >= 0 && b >= 0); // precondition
    auto sum = a + b;
    Dbc::ensure(sum >= 0); // postcondition
    return sum;
}

} // namespace
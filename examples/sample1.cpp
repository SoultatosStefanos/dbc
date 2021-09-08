/**
 * @file sample1.cpp
 * @author stef (stefanoss1498@gmail.com)
 * @brief Contains a code sample that makes use of the dbc library.
 * @version 0.1
 * @date 2021-09-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "dbc/dbc.h"

namespace
{

//
// Precondition: the integers are non negative
// Postcondition: the returned value is non negative
//
int
sum_non_negative_ints (const int a, const int b)
{
  dbc::require (a >= 0 && b >= 0); // precondition
  auto sum = a + b;
  dbc::ensure (sum >= 0); // postcondition
  return sum;
}

}
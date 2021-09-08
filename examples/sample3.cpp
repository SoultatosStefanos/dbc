/**
 * @file sample3.cpp
 * @author stef (stefanoss1498@gmail.com)
 * @brief Contains a code sample that makes use of the dbc library.
 * @version 0.1
 * @date 2021-09-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "dbc/dbc.h"
#include <array>

namespace
{

//
// Showcase of the loop invariant mechanism.
//
//
void
dostuff_with_ordered_array (std::array<int, 5> ordered)
{

  auto i = 1;
  while (i != 5)
    {
      dbc::invariant (ordered[i] > ordered[i - 1]); // loop invariant
      // do stuff
      dbc::invariant (ordered[i] > ordered[i - 1]); // loop invariant
    }
}

}
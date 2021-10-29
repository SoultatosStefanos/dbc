/**
 * @file sample3.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a code sample that makes use of the dbc library.
 * @version 2.0
 * @date 2021-10-29
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "dbc/dbc.hpp"
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
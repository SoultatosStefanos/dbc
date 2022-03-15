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

#define DBC_TERMINATE 1

namespace {

//
// Showcase of a loop invariant.
//
//
void dostuff_with_ordered_array(std::array<int, 5> ordered)
{
    for(auto i = 1; i < 5; ++i) {
        INVARIANT(ordered[i] > ordered[i - 1]);
        // do stuff
        // ....
        INVARIANT(ordered[i] > ordered[i - 1]);
    }
}

} // namespace
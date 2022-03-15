/**
 * @file sample7.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a code sample that showcases how to emulate the assertion
 * mechanism with DBC, without resolving the debug version of the assertions.
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef NDEBUG
#define DBC_ABORT 1 // abort on debug builds, else do nothing
#endif

#include "dbc/dbc.hpp"
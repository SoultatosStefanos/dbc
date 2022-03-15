/**
 * @file sample8.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a code sample that showcases how to essentially assert on
 * debug builds and throw on release builds.
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifdef NDEBUG
#define DBC_THROW 1 // throw on release
#else
#define DBC_ABORT 1 // abort on debug
#endif

#include "dbc/dbc.hpp"
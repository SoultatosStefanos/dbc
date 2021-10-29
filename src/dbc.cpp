/**
 * @file dbc.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains an implementation for the dbc library.
 * @version 2.0
 * @date 2021-10-29
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "dbc/dbc.hpp"

namespace dbc
{

void
invariant (bool expression, const std::string &what_arg)
{
  if (!expression)
    throw invariant_violation (what_arg);
}

void
require (bool expression, const std::string &what_arg)
{
  if (!expression)
    throw precondition_violation (what_arg);
}

void
ensure (bool expression, const std::string &what_arg)
{
  if (!expression)
    throw postcondition_violation (what_arg);
}

}
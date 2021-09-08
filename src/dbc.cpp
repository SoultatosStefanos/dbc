/**
 * @file dbc.cpp
 * @author stef (stefanoss1498@gmail.com)
 * @brief Contains an implementation for the dbc library.
 * @version 0.1
 * @date 2021-09-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "dbc/dbc.h"
#include <stdexcept>

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

}
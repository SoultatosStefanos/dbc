/**
 * @file dbc.hpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Distributes public functions that facilitate a simple design by
 * contract support through the std::logic_error exception hierarchy.
 * @version 2.0
 * @date 2021-10-29
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include "invariant_violation.hpp"
#include "postcondition_violation.hpp"
#include "precondition_violation.hpp"
#include <string>

namespace dbc
{

/**
 * @brief Throws a dbc::invariant_violation if the boolean expression is false
 *
 * @param expression the boolean expression
 * @param what_arg an explanatory error message
 */
void invariant (bool expression, const std::string &what_arg = "");
/**
 * @brief Throws a dbc::precondition_violation if the boolean expression is
 * false.
 *
 * @param expression the boolean expression
 * @param what_arg an explanatory error message
 */
void require (bool expression, const std::string &what_arg = "");
/**
 * @brief Throws a dbc::postcondition_violation if the boolean expression is
 * false/
 *
 * @param expression the boolean expression
 * @param what_arg an explanatory error message
 */
void ensure (bool expression, const std::string &what_arg = "");

}
/**
 * @file dbc.h
 * @author stef (stefanoss1498@gmail.com)
 * @brief Distributes public functions that facilitate a simple design by
 * contract support through the std::logic_error exception hierarchy.
 * @version 0.2
 * @date 2021-09-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef DBC_H
#define DBC_H

#include <string>

namespace dbc
{

/**
 * @brief Validates a class invariant which is abstracted with a boolean
 * expression.
 * Raises a dbc::invariant_violation if the boolean expression is false
 *
 * @param expression the boolean expression that abstracts the class invariant
 * @param what_arg an explanatory error message
 *
 * @throws dbc::invariant_violation if the boolean expression is false
 */
void invariant (bool expression, const std::string &what_arg = "");

/**
 * @brief Validates a function precondition which is abstracted with a boolean
 * expression.
 * Raises a dbc::precondition_violation if the boolean expression is false
 *
 * @param expression the boolean expression that abstracts the function
 * precondition
 * @param what_arg an explanatory error message
 *
 * @throws dbc::precondition_violation if the boolean expression is false
 */
void require (bool expression, const std::string &what_arg = "");

/**
 * @brief Validates a function postcondition which is abstracted with a boolean
 * expression.
 * Raises a dbc::postcondition_violation if the boolean expression is false
 *
 * @param expression the boolean expression that abstracts the function
 * postcondition
 * @param what_arg an explanatory error message
 *
 * @throws dbc::postcondition_violation if the boolean expression is false
 */
void ensure (bool expression, const std::string &what_arg = "");

}

#endif

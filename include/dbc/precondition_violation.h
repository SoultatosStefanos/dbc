/**
 * @file precondition_violation.h
 * @author stef (stefanoss1498@gmail.com)
 * @brief Contains a concrete precondition violation error.
 * @version 0.1
 * @date 2021-09-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef PRECONDITION_VIOLATION_H
#define PRECONDITION_VIOLATION_H

#include "contract_violation.h"

namespace dbc
{

/**
 * @brief This class provides a concrete precondition contract violation.
 *
 */
class precondition_violation : public contract_violation
{
public:
  /**
   * @brief Construct a new precondition_violation object.
   *
   * @param what_arg an explanatory string
   */
  precondition_violation (const std::string &what_arg)
      : contract_violation (what_arg)
  {
  }
  /**
   * @brief Construct a new precondition_violation object by deep copying
   * another object.
   *
   * @param other the other precondition_violation object
   */
  precondition_violation (
      const precondition_violation &other) noexcept = default;
  /**
   * @brief Destroys the precondition_violation object.
   *
   */
  ~precondition_violation () = default;
};

}

#endif

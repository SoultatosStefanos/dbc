/**
 * @file postcondition_violation.h
 * @author stef (stefanoss1498@gmail.com)
 * @brief Contains a concrete postcondition violation error.
 * @version 0.1
 * @date 2021-09-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef POSTCONDITION_VIOLATION_H
#define POSTCONDITION_VIOLATION_H

#include "contract_violation.h"

namespace dbc
{

/**
 * @brief This class provides a concrete postcondition contract violation.
 *
 */
class postcondition_violation : public contract_violation
{
public:
  /**
   * @brief Construct a new postcondition_violation object.
   *
   * @param what_arg an explanatory string
   */
  postcondition_violation (const std::string &what_arg)
      : contract_violation (what_arg)
  {
  }
  /**
   * @brief Construct a new postcondition_violation object by deep copying
   * another object.
   *
   * @param other the other postcondition_violation object
   */
  postcondition_violation (
      const postcondition_violation &other) noexcept = default;
  /**
   * @brief Destroys the postcondition_violation object.
   *
   */
  ~postcondition_violation () = default;
};

}

#endif

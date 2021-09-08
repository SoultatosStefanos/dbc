/**
 * @file invariant_violation.h
 * @author stef (stefanoss1498@gmail.com)
 * @brief Contains a concrete invariant violation error.
 * @version 0.1
 * @date 2021-09-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef INVARIANT_VIOLATION_H
#define INVARIANT_VIOLATION_H

#include "contract_violation.h"

namespace dbc
{
/**
 * @brief This class provides a concrete invariant contract violation.
 *
 */
class invariant_violation : public contract_violation
{
public:
  /**
   * @brief Construct a new invariant_violation object.
   *
   * @param what_arg an explanatory string
   */
  invariant_violation (const std::string &what_arg)
      : contract_violation (what_arg)
  {
  }
  /**
   * @brief Construct a new invariant_violation object by deep copying another
   * object.
   *
   * @param other the other invariant_violation object
   */
  invariant_violation (const invariant_violation &other) noexcept = default;
  /**
   * @brief Destroys the contract_violation object.
   *
   */
  ~invariant_violation () = default;
};

}

#endif

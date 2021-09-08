/**
 * @file contract_violation.h
 * @author stef (stefanoss1498@gmail.com)
 * @brief Contains an abstract contract violation error.
 * @version 0.1
 * @date 2021-09-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef CONTRACT_VIOLATION_H
#define CONTRACT_VIOLATION_H

#include <stdexcept>

namespace dbc
{
/**
 * @brief This class provides an abstract std::logic_error exception for design
 * by contract violations.
 *
 */
class contract_violation : public std::logic_error
{
public:
  /**
   * @brief Construct a new contract_violation object.
   *
   * @param what_arg an explanatory string
   */
  contract_violation (const std::string &what_arg) : std::logic_error (what_arg)
  {
  }
  /**
   * @brief Construct a new contract_violation object by deep copying another
   * object.
   *
   * @param other the other contract_violation object
   */
  contract_violation (const contract_violation &other) noexcept = default;
  /**
   * @brief Destroys the contract_violation object.
   *
   */
  virtual ~contract_violation () = default;
};

}

#endif

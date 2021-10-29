/**
 * @file precondition_violation.hpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a concrete precondition violation error.
 * @version 2.0
 * @date 2021-10-29
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include "contract_violation.hpp"

namespace dbc
{

/**
 * @brief This class provides a concrete precondition contract violation.
 *
 */
class precondition_violation : public contract_violation
{
public:
  precondition_violation (const std::string &what_arg)
      : contract_violation (what_arg)
  {
  }
  precondition_violation (const precondition_violation &) = default;
  precondition_violation (precondition_violation &&) = default;
  ~precondition_violation () override = default;

  auto operator= (const precondition_violation &)
      -> precondition_violation & = default;

  auto operator= (precondition_violation &&)
      -> precondition_violation & = default;
};

}
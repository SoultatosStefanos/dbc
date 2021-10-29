/**
 * @file postcondition_violation.hpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a concrete postcondition violation error.
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
 * @brief This class provides a concrete postcondition contract violation.
 *
 */
class postcondition_violation : public contract_violation
{
public:
  postcondition_violation (const std::string &what_arg)
      : contract_violation (what_arg)
  {
  }
  postcondition_violation (const postcondition_violation &) = default;
  postcondition_violation (postcondition_violation &&) = default;
  ~postcondition_violation () override = default;

  auto operator= (const postcondition_violation &)
      -> postcondition_violation & = default;

  auto operator= (postcondition_violation &&)
      -> postcondition_violation & = default;
};

}
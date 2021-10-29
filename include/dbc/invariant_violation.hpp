/**
 * @file invariant_violation.hpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a concrete invariant violation error.
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
 * @brief This class provides a concrete invariant contract violation.
 *
 */
class invariant_violation : public contract_violation
{
public:
  invariant_violation (const std::string &what_arg)
      : contract_violation (what_arg)
  {
  }
  invariant_violation (const invariant_violation &) = default;
  invariant_violation (invariant_violation &&) = default;
  ~invariant_violation () override = default;

  auto operator= (const invariant_violation &)
      -> invariant_violation & = default;

  auto operator= (invariant_violation &&) -> invariant_violation & = default;
};

}
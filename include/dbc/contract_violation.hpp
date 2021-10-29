/**
 * @file contract_violation.hpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains an abstract contract violation error.
 * @version 2.0
 * @date 2021-10-29
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

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
  contract_violation (const std::string &what_arg) : std::logic_error (what_arg)
  {
  }
  contract_violation (const contract_violation &) = default;
  contract_violation (contract_violation &&) = default;
  virtual ~contract_violation () = default;

  auto operator= (const contract_violation &) -> contract_violation & = default;
  auto operator= (contract_violation &&) -> contract_violation & = default;
};

}

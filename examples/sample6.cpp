/**
 * @file sample6.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a code sample that showcases the debug only DBC assertions,
 * that can be used at performance critical operations.
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#define DBC_ABORT 1

#include "dbc/dbc.hpp"
#include <iostream>
#include <string>

class performance_critical_balanced_tree {
public:
    void foo(const std::string& cmd)
    {
        INVARIANT_DBG(is_balanced()); // O(nlog(n))
        PRECONDITION_DBG(cmd == valid_cmd(), "Found: " + cmd); // O(n)

        // impl

        POSTCONDITION_DBG(info() == valid_info(), "Found: " + info()); // O(n)
        INVARIANT_DBG(is_balanced(), "What??"); // O(nlog(n))
    }
private:
    auto is_balanced() const -> bool;
    auto info() const -> std::string;
    auto valid_cmd() const -> std::string;
    auto valid_info() const -> std::string;
};
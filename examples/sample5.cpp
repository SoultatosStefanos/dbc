/**
 * @file sample5.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a code sample that makes use of the dbc library.
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "dbc/dbc.hpp"
#include <iostream>

#define DBC_THROW 1

// showcase of DBC working with defensive programming.

auto read_int(std::istream& in) -> int
{
    PRECONDITION(in.good(), "Invalid input stream!");

    auto i{0};
    in >> i;

    POSTCONDITION(in.good());
    return i;
}

extern void reboot();
extern void log(const std::string& error);

auto main() -> int
{
    try {
        const auto i = read_int(std::cin);
    }
    catch(const dbc::contract_violation& e) { // catch contract violation
        log(e.what());
        reboot();

        return EXIT_FAILURE;
    }
    catch(...) {
        std::cerr << "Unexpected error!\n";

        return EXIT_FAILURE;
    }
    return 0;
}

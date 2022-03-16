/**
 * @file sample5.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a code sample that showcases catching DBC thrown contract
 * violations.
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#define DBC_THROW 1

#include "dbc/dbc.hpp"
#include <iostream>

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

void recover_gracefully(const std::string& error)
{
    log(error);
    reboot();
}

auto main() -> int
{
    try {
        const auto i = read_int(std::cin);
    }
    catch(const dbc::contract_violation& e) { // catch contract violation
        recover_gracefully(e.what());

        return EXIT_SUCCESS;
    }
    catch(...) {
        std::cerr << "Unexpected error!\n";

        return EXIT_FAILURE;
    }
    return 0;
}

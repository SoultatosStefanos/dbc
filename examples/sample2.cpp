/**
 * @file sample2.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a code sample that showcases class encapsulation with DBC.
 * In particular, the class invariant is showcased.
 * The build configuration, allows as to abort on debug builds, and throw on
 * release builds.
 * @version 2.0
 * @date 2021-10-29
 *
 * @copyright Copyright (c) 2021
 *
 */

#define DBC_ABORT 1

#include "dbc/dbc.hpp"

namespace {

// Showcase of encapsulation with dbc.
// Class invariant: v must be positive.
class x {
public:
    auto var() const -> int
    {
        INVARIANT(v > 0);
        return v;
    }

    void set_var(int _v)
    {
        INVARIANT(v > 0);
        PRECONDITION(_v > 0); // same as
        // for more debug info
        PRECONDITION(_v > 0, "found _v == " + std::to_string(var()));

        v = _v;

        POSTCONDITION(v == _v); // same as
        // for more  info
        POSTCONDITION(v == _v, "v is actually: " + std::to_string(var()));
        INVARIANT(v > 0);
    }
private:
    int v{2};
};

} // namespace
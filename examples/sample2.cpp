/**
 * @file sample2.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a code sample that makes use of the dbc library.
 * @version 2.0
 * @date 2021-10-29
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "dbc/dbc.hpp"

#ifdef NDEBUG // throw on release builts, abort on debug
#define DBC_THROW 1
#else
#define DBC_ABORT 1
#endif

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
        PRECONDITION(_v > 0, "found _v == " << var()); // for more debug info
        v = _v;
        POSTCONDITION(v == _v); // same as
        POSTCONDITION(v == _v, "v is actually: " << var()); // for more  info
        INVARIANT(v > 0);
    }
private:
    int v{2};
};

} // namespace
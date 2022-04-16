#ifndef DBC_EXPR_DECOMPOSITION_HPP
#define DBC_EXPR_DECOMPOSITION_HPP

#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <string_view>

namespace dbc
{

namespace details
{
    struct lhs_decomposer;

    // Decomposes a boolean expression, given its left hand side operand
    // Makes use of the operator overloads to deduce the right hand operand and the operation.
    template <typename T>
    class rhs_decomposer
    {
    public:
        explicit rhs_decomposer(const T& lhs) { ss << lhs; }

        auto operator==(const T& rhs) -> const auto&
        {
            ss << " == " << rhs;
            return *this;
        }

        auto operator!=(const T& rhs) -> const auto&
        {
            ss << " != " << rhs;
            return *this;
        }

        auto operator<(const T& rhs) -> const auto&
        {
            ss << " < " << rhs;
            return *this;
        }

        auto operator>(const T& rhs) -> const auto&
        {
            ss << " > " << rhs;
            return *this;
        }

        auto operator<=(const T& rhs) -> const auto&
        {
            ss << " <= " << rhs;
            return *this;
        }

        auto operator>=(const T& rhs) -> const auto&
        {
            ss << " >= " << rhs;
            return *this;
        }

        // Returns an std::string decomposition of the boolean expression, of the form:
        //"'lhs' 'operation' 'rhs'""
        auto decomposition() const -> auto { return ss.str(); }

    private:
        std::stringstream ss;
    };

    // Hepler struct, forwards a left hand side opperand to a right hand side decomposer
    struct lhs_decomposer
    {
        template <typename T>
        auto operator->*(const T& lhs) const -> auto
        {
            return rhs_decomposer<T>{lhs};
        }
    };
} // namespace details

} // namespace dbc

// Utility macro to obtain an std::string decomposition of a boolean expression
#define DBC_DECOMPOSE(expr)                                                                        \
    ([]() -> dbc::details::lhs_decomposer { return {}; }()->*expr).decomposition();

#endif // DBC_EXPR_DECOMPOSITION_HPP

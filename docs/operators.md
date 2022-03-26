# Operators Reference

This page lists the operator overloads provided by DBC. To use them, include the
header `dbc/dbc.h`.

### operator== {#operator==}

`constexpr auto operator==(const violation_context&) const -> bool = default`


### operator!= {#operator!=}

` constexpr auto operator!=(const violation_context&) const -> bool = default`


### operator<< {#operator<<}

`inline auto operator<<(std::ostream& os, const violation_context& context) -> auto&`
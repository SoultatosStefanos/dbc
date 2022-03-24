# Functions Reference

This page lists the free functions provided by DBC. To use them, include the
header `dbc/dbc.h`.


### to_string_view {#to_string_view}

`constexpr auto to_string_view(contract_type type)`

Returns an std::string_view representation of a contract_type.


### to_string {#to_string}

`inline auto to_string(const violation_context& context)`

Returns an std::string representation of a violation context.


### set_violation_handler {#set_violation_handler}

`inline void set_violation_handler(const violation_handler& f)`

Distributed when the DBC flag DBC_CUSTOM is set.

Sets a global violation handler function. Any failed DBC assertions will forward
the violation context information to this custom handler function.

Initially, before setting a custom handler, the default one performs a noop.
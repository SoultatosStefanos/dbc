# Build Flags Reference

This page lists the build flag macros provided by DBC for specifying contract 
the DBC assertions behavior. To use them, include the header `dbc/dbc.h`.

### DBC_ABORT {#DBC_ABORT}

When defined, any contract violations that are verified by the DBC macros will 
cause a core dump. In particular, all of the contract violation context info 
(file, line, function and expression) will be logged to the std::cerr stream, 
and a call to std::abort will be made.

### DBC_TERMINATE {#DBC_TERMINATE}

When defined, any contract violations that are verified by the DBC macros will 
cause a core dump. In particular, all of the contract violation context info 
(file, line, function and expression) will be logged to the std::cerr stream, 
and a call to std::terminate will be made.

### DBC_THROW {#DBC_THROW}

When defined, any contract violations that are verified by the DBC macros will 
throw a dbc::contract_violation exception. All of the contract violation context
info (file, line, function and expression) can be obtained through the 
dbc::contract_violation::what() method.
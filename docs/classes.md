# Classes Reference

This page lists the classes provided by DBC. To use them, include the header 
`dbc/dbc.h`.

### contract_type {#contract_type}

A Design By Contract contract type enumeration, consisting of a precondition,
a postcondition and an invariant.


### violation_context {#violation_context}

A set of useful information about the context where a contract violation took 
place. 

In particular, this structure contains: the type of the contract violation,
(precondition, postcondition, invariant), the boolean expression that failed,
the function, file, line, a hushed thread id and a timestamp (ms), where the violation took
place, and finally, an optional user error message.


### contract_violation {#contract_violation}

Distributed when the DBC flag DBC_THROW is set.

A derivative of the std::logic_error class. It encapsulates any contract 
violation errors that can be thrown when verifying invariants or pre/post 
conditions. 

Effectively used, when the DBC_THROW build flag macro is defined. 

In order to observe the contract violation context debug info (file, function, etc), the member 
function dbc::contract_violation::context() can be used.
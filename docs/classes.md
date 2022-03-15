# Classes Reference

This page lists the classes provided by DBC. To use them, include the header 
`dbc/dbc.h`.

### contract_violation {#contract_violation}

A derivative of the std::logic_error class. It encapsulates any contract 
violation errors that can be thrown when verifying invariants or pre/post 
conditions. 

Effectively used, when the DBC_THROW build flag macro is defined. 

In order to observe the contract violation context debug info 
(file, function, etc), the inherited, public, accessor method
dbc::contract_violation::what() can be used.
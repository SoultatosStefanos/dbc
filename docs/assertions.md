# Assertions Reference

This page lists the assertion macros provided by DBC for verifying code
behavior. To use them, include the header `dbc/dbc.h`.

All of the macros listed below come as a pair with an overloaded, with a custom
error message, variant. Upon failure, these assertion macros behavior varies 
depending on the DBC build flags.

### INVARIANT {#INVARIANT}

`INVARIANT(`*`condition`*`)` \
`INVARIANT(`*`condition`*`, `*`message`*`)`

Validates a class or loop invariant, abstracted through a boolean expression.

The optional message overload is used, inorder to forward an explanatory error
message to the std::cerr stream.

Class/loop invariants should be checked at the entry point of both accessor and
mutator methods, as well as at the exit point of the mutator methods/functions.

Invariants should not be weakened across an inheritance tree, but can be
strenghtened.

### PRECONDITION {#PRECONDITION}

`PRECONDITION(`*`condition`*`) ` \
`PRECONDITION(`*`condition`*`, `*`message`*`) `

Validates a function/method precondition, abstracted through a boolean
expression. 

The optional message overload is used, inorder to forward an explanatory error
message to the std::cerr stream.

Function/method preconditions should be checked at the entry point of both
accessor and mutator methods/functions.

Preconditions should not be strengthened across an inheritance tree, but can be
weakened. 

### POSTCONDITION {#POSTCONDITION}

`POSTCONDITION(`*`condition`*`) ` \
`POSTCONDITION(`*`condition`*`, `*`message`*`) `

Validates a function/method postcondition, abstracted through a boolean
expression. 

The optional message overload is used, inorder to forward an explanatory error
message to the std::cerr stream.

Function/method postconditions should be checked at the exit point of both
accessor and mutator methods/functions.

Postconditions should not be weakened across an inheritance tree, but can be
strengthened.

As a convention, functions/methods that return a non void type should store the
result to a variable before returning it, in order to ensure the postcondition. 


# Assertions Reference

This page lists the assertion macros provided by DBC for verifying code
behavior. To use them, include the header `dbc/dbc.h`.

All of the macros listed below come as a pair with an overloaded, with a custom
error message, variant. In addition, each assertion comes with a debug-only 
variant, that can be used at performance critical hot spots. Upon failure,
these assertion macros behavior varies depending on the DBC build flags.

### INVARIANT {#INVARIANT}

`INVARIANT(`*`condition`*`)` \
`INVARIANT(`*`condition`*`, `*`message`*`)`

Validates a class or loop invariant, abstracted through a boolean expression.

The optional message overload is used, inorder to forward an explanatory error
message to the std::cerr stream.

### INVARIANT_DBG {#INVARIANT_DBG}

`INVARIANT_DBG(`*`condition`*`)` \
`INVARIANT_DBG(`*`condition`*`, `*`message`*`)`

Validates a class or loop invariant, abstracted through a boolean expression.

The optional message overload is used, inorder to forward an explanatory error
message to the std::cerr stream.

This variant can be used in order to assert invariants for performance critical
code, thus it's disabled on release builds.

### PRECONDITION {#PRECONDITION}

`PRECONDITION(`*`condition`*`) ` \
`PRECONDITION(`*`condition`*`, `*`message`*`) `

Validates a function/method precondition, abstracted through a boolean
expression. 

The optional message overload is used, inorder to forward an explanatory error
message to the std::cerr stream.

### PRECONDITION_DBG {#PRECONDITION_DBG}

`PRECONDITION_DBG(`*`condition`*`) ` \
`PRECONDITION_DBG(`*`condition`*`, `*`message`*`) `

Validates a function/method precondition, abstracted through a boolean
expression. 

The optional message overload is used, inorder to forward an explanatory error
message to the std::cerr stream.

This variant can be used in order to assert preconditions for performance
critical code, thus it's disabled on release builds.

### POSTCONDITION {#POSTCONDITION}

`POSTCONDITION(`*`condition`*`) ` \
`POSTCONDITION(`*`condition`*`, `*`message`*`) `

Validates a function/method postcondition, abstracted through a boolean
expression. 

The optional message overload is used, inorder to forward an explanatory error
message to the std::cerr stream.

### POSTCONDITION_DBG {#POSTCONDITION_DBG}

`POSTCONDITION_DBG(`*`condition`*`) ` \
`POSTCONDITION_DBG(`*`condition`*`, `*`message`*`) `

Validates a function/method postcondition, abstracted through a boolean
expression. 

The optional message overload is used, inorder to forward an explanatory error
message to the std::cerr stream.

This variant can be used in order to assert postconditions for performance
critical code, thus it's disabled on release builds.


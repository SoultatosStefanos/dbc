# Assertions Reference

This page lists the assertion macros provided by DBC for verifying code
behavior. To use them, include the header `dbc/dbc.h`.

All of the macros listed below come as a pair with an overloaded, with a custom
error message, variant. In addition, each assertion comes with a debug-only 
variant, that can be used at performance critical hot spots, and a static variant, that makes a call
to static_assert.

### INVARIANT {#INVARIANT}

`INVARIANT(`*`condition`*`)` \
`INVARIANT(`*`condition`*`, `*`message`*`)`

Validates a class or loop invariant, abstracted through a boolean expression.

The optional message overload is used, in order to forward an explanatory error
message to the std::cerr stream.

### INVARIANT_DEBUG {#INVARIANT_DEBUG}

`INVARIANT_DEBUG(`*`condition`*`)` \
`INVARIANT_DEBUG(`*`condition`*`, `*`message`*`)`

Validates a class or loop invariant, abstracted through a boolean expression.

The optional message overload is used, in order to forward an explanatory error
message to the std::cerr stream.

This variant can be used in order to assert invariants for performance critical
code, thus it's disabled on release builds.

### INVARIANT_STATIC {#INVARIANT_STATIC}

`INVARIANT_STATIC(`*`condition`*`)` \
`INVARIANT_STATIC(`*`condition`*`, `*`message`*`)`

Validates a class or loop invariant, abstracted through a boolean expression.

This variant can be used in order to static_assert invariants.

### PRECONDITION {#PRECONDITION}

`PRECONDITION(`*`condition`*`) ` \
`PRECONDITION(`*`condition`*`, `*`message`*`) `

Validates a function/method precondition, abstracted through a boolean
expression. 

The optional message overload is used, in order to forward an explanatory error
message to the std::cerr stream.

### PRECONDITION_DEBUG {#PRECONDITION_DEBUG}

`PRECONDITION_DEBUG(`*`condition`*`) ` \
`PRECONDITION_DEBUG(`*`condition`*`, `*`message`*`) `

Validates a function/method precondition, abstracted through a boolean
expression. 

The optional message overload is used, in order to forward an explanatory error
message to the std::cerr stream.

This variant can be used in order to assert preconditions for performance
critical code, thus it's disabled on release builds.

### PRECONDITION_STATIC {#PRECONDITION_STATIC}

`PRECONDITION_STATIC(`*`condition`*`) ` \
`PRECONDITION_STATIC(`*`condition`*`, `*`message`*`) `

Validates a function/method precondition, abstracted through a boolean
expression. 

This variant can be used in order to static_assert preconditions.

### POSTCONDITION {#POSTCONDITION}

`POSTCONDITION(`*`condition`*`) ` \
`POSTCONDITION(`*`condition`*`, `*`message`*`) `

Validates a function/method postcondition, abstracted through a boolean
expression. 

The optional message overload is used, in order to forward an explanatory error
message to the std::cerr stream.

### POSTCONDITION_DEBUG {#POSTCONDITION_DEBUG}

`POSTCONDITION_DEBUG(`*`condition`*`) ` \
`POSTCONDITION_DEBUG(`*`condition`*`, `*`message`*`) `

Validates a function/method postcondition, abstracted through a boolean
expression. 

The optional message overload is used, in order to forward an explanatory error
message to the std::cerr stream.

This variant can be used in order to assert postconditions for performance
critical code, thus it's disabled on release builds.

### POSTCONDITION_STATIC {#POSTCONDITION_STATIC}

`POSTCONDITION_STATIC(`*`condition`*`) ` \
`POSTCONDITION_STATIC(`*`condition`*`, `*`message`*`) `

Validates a function/method postcondition, abstracted through a boolean
expression. 

This variant can be used in order to static_assert postconditions.

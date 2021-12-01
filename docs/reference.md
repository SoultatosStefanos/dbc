# Dbc Reference

This page lists the facilities provided by dbc, for making use of the Design By
Contract framework, at development time, through public macros.
To use them, include the header `dbc/dbc.h`


## Macros

Dbc defines the following macros.
<br /><br />

### INVARIANT {#INVARIANT}
<br />

`INVARIANT(condition) ` \
`INVARIANT(condition, message) `

Validates a class or loop invariant, abstracted through a boolean expression.
In particular, makes a call to std::terminate(), if the boolean
expression evaluates to false, and outputs the appropriate debug info to the 
std::cerr stream.

The optional message overload is used, inorder to forward an explanatory error
message to the std::cerr stream.

Class/loop invariants should be checked at the entry point of both accessor and
mutator methods, as well as at the exit point of the mutator methods/functions.

Invariants should not be weakened across an inheritance tree, but can be
strenghtened.<br /><br />


### PRECONDITION {#PRECONDITION}
<br />

`PRECONDITION(condition) ` \
`PRECONDITION(condition, message) `

Validates a function/method precondition, abstracted through a boolean
expression. In particular, makes a call to std::terminate(), if the boolean
expression evaluates to false, and outputs the appropriate debug info to the 
std::cerr stream.

The optional message overload is used, inorder to forward an explanatory error
message to the std::cerr stream.

Function/method preconditions should be checked at the entry point of both
accessor and mutator methods/functions.

Preconditions should not be strengthened across an inheritance tree, but can be
weakened.<br /><br />


### POSTCONDITION {#POSTCONDITION}
<br />

`POSTCONDITION(condition) ` \
`POSTCONDITION(condition, message) `

Validates a function/method postcondition, abstracted through a boolean
expression. In particular, makes a call to std::terminate(), if the boolean
expression evaluates to false, and outputs the appropriate debug info to the 
std::cerr stream.

The optional message overload is used, inorder to forward an explanatory error
message to the std::cerr stream.

Function/method postconditions should be checked at the exit point of both
accessor and mutator methods/functions.

Postconditions should not be weakened across an inheritance tree, but can be
strengthened.

As a convention, functions/methods that return a non void type should store the
result to a variable before returning it, in order to ensure the postcondition. 

E.g: 

<pre>
// Returns a non negative sum.
void
sum(const int a, const int b) 
{
  auto res = a + b;

  POSTCONDITION(res >= 0);
  return res;
}
</pre>

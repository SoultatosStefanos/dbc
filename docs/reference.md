# Dbc Reference

This page lists the facilities provided by dbc for making use of the Design By
Contract framework through the std::logic_error exception hierarchy.
To use them, include the header `dbc/dbc.h`


## Classes

Dbc defines the following classes.

### contract_violation {#contract_violation}

An std::logic_error abstract extension class that indicates a design by contract
violation error.

### invariant_violation {#invariant_violation}

A `contract_violation` concrete extension class that indicates a design by
contract invariant violation error.

### precondition_violation {#precondition_violation}

A `contract_violation` concrete extension class that indicates a design by
contract precondition violation error.

### postcondition_violation {#postcondition_violation}

A `contract_violation` concrete extension class that indicates a design by
contract postcondition violation error.

## Functions

Dbc defines the following functions.

### invariant {#invariant}

`void invariant (bool expression, const std::string &what_arg = "")`

Validates a class or loop invariant, abstracted through a boolean expression.
In particular, throws an `invariant_violation` exception if the boolean
expression evaluates to false.

The optional message parameter is used as an explanatory error message that is
passed to the thrown exception.

Class/loop invariants should be checked at the entry point of both accessor and
mutator methods, as well as at the exit point of the mutator methods/functions.

Invariants should not be weakened across an inheritance tree, but can be
strenghtened.

### require {#require}

`void require (bool expression, const std::string &what_arg = "")`

Validates a function/method precondition, abstracted through a boolean
expression. In particular, throws a `precondition_violation` exception if the
boolean expression evaluates to false.

The optional message parameter is used as an explanatory error message that is
passed to the thrown exception.

Function/method preconditions should be checked at the entry point of both
accessor and mutator methods/functions.

Preconditions should not be strengthened across an inheritance tree, but can be
weakened.

### ensure {#ensure}

`void ensure (bool expression, const std::string &what_arg = "")`

Validates a function/method postcondition, abstracted through a boolean
expression. In particular, throws a `postcondition_violation` exception if the
boolean expression evaluates to false.

The optional message parameter is used as an explanatory error message that is
passed to the thrown exception.

Function/method postconditions should be checked at the exit point of both
accessor and mutator methods/functions.

Postconditions should not be weakened across an inheritance tree, but can be
strengthened.

As a convention, functions/methods that return a non void type should store the
result to a variable before returning it, in order to ensure the postcondition.

<pre>
// Returns a non negative sum.
void
sum(const int a, const int b) 
{
  auto res = a + b;
  dbc::endure(res >= 0);
  return res;
}
</pre>
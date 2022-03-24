# DBC Samples

The examples directory has a number of well-commented samples showcasing
different use cases for a variety of DBC features.

See [dbc samples.](https://github.com/SoultatosStefanos/dbc/tree/master/examples)

*   Sample #1 shows a basic use case of a precondition and a postcondition.
*   Sample #2 shows how a class invariant can be protected with DBC.
*   Sample #3 shows a loop invariant verification use case.
*   Sample #4 shows how DBC can be used to take advantage of terminate hooks.
*   Sample #5 shows how DBC can be used to catch contract violations to recover
gracefully.
*   Sample #6 shows a performance critical use case where the debug-only 
assertions are used.
*   Sample #7 shows how DBC can be configured to emulate the assertion mechanism.
*   Sample #8 shows how DBC can be configured to abort on debug builds, but
throw on release builds.
*   Sample #9 shows how DBC can be configured in order to install a custom 
global contract violation handler function.
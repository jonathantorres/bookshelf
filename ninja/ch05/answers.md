## Functions for the master

#### Answer #1
Option a) "Access external variable that are in scope when the function is defined".
***

#### Answer #2
Option b) "Memory costs".
***

#### Answer #3
The identifiers are `weapon` and `name`.
***

#### Answer #4
4 execution contexts are created:
- The global context
- The `perform` context
- The `sneak` context
- The `infiltrate` context

The largest size of the execution context stack is 3 (Global->`perform`->`sneak`).
***

#### Answer #5
The `const` keyword.
***

#### Answer #6
`var` only creates variables that are function-scoped, `let` also allows us to create variables that are block-scoped (if statement, for loop etc. etc.).
***

#### Answer #7
In the call to `getSamurai` an exception is thrown, since it's a variable and not a function declaration. The `getSamurai` name is only available after is declared.
***

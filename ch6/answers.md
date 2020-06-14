## Answers to questions
1. If the numbers that we are using are ints, it would be `func sum(nums []int) int`
2. See `half`
3. See `biggest`
4. See `oddgen`
5. See `fib`
6. `defer` is to execute a function when the calling function finishes is perfectly used for "cleanup" functions (like closing a file when we are done with it etc. etc.), `panic` is a way to stop execution of a program and give a type as a parameter, `recover` is used to detect when the panic happens and act as desired on it in order to prevent the program from stopping, and handle the error gracefully
7. With the `&` character, for example `&myVar`
8. With the `*` character, for example `*myPointer = 10` if the pointer points to an int `*int`
9. With the `new` function, you must specifiy a type as the only parameter, this will allocate enough memory to store a value of that type and return a pointer to it, for example `var v *int = new(int)`. This will allocate memory to hold an `int` and `v` will have a pointer to the address where the memory was allocated for it
10. The value is `2.25`, is basically multiplying the number by itself
11. See `swap`

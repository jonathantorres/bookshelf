## Interlude: Process API

#### Answer #1
The child gets it's own copy of the variable, this means that changing the value in the parent does not affect the value of the variable on the child. See `1.c`.
***

#### Answer #2
Yes, both the child and the parent have their own copy of the file descriptor. One process writes to the file after the other, the writes to the file do not overlap. See `2.c`.
***

#### Answer #3
The only way that I can think of is by sleeping the parent for a second or two, this way the child finishes executing first. See `3.c`.
***

#### Answer #4
Probably to support the needs of different kinds of programs (shells, scripting etc. etc.) See `4.c`.
***

#### Answer #5
`wait` returns the id of the child process that just terminated. `wait` returns an error if called on a process that does not have any children. See `5.c`.
***

#### Answer #6
`waitpid` is useful when you want to wait for a specific child process or for all of the children of the process. See `6.c`.
***

#### Answer #7
`printf` still returns sucessfully, but the bytes are written to a buffer that is no longer attached to the terminal since the descriptor has been closed. See `7.c`.
***

#### Answer #8
See `8.c`.
***

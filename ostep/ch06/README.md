## Mechanism: Limited Direct Execution

#### Measuring a System Call
Running the benchmarks for a system call by calling `read` and reading 0 bytes a million times. It looks like the system call takes about 0.53029 microseconds. See `syscall.c`.

#### Measuring a Context Switch
Running the benchmarks for a context switch by calling `read` and `write` and reading/writing 0 bytes a million times on two processes (a parent and a child). It looks like the context switch takes about 1.02323 microseconds. See `switch.c`.

## The Abstraction: The Process

#### Answer #1
The CPU utilization would be 100%. This is because we are specifying 100% CPU utilization for each process.
***

#### Answer #2
It should take 11 time slices.
- 4 time slices for the first process
- 7 time slices for the second process
  - 5 for the IO
  - 1 to request for IO
  - 1 to wait for IO
***

#### Answer #3
The processes take only 7 time slices to run. Switching the order matters (I thought it would run in the same amount of time), because the CPU switches to the other process while the first one waits for the IO to be completed.
***

#### Answer #4
This time it takes 11 time slices to run (similar as answer #2) because the `SWITCH_ON_END` flag forces the CPU to wait for the IO to finish when the first process starts.
***

#### Answer #5
The process runs in 7 time slices (same as answer #3) since the CPU is switching to the second process while the first one is waiting for the IO to finish.
***

#### Answer #6
No, system resources are not being used effectively, we should probably schedule the process that issue the IO to run immediately after the IO is done. That way the CPU is not idle while waiting for the IO from the last 2 processes.
***

#### Answer #7
This one runs the same processes in just 21 time slices (instead of 31) because we are completing the instruction that started the IO immediately after the IO for it is done, and now we can issue the next IO request and switch to another process while waiting for the next IO request and so on. In this case the CPU utilization is 100% which is what we want.
***

#### Answer #8
- `IO_RUN_IMMEDIATE` generally works better since we can finish the instruction once the IO is finished and we can have the CPU execute the next instruction immediately.
- `SWITCH_ON_END` slows down the processes because we don't switch to another process until the IO for an instruction is done.
***


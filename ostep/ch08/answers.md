## Scheduling: The Multi-Level Feedback Queue

#### Answer #1
One example job would be: `./mlfq.py -j 2 -n 2 -i 0 -m 10 -M 0` whose execution trace looks like the following:
```bash
Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] JOB BEGINS by JOB 1
[ time 0 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 7 (of 8) ]
[ time 1 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 6 (of 8) ]
[ time 2 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 5 (of 8) ]
[ time 3 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 4 (of 8) ]
[ time 4 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 3 (of 8) ]
[ time 5 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 2 (of 8) ]
[ time 6 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 1 (of 8) ]
[ time 7 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 0 (of 8) ]
[ time 8 ] FINISHED JOB 0
[ time 8 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 3 (of 4) ]
[ time 9 ] Run JOB 1 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 2 (of 4) ]
[ time 10 ] Run JOB 1 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 1 (of 4) ]
[ time 11 ] Run JOB 1 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 0 (of 4) ]
[ time 12 ] FINISHED JOB 1
```
***

#### Answer #2
- A single long running job: `./mlfq.py -l 0,100,0`
- Along came a short job: `./mlfq.py -l 0,200,0:100,20,0`
- What about I/O? : `./mlfq.py -l 0,200,0:50,150,1 -S`
***

#### Answer #3
You can do this by assigning the same priority to every job in the queue, this way it will behave the same way as the Round-Robin scheduler.
***

#### Answer #4
You can do this by making an IO request just before the job from the CPU is released: `./mlfq.py -j 2 -m 50 -i 49 -S -c`
***

#### Answer #5
This amount is dependent on the amount of queue priority levels, if the scheduler has 5 level queues, in order to prevent the lowest priority from starving I'd say to set it to `125ms`.
***

#### Answer #6
Use different values for `I` (play around with it)
***

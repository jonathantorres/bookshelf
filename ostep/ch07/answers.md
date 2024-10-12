## Scheduling: Introduction

#### Answer #1
##### FIFO Scheduler
| Metric           | Job 0 | Job 1 | Job 2 |
| ---------------- | ----- | ----- | ----- |
| Response Time    | 0     | 200   | 400   |
| Turnaround Time  | 200   | 400   | 600   |

##### SJF Scheduler
| Metric           | Job 0 | Job 1 | Job 2 |
| ---------------- | ----- | ----- | ----- |
| Response Time    | 0     | 200   | 400   |
| Turnaround Time  | 200   | 400   | 600   |

***

#### Answer #2
##### FIFO Scheduler
| Metric           | Job 0 | Job 1 | Job 2 |
| ---------------- | ----- | ----- | ----- |
| Response Time    | 0     | 100   | 300   |
| Turnaround Time  | 100   | 300   | 600   |

##### SJF Scheduler
| Metric           | Job 0 | Job 1 | Job 2 |
| ---------------- | ----- | ----- | ----- |
| Response Time    | 0     | 100   | 300   |
| Turnaround Time  | 100   | 300   | 600   |
***

#### Answer #3
##### Round-Robin Scheduler
| Metric           | Job 0 | Job 1 | Job 2 |
| ---------------- | ----- | ----- | ----- |
| Response Time    | 0     | 1     | 2     |
| Turnaround Time  | 298   | 499   | 600   |
***

#### Answer #4
SJF delivers the same turnaround time as FIFO for workloads in which the jobs have the same length or if they come in increasing order of length.
***

#### Answer #5
If both the job length and the quantum length are the same, then SJF will deliver the same response time as RR.
***

#### Answer #6
The response time increases as the time for each job increases. Here we are duplicating the length of the job as it arrives, the response time for each increases in a similar way.
```bash
./scheduler.py -p SJF -l 1,2,4,8,16,32,64,128 -c

ARG policy SJF
ARG jlist 1,2,4,8,16,32,64,128

Here is the job list, with the run time of each job: 
  Job 0 ( length = 1.0 )
  Job 1 ( length = 2.0 )
  Job 2 ( length = 4.0 )
  Job 3 ( length = 8.0 )
  Job 4 ( length = 16.0 )
  Job 5 ( length = 32.0 )
  Job 6 ( length = 64.0 )
  Job 7 ( length = 128.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 1.00 secs ( DONE at 1.00 )
  [ time   1 ] Run job 1 for 2.00 secs ( DONE at 3.00 )
  [ time   3 ] Run job 2 for 4.00 secs ( DONE at 7.00 )
  [ time   7 ] Run job 3 for 8.00 secs ( DONE at 15.00 )
  [ time  15 ] Run job 4 for 16.00 secs ( DONE at 31.00 )
  [ time  31 ] Run job 5 for 32.00 secs ( DONE at 63.00 )
  [ time  63 ] Run job 6 for 64.00 secs ( DONE at 127.00 )
  [ time 127 ] Run job 7 for 128.00 secs ( DONE at 255.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 1.00  Wait 0.00
  Job   1 -- Response: 1.00  Turnaround 3.00  Wait 1.00
  Job   2 -- Response: 3.00  Turnaround 7.00  Wait 3.00
  Job   3 -- Response: 7.00  Turnaround 15.00  Wait 7.00
  Job   4 -- Response: 15.00  Turnaround 31.00  Wait 15.00
  Job   5 -- Response: 31.00  Turnaround 63.00  Wait 31.00
  Job   6 -- Response: 63.00  Turnaround 127.00  Wait 63.00
  Job   7 -- Response: 127.00  Turnaround 255.00  Wait 127.00

  Average -- Response: 30.88  Turnaround 62.75  Wait 30.88
```
***

#### Answer #7
The response time also increases, this response time grows in relation with the number of jobs and the quantum. If `n` represents the number of jobs and `q` is the quantum, then an equation that gives the response time in the worst case would look like this: `q(n-1)`
***

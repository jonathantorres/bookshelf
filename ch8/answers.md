## 8. Scheduling: The Multi-Level Feedback Queue (Answers)
1. Run the random jobs

2. Translate the settings of each illustration into command line arguments for the scheduler

3. Assign the same priority to every job in the queue, so that it has the RR behaviour

4. Make an IO request just before the job from the CPU is released. `python mlfq.py -j 2 -m 50 -i 49 -S -c`

5. This amount is dependent on the amount of queue priority levels, if the scheduler has 5 level queues, in order to prevent the lowest priority from starving I'd say to set it to `125ms`.

6. Use different values for `I` (play around with it)

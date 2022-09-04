## 26. Concurrency: An Introduction (Answers)

1. The value will be -1

2. The value of dx will go from 3 to -1 on each thread. No, I do not think there's a race in this code

3. Yes, the value of dx is not kept accross each interrupt, causing unexpected results

4. The value of it is 0 and 1 accross the run

5. Because the value of the register starts at 3. The final value is 6

6. The critical section is the instruction that substracts the value, and puts it back at the memory location 2000

7. The value will be 1, it seems to be correct when the number of interrupts is greater than 2

8. Interrupt numbers greater than 5

9. It's final value will be 1

10. Thread 0 is waiting for thread 1 to change it's value

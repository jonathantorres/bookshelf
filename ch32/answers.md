# 32. Common Concurrency Problems

1. The output does not seem to change, one thread does the add and returns, the other one does the same

2. More add operations are performed, the program doesn't seem to deadlock

3. Same outcome I'll say, it's just more calls to `add`. Running it with just 1 thread will ensure no deadlocks (it's just one thread!)

4. It enforces lock ordering by lock address

5. It takes almost 8 seconds. With the double amount of threads (4) it takes double the same (16 seconds)

6. It varies, but the differences are minimal

7. Yes, it keeps trying to get the lock until it is obtained. It's about twice as fast. The number of retries is reduced as the number of threads is increased

8. It's a bit more slower since it uses a single global lock

9. I would say it does, kind of the same performace as the programs with the locks

10. Almost the same, didn't find that many differences between both

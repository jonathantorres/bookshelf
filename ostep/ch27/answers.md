## 27. Interlude: Thread API (Answers)

1. Yes, it tells you in which line of code the problem is, it also says the kind of problem encountered (data race) and on which thread

2. The same data races are reported by the tool, even when adding the lock/unlock before and after increasing the `balance` variable

3. The lock cannot be released, hence the deadlock

4. Data races are reported by the tool (running on a mac)

5. I believe it will have the same problem, and the helgrind tool also reports the same

6. The parent spend most of it's time waiting for the child thread to finish

7. It reports a possible data race (running on a mac). Test on a linux machine, it could give more accurate results

8. Both correctness and performance

9. Same error regarding a possible data race (ran on a mac)

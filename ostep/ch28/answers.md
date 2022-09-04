## 28. Locks (Answers)

1. Yes, the comments help a lot

2. It does seem to work, the value of flag will end up back to 0

3. It increases the counter based on the flag, it changes the answers by returning a higher value

4. Lower values generally lead to bad outcomes

5. With an atomic swap of the mutex

6. Not always, but using a lower value for the interrupt seems to remedy it

7. Not every time

8. Just read the assembly code

9. Incosistent behaviour with the interrupts

10. Yes, it can be

11. It does not match the code in the book as exactly. Yes.

12. It seems to take a little longer

13. It can be simulated, since with yield, the work of waiting for the lock goes back to the CPU

14. It does an extra check to see if it's still looping, and keeps trying until the lock is released by another thread

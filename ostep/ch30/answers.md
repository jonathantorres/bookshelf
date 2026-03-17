# 30. Condition Variables (Answers)

1. Some understanding, the comments always help

2. It does change a bit, specially on the way the buffers are handled

3. Runs pretty much the same on both my mac and linux machine

4. It ran for 12 seconds

5. No, not a difference, still took 12 seconds

6. It's a lot more faster, it takes 5 seconds

7. Same, 5 seconds

8. It will run significantly slower with `./main-one-cv-while -p 1 -c 1 -m 1 -C 1,1,1,1,1,1 -v`

9. Runs slower with `./main-one-cv-while -p 1 -c 2 -m 1 -C 1,1,1,1,1,1:1,0,0,1,0,1,1 -v`

10. You can make the threads sleep forever

11. The put or get operation cannot be reliably execute, it can be executed by more than one thread at a time

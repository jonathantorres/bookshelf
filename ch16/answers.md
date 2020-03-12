## 16. Segmentation (Answers)

1. For a simulation with 2 seeds
```
ARG seed 2
ARG address space size 128
ARG phys mem size 512

Segment register information:

Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
Segment 0 limit                  : 20

Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
Segment 1 limit                  : 20

Virtual Address Trace
VA  0: 0x0000007a (decimal:  122) --> VALID in SEG1: 0x000001fa (decimal:  506)
VA  1: 0x00000079 (decimal:  121) --> VALID in SEG1: 0x000001f9 (decimal:  505)
VA  2: 0x00000007 (decimal:    7) --> VALID in SEG0: 0x00000007 (decimal:    7)
VA  3: 0x0000000a (decimal:   10) --> VALID in SEG0: 0x0000000a (decimal:   10)
VA  4: 0x0000006a (decimal:  106) --> SEGMENTATION VIOLATION (SEG1)
```

2. It's 20 for segment 0, the range would be from 0 to 20

3. Try with `./segmentation.py -a 16 -p 128 -A 0,1,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 0 --l0 2 --b1 4 --l1 8 -c`

4. A consisten number for the address parameters, try with `./segmentation.py -a 16 -p 128 -s 2 -c`

5. Use a value higher than the address space, try with `./segmentation.py -a 16 -p 128 -l 0 -L 256 -c`


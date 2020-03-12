## 15. Mechanism: Address Translation (Answers)

1. Example with 3 seeds:
```
ARG seed 3
ARG address space size 1k
ARG phys mem size 16k

Base-and-Bounds register information:

Base   : 0x000022d4 (decimal 8916)
Limit  : 316

Virtual Address Trace
VA  0: 0x0000017a (decimal:  378) --> SEGMENTATION VIOLATION
VA  1: 0x0000026a (decimal:  618) --> SEGMENTATION VIOLATION
VA  2: 0x00000280 (decimal:  640) --> SEGMENTATION VIOLATION
VA  3: 0x00000043 (decimal:   67) --> VALID: 0x00002317 (decimal: 8983)
VA  4: 0x0000000d (decimal:   13) --> VALID: 0x000022e1 (decimal: 8929)
```

2. Use a value of 1000 so that it covers a large amount of the address space

3. The value should be at most `16284`

4. Run the experiments

5. Plot a graph of the fraction of addresses that are valid based on the total physical address


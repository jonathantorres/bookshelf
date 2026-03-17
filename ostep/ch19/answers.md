## 19. Paging: Faster Translation (TLB's) (Answers)

1. I would think it's reliable, since you can use microseconds for measurement, see `gettime.c`

2. See `tlb.c`

3. See `tlb-run.php`, I would say a few hundred to start seeing a difference

4. It's easier to visualize trends and such

5. Try to find some sort of compiler flag, that would remove such optimizations, something like `-O0` for GCC

6. If we let the code run on multiple CPU's we won't be able to measure the TLB performance reliably

7. It will most likely affect performance if the array is not properly initialized beforehand

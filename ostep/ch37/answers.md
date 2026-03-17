# 37. Hard Disk Drives

1.
- seek: 0, rotate: 165, transfer: 30
- seek: 0, rotate: 345, transfer: 30
- seek: 80, rotate: 265, transfer: 30
- seek: 160, rotate: 545, transfer: 90
- seek: 40, rotate: 425, transfer: 120

2. The higher the value, the faster the seek is

3. The higher the value, the faster the rotation is

4. It will execute in this order: 7, 8 and then 30. Seek takes 80, rotate 205 and transfer 90

5. Not at all, same results as before. SATF outperforms SSTF if the values are on the same track and next to each other

6. It takes a bit of time after finishing the seek to the next track, since the value goes over it when it enters the track

7. Seek is 80, rotate 1025 and transfer is 70

8. Not at all, the performance on both schedules seems to be similar

9. It seems to solve the problem of starvation to a certain degree, it's definetely not perfect

10. `./disk.py -z 10,20,30,35,45,55 -G` doesn't seem to be the best with the greedy approach

# 44. Flash Based SSD's

1. A variety of read(), write() and trim() operations

2. It shows a `success` state if succeded and `f` otherwise

3. All the reads fail or are uninitialized

4. With the previous command `./ssd.py -T log -s 2 -n 10 -r 20` total time is 1230.00

5. The direct type performs 5x times worse, with the command in step 4, total time was 5280.00

6. It seems to run as normal, but it takes a while

7. A high of 8 and a low of 4 seems to do the trick

8. The ideal SSD seems to do a lot of less work (less reads and writes) than the log SSD, the garbage collector causes the disk to do less work

9. Try changing the skew values here and there (experiment), depending on the skew values used, it may cause the disk to do a little less work that without the skew

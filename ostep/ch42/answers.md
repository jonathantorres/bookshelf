# 42. Crash Consistency: FSCK and Journaling

1. Run the examples and experiment

2. Corrupt ionode bitmap 13

3. The amount of the refcount that decreased

4. inode corruption in directory, they all can be detected the same way

5. inode orphan, the id of inode is different accross runs

6. inode 12 orphan

7. The inode was a file but then changed to directory

8. inode 4 with directory corrupted

9. An inode points to a dead block, the id of the inode is different accross runs

# 43. Log-structured File Systems

1. The commands were `create file /ku3`, `write file  /ku3 offset=7 size=4`, `create file /qg9`

2. Run with the new flag, and see if it's easier to interpret

3. In the final state, the file system wont be corrupt, it will have the specified files in it

4. I think all pathnames are indeed valid

5. Final state is not corrupted

6. More write operations are performed

7. It seems like they are not recognized

8. The `c` and `d` options to specify if a regular file or a directory is being created

9. Almost the same, just the hardlink parameter that makes a difference

10. Name of the files and the order and number of operations

11. Ran with `100`, `1000` returns an index out of range error. If the checkpoint region is never updated, then restoring loses during a crash wouldn't be possible


## Chapter 11 - Threads

#### 11.1

See `11.c`

#### 11.2

To change the thread id of the pending job, the reader-writer lock must be held in write mode to prevent anyone from searching the list while the ID is updated

#### 11.3

The list is guarded by a reader-writer lock, but the condition variable needs a mutex to protect the condition, also each thread needs a data structure to represent when there is a job available to process

#### 11.4

Both are technically correct, but I prefer the second approach in which we notify the waiting threads after the mutex is unlocked

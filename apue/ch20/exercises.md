## Chapter 20 - A Database Library

#### 20.1

It could cause data-races with `db_nextrec`. Specifically a record could be deleted from the database while `db_nextrec` is still reading it.

#### 20.2

If `db_nextrec` calls `_db_readidx`, and it reads the key into the index buffer for the process. Now, if this process is stopped by the kernel (due to scheduling) and another process runs and calls `db_delete` and the record being read by the other process is deleted.

#### 20.3

No, with mandatory locking other readers and writers are affected.

#### 20.4

I would integrate `fsync` into the `_db_writedat` and `_db_writeidx` functions, this would greatly decrease the overall performace though.

#### 20.5

If we write the index record before the data record and the process is killed before writing the data record, the database would have a valid index record that points to invalid data.

#### 20.6

See `20.6.c`

#### 20.7

See `20.7.c`

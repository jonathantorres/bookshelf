## Chapter 4 - Files and Directories

#### 4.1

`stat` follows symbolic links, so this program will never print a file with the type of "symbolic link"

#### 4.2

All permissions for newly created files will be turned off

#### 4.3

Yes, this denies access to the file. See example below:

```
$ date > myfile
$ chmod u-r myfile
$ ls -l myfile
--w-r--r-- 1 jonathan jonathan 32 Sep  3 19:19 myfile

$ cat myfile
cat: myfile: Permission denied
```

#### 4.4

The file permission bits are unchanged but the files are truncated

#### 4.5

No, since directories have an entry for dot and dot-dot and symlinks have a path to their location which dictates their size

#### 4.6

See `4.6.c`

#### 4.7

It's the shell's default access permission when it creates files via redirection

#### 4.8

`du` requires the name of the file that we just deleted. This is why we need to inspect the amount of free space on the system

#### 4.9

In the case in which the unlinked file is not the last link to the file

#### 4.10

The depth of the directory tree in which we can call `opendir` recursively

#### 4.11

See `4.11.c`

#### 4.12

It can be used to build a copy of a filesystem at a new location to make changes without affecting the original

#### 4.13

Use `stat` to fetch all of the time values, change the time value that you want on the `utimbuf` struct with `utime` and set the others to the value as it was from the call to `stat`

#### 4.14

By using `stat` to get the last modification time and the last access time on the mailbox

#### 4.15

Only the modification time of the file is saved for each file and restored when the archive is extracted

#### 4.16

No, there is no limitation on the depth of the directory tree. Many UNIX tools fail on path names that are greater than `PATH_MAX`

#### 4.17

The call to `unlink` fails silently. The call to `creat` does not make any changes to the file

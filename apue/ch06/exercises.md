## Chapter 6 - System Data Files and Information

#### 6.1

On Linux we can use the `getspnam` function, and use the `sp_pwdp` field in the structure returned

#### 6.2

See `6.2.c`

#### 6.3

See `6.3.c`

#### 6.4

Most systems represent `time_t` as a signed integer, after we calculate the latest time and it wraps around, the date will be set to the smallest date that can be represented with that number.

If `time_t` is represented as a 32-bit integer, it's latest time is 03:14:07 UTC on 19 January 2038, once it wraps around it will be set to 20:45:52 UTC on 13 December 1901.

#### 6.5

See `6.5.c`

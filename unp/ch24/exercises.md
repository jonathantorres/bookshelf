## Chapter 24 - Out-of-Band Data

#### 24.1

Yes, the first call to `send` sends 2 bytes that are sent with a single urgent pointer, the second example (with two function calls) send their only byte with the urgent pointer (each is different) that points just beyond it.

#### 24.2

See `24.2.c`

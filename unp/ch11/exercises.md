## Chapter 11 - Name and Address Conversions

#### 11.1

See `11.1.c`

#### 11.2

See `11.2.c`

#### 11.3

This server just sends data to the client indefinitely until the client closes the connection.

#### 11.4

See `11.4.c`

#### 11.5

See `11.5.c`

#### 11.6

See `11.6.c`

#### 11.7

You can do this by allocating a large enough buffer and call the `getsockname` function.

#### 11.8

See `11.8.c`

#### 11.9

The problem is that the second server cannot bind the same port since the `SO_REUSEADDR` option is not set on it.

#### 11.10

The output of "Trying..." means that `gethostbyname` has returned the IP Address. The output of "Connected to..." means that `connect` has returned succesfully.

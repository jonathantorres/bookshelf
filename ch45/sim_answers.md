# 45. Data Integrity and Protection (Simulation)

1. For decimals `216,194,107,66`. The Add is `71`, the Xor is `51` and the Fletcher is `73,196`.

2. Same calculations, with a random seed

3. This can be accomplished by using `./checksum.py -D 256,256,256,256 -c`, this happens due to overflow on a byte value, since it over the range `0` to `255`

4. Use `./checksum.py -D 67,5,6,9 -c`

5. Use `./checksum.py -D 25,25,50,50 -c` and `./checksum.py -D 10,10,100,30 -c`

6. Use `./checksum.py -D 3,12,48,192 -c` and `./checksum.py -D 129,66,36,24 -c`

7. Addition and Xor are the same but Fletcher checksum can be calculated with two different values

8. Use `./checksum.py -D 255,1,2,3 -c`


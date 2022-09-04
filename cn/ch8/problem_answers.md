#### P1
- Encoding is "uasi si my cmiw lokngch"
- Decoding is "wasn't that fun"

#### P2
If Trudy knew that the words "bob" and "alice" appeared in the text, she would know the ciphertext for b,o,a,l,i,c,e. Since she knows the ciphertext for 7 letters, then she needs to try 19!, rather than 26! pairs, which is approximately 10^9

#### P3
Since every letter of the alphabet is on that phrase, the Caesar cipher would be broken, the intruder would know the ciphertext character for every plaintext character

#### P4
- Output is 00000101 repeated eight times
- Output is 00000101 repeated seven times + 10000101
- For (a) output is 10100000 repeated eight times
- For (b) output is 10100001 + 10100000 repeated seven times

#### P5
214 bits are necessary

#### P6
- 100100100 -> 011011011
- They are the same
- c(i) = KS(m(i)) XOR c(i-1)
- c(i) = KS(100 XOR 111) = KS(011) = 100
- c(2) = KS(100 XOR 100) = KS(000) = 110
- c(1) = KS(100 XOR 110) = KS(010) = 101

#### P7
- The message is dog

#### P8
- n = 5, z = 40
- e = 3 is less than n and has no common factors with z
- d = 27
- m = 8, me = 512, ciphertext c = me mod n = 17

#### P9
- S = (TB^SA) mod p = ((g^SB mod p)^SA) mod p  
    = (g^(SBSA)) mod p = ((g^SA mod p)^SB) mod p  
    = (TA^SB) mod p = S
- p = 11, g = 2
- p = 11, g = 2
![problem9](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch8/img/p9.jpg)

#### P10
![problem10](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch8/img/p10.jpg)

#### P11
The message has the same checksum:
```bash
I O U 1
9 0 . 9
O B O B
```

#### P12
![problem12](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch8/img/p12.jpg)

#### P13
File is broken into blocks of equal size, for each block calculate a hash (MD5 or SHA-1). When a peer downloads a block, calculate the has of this block and compare it to the hash in the `.torrent` file. If they are equal, the file is valid, otherwise it's a bogus file

#### P14
Yes, it's true

#### P15
Bob does not know if he's talking to Trudy or Alice initially, Bob and Alice share a secret key that Trudy does not know
- Bob to Trudy: "I am Bob"
- Trudy to Bob: "I am Alice"
- Bob to Trudy: "R"
- Trudy to Bob: "R"
- Bob to Trudy: K A-B(R) - Bob completes his own authentication
- Trudy to Bob: K A-B(R) - Trudy completes her authentication, responding to the R that Bob sent, Bob now thinks that Trudy is Alice

#### P16
This wouldn't solve the problem. Just as Bob thinks that he's authenticating Alice, so too can Trudy fool Alice into thinking that she is authenticating Bob

#### P17
![problem17](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch8/img/p17.jpg)

#### P18
- No, without a public-private key pair, Bob cannot verify that Alice created the message
- Yes, Alice simply encrypts the message with Bob's public key and sends the encrypted message to Bob

#### P19
- Client
- IP - 216.75.194.220 port: 443
- 283
- 3 SSL records
- Yes, contains encrypted master secret
- First byte: bc, Last byte: 29
- 6

#### P20
Trudy needs to adjust the sequence numbers in the subsequent packets sent from Alice to Bob and the acknowledgment numbers sent from Bob to Alice. The result is that Bob will be missing a packet's worth of bytes in the byte stream

#### P21
Add a checksum or some sort of integrity check on the link-state messages that are broadcast to the router

#### P22
- False
- True
- True
- False

#### P23
If Trudy does not bother to change the sequence number, R2 will detect the duplicate when checking the sequence number in the ESP header. If Trudy increments the sequence number, the packet will fail the integrity check at R2

#### P24
- IV: 11
- Encrypted message: 10100000 XOR 11111010 = 01011010
- Encrypted ICV: 1010 XOR 0000 - 1010
- 1010 XOR 0000 = 1010. The receiver then XOR's the first 4 bits of recovered message with it's last 4 bits: 1010 XOR 0000 = 1010 which equals the recovered ICV
- Either the 1st or the 5th bit of the message has to be flipped
- For a) the message was 01011010 flipping the first bit gives, 11011010 and then Trudy XOR's this message with keystream: 11011010 XOR 11111010 = 00100000

#### P25
![problem25](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch8/img/p25.jpg)

#### P26
![problem26](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch8/img/p26.jpg)

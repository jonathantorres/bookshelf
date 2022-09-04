#### R1
A firewall blocks packets based on rules from the network administrator (source IP address etc. etc) and the firewall will check th epacket headers against these rules, and an instrusion detection system checks the actual data in the packets

#### R2
- User's laptop
- Web server
- Two routers
- Two DNS servers

#### R3
It comes from the secret decryption key that is only known by the user

#### R4
In the known-plaintext attack, the attacker knows some of the (plaintext, ciphertext) pairings, in a chosen-plaintext attack, the attacker is able to choose the plaintext message and obtain it's corresponding ciphertext form

#### R5
An 8-block cipher has 2^8 possible input blocks. Each mapping is a permutation of the 2^8 input blocks, so there are 2^8 possible mappings, so there are 2^8! possible keys

#### R6
For symmetric keys, there should be N x (N-1)/2 keys. In a public key system, there should be 2N keys

#### R7
(a x b) mod n = 23 x 4 = 92

#### R8
175

#### R9
In that is very difficult to find another message that translates to the same hash

#### R10
No, a hash function is a one-way function

#### R11
Yes, it's flawed. An attacker can obtain the shared secret by extracting the last portion of digits from H(m) + S

#### R12
Is when the document is encrypted with a secret key that is only known by the parties involved

#### R13
One way to do this is for the network administrator to enter the secret key to each router manually, this would only work with smaller networks of course

#### R14
SSH and SSL

#### R15
In this case a digital signature is better, Alice can use the same signature for every recipient

#### R16
A nonce is used

#### R17
It means that the entity sending the nonce will never again use that value to check whether another entity is "live"

#### R18
In a man-in-the middle attack, the attacker puts himself between Alice and Bob, altering the data between them. If both share a secret authentication key, alterations will be detected

#### R19
A digital signature can be provided. PGP uses digital signatures, not MAC's for message integrity

#### R20
False, SSL uses implicity sequence numbers

#### R21
Is to defend agains the connection replay attack

#### R22
True, the IV is always sent in the clear

#### R23
After the client generates a pre-master secret (PMS) it will encrypt it with Alice's public key, and send it to Trudy. Trudy will not be able to decrypt it since she does not have Alice's private key

#### R24
False

#### R25
False

#### R26
No, more than 1 algorithm can be chosen by the server

#### R27
01011100

#### R28
Yes, it's appended

#### R29
Filter table and connection table. The connection table keeps track of the connections, allowing better packet filtering

#### R30
True

#### R31
True

#### R32
If there isn't a packet filter, the users inside the network will still be able to make connections to hosts outside the institution's network. The filter forces users to firt connect to the application gateway

#### R33
True

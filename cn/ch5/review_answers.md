#### R1
Is when the link layer encapsulates each network-layer datagram within a link-layer frame before transmission over the link

#### R2
No, TCP is still needed to provide the receiving end of the application the byte stream in the correct order

#### R3
- Parity checks
- Checksumming methods
- Cyclic redundancy check (CRC)

#### R4
There will be a collision in the sense that while a node is transmitting it will start to receive a packet from the other node

#### R5
- Slotted Aloha: 1, 2 and 4
- Token passing: 1, 2, 3 and 4

#### R6
The probability is 1/32. It waits 204.8 ms

#### R7
In polling, a leader allows only one participant to talk at a time, with each participant having a chance to talk in a round-robin fashion. For token ring a participant is only allowed to talk if it's holding the wine glass

#### R8
When a node transmits a frame, the node has to wait for the frame to propagate around the entire ring before the node can release the token

#### R9
- MAC Address - 2^48 6 bytes long
- IPv4 Address - 2^32 4 bytes long
- IPv6 Address - 2^128 16 bytes long

#### R10
C's adapter will process the frames, but the adapter will not pass the datagrams up the protocol stack. If the LAN broadcast address is used, then C's adapter will both process the frames and pass the datagrams up the protocol stack

#### R11
2^24 adapters or 16,777,216 adapters

#### R12
No, it's not possible. Each LAN has it's own distinct set of adapters attached to it, with each adapter having a unique LAN address

#### R13
When a bit arrives from one interface, the hub re-creates the bit boosts it's energy strength, and transmits the bit onto all other interfaces

#### R14
2. The internal subnet and the external internet

#### R15
The mapping of MAC addresses to it's appropriate IP address, and a time-to-live (TTL) which indicates when the mapping will be deleted from the table

#### R16
Each of the first 7 bytes has a value of 10101010, the last byte is 10101011. The last byte of the preamble is to let an adapter know that "important stuff" is about to come

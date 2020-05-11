#### P1
- source: 27459, dest: 80
- source: 25111, dest: 80
- source: 80, dest: 27459
- source: 80, dest: 25111
- THe could be, but their IP addresses would be different
- Not in that case, ports would have to be different, otherwise it would be the same client

#### P2
Source port is 80 and destination ports are 26145 and 7532. Source IP is B and destination IP's are A and C

#### P3
00000010. It detects errors when the expected buts are different. In both cases it's possible

#### P4
- 11111011
- 11111111
- The opposite bits

#### P5
When a segment is stored in the router's memory

#### P6
The value is stored in the TCP segment

#### P7
Host A must continue to send segments with one data byte. These will be acknowledged and eventually the buffer will begin to empty and the acknowledgments will contain a nonzero `rwnd` value

#### P8
***Insert image***

#### P9
***Insert Image***

#### P10
***Insert Image***

#### P11
No, since the ACK from the receiver won't be sent. It won't take an action

#### P12
Yes, it would still work, but the packets in error would have to be retransmitted

#### P13
***Insert Image***

#### P14
No, since it's only acknowledging failures. It would not be guaranteeing the receival of the packets on the receival's end

#### P15
32,000 bytes

#### P16
- It sends the signal to the other host that it wants to end the connection
- The other host acknoledges it
- The initiator knows that the other host reveived it
- The initiator ends the connection, sends the final ACK
- The received receives this and ends it's connection

#### P17
***Insert picture***

#### P18
- Send two messages at a time
- If a packet is lost, detect it and resend it again
- Every packet received by the receiver must be ACK'd
- Use a timeout to detect packet loss

#### P19
- Host B and C would have to ACk that the packer from A was received
- If a packet is lost, resend it to the appropriate host
- Use the same error-control protocol for both B and C

#### P20
- Host A and B would send packets that host C would ACK
- If the ACK is not received in a timeout, the re-send the packet
- The same error-control protocol would have to be used for all, A, B and C

#### P21
- Use the GBN protocol (or a variation of)
- It will account for any loss messages at the other end, and make sure they are re-sent, and delivered correctly

#### P22
- Any number between k and 1024
- The value of k+1

#### P23
A number in the range from 0 to k

#### P24
No response or ACK will be received from the server, and TCP will timeout, and the connection will not be established.

#### P25
The host will send a special ICMP datagram

#### P26
- `L/512`
- About 3.4ms. That's if L = 5,120 bytes

#### P27
- Sequence #168, source port is 80 and destination port is 302
- ACK # is 128, source port is 80 and destination port is 302
- The ACK is # 167
- ***Insert Image***

#### P28
Massive overflow, a lot of packets would have to be re-sent. The other end read the data out at a much slower rate than that it goes in

#### P29
Each packet is uniquely identified by the internet checksum. Any duplicate packet that already has been ACK'd is then discarded

#### P30
The stay in the buffer until the packet in between is ACK'd, then is sent out in order to the other end

#### P31
- `EstimatedRTT` = 100.75ms
- `DevRTT` = 5.06ms
- `TimeoutInterval` = 120.99ms

#### P32
- `EstimatedRTT` = (1-0.1) * `EstimatedRTT` + 0.1 * `SampleRTT[n]`
- `EstimatedRTT` = (1-0.1) * `EstimatedRTT` + 0.1 * `SampleRTT[n]`
- Because it grows exponentially on each `EstimatedRTT`

#### P33
`TimeoutInterval` = `EstimatedRTT` + 4 * `DevRTT`

#### P34
Is the sequence number of the oldest unacknowledged byte

#### P35
If a segment is lost, TCP can re-transmit the value quickly

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
![problem8](https://github.com/jonathantorres/cn/blob/master/ch3/img/p8.jpg)

#### P9
![problem9](https://github.com/jonathantorres/cn/blob/master/ch3/img/p9.jpg)

#### P10
![problem10](https://github.com/jonathantorres/cn/blob/master/ch3/img/p10.jpg)

#### P11
No, since the ACK from the receiver won't be sent. It won't take an action

#### P12
Yes, it would still work, but the packets in error would have to be retransmitted

#### P13
![problem13](https://github.com/jonathantorres/cn/blob/master/ch3/img/p13.jpg)

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
![problem8](https://github.com/jonathantorres/cn/blob/master/ch3/img/p8.jpg)

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
- ![problem27](https://github.com/jonathantorres/cn/blob/master/ch3/img/p27.jpg)

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

#### P36
The remedy is a duplicate ACK

#### P37
- A has sent 5 segments and B has sent 4 ACK's
- TCP which uses a good combination of both GBN and Selective Repeat (SR)

#### P38
Yes, it should be set to this value to keep the congestion window to a manageable value

#### P39
It ackknowledges out of order segments selectively rather than just cumulatively acknowledging the last correctly received, in order segment. Looks like a generic SR protocol

#### P40
- From 1 to 6
- From 14 to 20
- By a timeout
- Triple duplicate ACK
- Around 8 segments
- Around 6 segments
- Around 8 segments
- About the 90th transmission round
- 15 and 8
- Around 6 segments
- An estimate of 320 packets

#### P41
Congestion control is done via the congestion window and flow control is done via the receive window

#### P42
Since resources are allocated at each end to transmit the packet, then that statement is justifiable

#### P43
I don't think anything can prevent the transfer of the file, it's just that is going to be a very slow transfer, since the sending host can only hold 1 percent of the file at a time

#### P44
- 6 MSS
- 8 MSS

#### P45
- 0.75 * W/RTT
- L = 1/(3/8) * W^2

#### P46
- 425 segments
- 350 segments and 8Mbps
- 5.2 seconds

#### P47
Yes, otherwise we wouldn't be able to send the bytes of data at a constant rate

#### P48
The link is a lot faster (10Gbps) doesn't that solve the problem?

#### P49
If T = 5 RTT and W = 6, then yes T would be = 1.22 * MSS / RTT * sqrt(L)

#### P50
- 50 segments
- Not likely since the RTT's on both C[1] and C[2] are different. 50 msec and 100 msec respectively

#### P51
- 146 segments for C[1] and 220 segments for C[2]
- It's possible since they have the same RTT
- Yes, possibly and the 15th segment for C[1], C[2] would reach it's 10th segment
- Will have the same usage in terms of bandwidth, but not sure if it will increase the utilization of the links

#### P52
L/W. It would since the congestion window would be increased by the same constant

#### P53
It would be 2 * 10^50 (1 out of 50,000,000)

#### P54
To keep the window and the threshold in control, in case there's a big surge in the traffic of the network. I would increase the congestion window by a fraction of time where the connection remains idle

#### P55
- To the spoofed address but it won't receive the appropriate response since the checksum won't succeed it's validation
- Yes, the spoofing is prevented with SYN cookies

#### P56
- 12 RTT
- 4 RTT
- 3 RTT

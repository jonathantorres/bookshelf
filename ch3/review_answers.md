#### R1
- Use multiplexing from the host and demultiplexing at the destination host.
- This would add a field in the header that contains the "return address"
- No, since it's built on top of it

#### R2
- Add the name of the recipient to the top (header) of the letter
- No, no need to. All the information needed to deliver the letter is in top of the letter (header)

#### R3
Source port number is 61 and destination port is 37

#### R4
Both can be used, for video conferencing we can use UDP for video content delivery, and TCP for the other Internet services, HTTP, Email etc. etc.

#### R5
TCP has 20 bytes of header overhead in every segment, and UDP has only 8 bbytes of overhead

#### R6
None. UDP does not guarantee reliability of the data, same as the network layer

#### R7
Yes, to the same socket. It will use the source IP address of the segment header to differentiate between both

#### R8
No, a different socket is create on the server to handle each client. The destination port of each socket will be 80, the source will be different per connection/client

#### R9
The positive acknowledgement is when a message is received succesfully, the negative acknowledgement is when it's not

#### R10
- Keep asking what was the response to the message. "What did you say?"
- Add checksum bits so the sender can detect and recover from bit errors
- The sender would have to re-send the data when the ACK is not received

#### R11
- Wait for call from above and wait for ACK or NAK
- Wait for call from below

#### R12
- ACK's are not sent for the rest of the packets since they arrived out of order
- It looks like the packet is still ACK'd even though the ACK was not reveived
- Only 5 packets can be sent, window size is 5

#### R13
- The rest of the packets are buffered, the lost packet is re-sent after a timer
- The packet with the lost ACK is re-sent, duplicate packet is detected and discarded, ACK is re-sent
- Only 5 packets can be sent, window size is 5

#### R14
- false
- false
- false
- true
- false
- true
- true
- false

#### R15
- 65 bytes
- 66

#### R16
Because it's part of the network edge which is implemented in the end systems

#### R17
TCP would like to give the same transmission rate to each connection

#### R18
Because it consistes of a linear increase in `cwnd` of 1 MSS per RTT and then a halving of `cwnd` on a triple duplicate-ACK event

#### R19
Yes, Since UDP has no fairness mechanism. It just sends packets to the network layer

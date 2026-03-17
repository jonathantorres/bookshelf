#### R1
| Person         | Bit Rate   | Bytes Transferred |
| -------------- | ---------- | ----------------- |
| Facebook Frank | 40 Kbps    | 20 Mbytes         |
| Martha Music   | 200 Kbps   | 100 Mbytes        |
| Victor Video   | 4 Mbps     | 2 Gbytes          |

#### R2
4 bits

#### R3
160 Kbps

#### R4
- Streaming
- Interactivity
- Continuous Playout

#### R5
- It can absorb variations in server-to-client delay
- If server-to-client bandwidth briefly drops below the video consumption rate, a user can continue to enjoy continuous playback, as long as the client application buffer does not become completely drained

#### R6
- It allows the video traverse firewalls and NAT's
- It obviates the need for a media control server
- Reduces the cost of a large scale deployment over the internet

#### R7
No, on the client side, the client application reads bytes from the TCP receive buffer and places the bytes in the client application buffer

#### R8
t[p] = Q/x = 4 seconds

#### R9
When a client downloads video at a rate higher than the consumption rate

#### R10
Geographically closest cluster selection and real time measurements selection can find a good cluster with respect to LDNS. IP anycast chooses good cluster with respect to client itself

#### R11
- Load on the cluster
- ISP delivery cost

#### R12
- Prepending each chunk with a timestamp
- Delaying playout of chunks at the receiver

#### R13
- Forward error correction (FEC)
- Interleaving

#### R14
- First scheme: send a redundant encoded chunk after every n chunks
- Second scheme: send a lower-resolution low-bit rate scheme along with the original stream

#### R15
- Payload type
- Sequence Number
- Timestamp
- Synchronization source identifier

#### R16
It keeps track of the users and their corresponding IP addresses which they are currently using

#### R17
In non-preemptive priority queuing the transmission of a packet is not interrupted once it has begun, in preemptive priority queueing, the transmission of a packet will be interrupted if a higher priority packet arrives before transmission completes

#### R18
An example is time division multiplexing, whereby a rotating frame is partitioned into slots, with each slot exclusively available to a particular class

#### R19
It was proposed as a signaling protocol to coordinate the per-hop allocation of local resources, as well as the overall end-to-end decision of whether or not a call has been able to reserve sufficient resources at each and every router on the end-to-end path


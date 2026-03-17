#### R1
They all refer to a packet but it's names differently based on the networking layer. The router forwards a packet based on the IP address and the link-layer switch is based on the MAC address

#### R2
It defines the characteristics of end-to-end transport of packets between sending and receiving end systems

#### R3
- In order packet delivery
- Guaranteed minimal bandwidth
- Guaranteed maximum jitter
- Security services

#### R4
- It consists of a path between the source and destination hosts
- VC numbers, one number for each link along the path
- Entries in the forwarding table in each router along the path

#### R5
It reduces the length of the VC field in the packet header and the VC setup is considerably simplified by permitting a different VC number at each link along the path of the VC

#### R6
It passes through a series of routers, each router uses the packet's destination address to forward the packet

#### R7
The forwarding table

#### R8
They are capable of forwarding multiple packets in parallel

#### R9
Is that it must choose one packet amojng those queued for transmission

#### R10
Is when a packet is dropped when there is no enough memory to buffer it. They are packet-dropping and marking policies. The Random Early Detection (RED) algorithm

#### R11
When a queued packet in an input queue must wait for transfer through the fabric because it is blocked by another packet at the head of the line

#### R12
Eight IP addresses

#### R13
11001010000000110000111000011001

#### R14

#### R15
10 interfaces, 4 routing tables

#### R16
50% overhead and 50% application data

#### R17
With the upper-layer protocol field in the IP datagram

#### R18
Every PC will have the prefix of 802.11, 802.12, 802.13 and so on. I think, it will use DHCP to distribute the IP addresses to the other PC's

#### R19
Yes, the data, destination and source address, version etc etc

#### R20
Yes, I would say so. The IPv6 packet goes in the data field of the IPv4 packet

#### R21
In a static routing algorithm, the routes change very slowly over time, often as result of human intervention, dynamic routing algorithms change the routing paths as the network traffic loads or topology change

#### R22
The cost may represent the physical length of the link, the link speed, or the monetary cost associated with it

#### R23
It's carried out in an iterative, distributed manner. Each node knows the cost of the link attached to it

#### R24
The destination subnet z will change to 2 hops

#### R25
It's used to decide whether to accept or filter a route and whether to set certain attributes such as the router preference metrics

#### R26
Route

#### R27
Due to the differences between the goals of routing within an AS and among AS's
- Policy
- Scale
- Performance

#### R28
ISP C can use the BGP Multi-Exit Descriptor to suggest to ISP B that the preferred route to ISP D is through the east coast peering point

#### R29
A subnet is a portion of a larger network, it does not contain a router. A prefix is the network portion of a CDIRize address. When a router advertizes a prefix across a BGP session, it also includes a number of BGP attributes, which is also a route

#### R30
It uses it in advertisements to determine which peering link to use. The AS-PATH contains the ASs through which the advertisement for the prefix has passed

#### R31
Any traffic flowing across an ISP's backbone networking must have either a source or a destination (or both) in a network that is customer of that ISP

#### R32
N-way has some drawbacks:
- Efficiency: multiple copies of the same packet are sent over the same link
- Addressing: The source must discover the address of all the recipients

#### R33
- uncontrolled flooding: true, controlled flooding: true, spanning tree: false
- uncontroller flooding: true, controlled flooding: false, spanning tree: false

#### R34
No, it must not

#### R35
IGMP is a protocol run only between the host and it's first hop multicast router. It allows a host to specify the multicast group it wants to join

#### R36
The multicast routing over a group-shared tree is based on building a tree that includes all edge routers with attached hosts belonging to the multicast group. The multicast using a source-based tree constructs a routing tree for each source in the multicast group. An RPF algorithm is used

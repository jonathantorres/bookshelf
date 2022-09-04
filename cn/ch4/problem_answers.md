#### P1
- Datagram network would be better, since no signaling is required to either set up a new downstream path or take down an old downstream path
- A VC network is preferable, it would need to know the characteristics of the traffic from all sessions passing through that link
- In this scenario a datagram architecture has more control traffic overhead

#### P2
- 256
- The centralized node could pik any free VC number. So it's not possible that there are fewer VC's in progress that 256
- Each link independently allocates VC numbers. Thus, a VC will likely have a different VC number for each link along it's path

#### P3
For VC table:
- Incoming interface
- Incoming VC number
- Outgoing interface
- Outgoing VC number

For datagram table:
- Destination address
- Outgoing interface

#### P4
- Data for H3 is forwarded through interface 3
- No, since forwarding rule is only based on destination address

Incoming interface  | Incoming VC number  | Outgoing interface  | Outgoing VC number
| ----------------- | ------------------- | ------------------- | ------------------ |
| 1                 | 12                  | 3                   | 22                 |
| 2                 | 63                  | 4                   | 18                 |

Router   | Incoming interface  | Incoming VC number  | Outgoing interface  | Outgoing VC number
-------- | ------------------- | ------------------- | ------------------- | ------------------ |
Router B | 1                   | 22                  | 2                   | 24                 |
Router C | 1                   | 18                  | 2                   | 50                 |
Router D | 1                   | 24                  | 3                   | 70                 |
Router D | 2                   | 50                  | 3                   | 76                 |

#### P5
- No VC can be assigned to the new VC
- Each link has two available VC numbers

#### P6
Probably less control over which IP addresses are assigned to each host

#### P7
- No, only one at a time over a shared bus
- Yes
- No

#### P8
- (n-1)D
- (n-1)D
- 0

#### P9
Minimal number of time slots needed is 3:
- Slot 1, send X in top input, send Y in middle input
- Slot 2, send X in middle input, send Y in bottom input
- Slot 3, send Z in bottom input

#### P10
Prefix Match        | Link Interface
| ----------------- | ------------------- |
| 11100000 00       | 0                   |
| 11100000 01000000 | 1                   |
| 11100000          | 2                   |
| 111000001 1       | 3                   |
| otherwise         | 3                   |

- Prefix for 1st address is 5th entry - Link 3
- Prefix for 2nd address is 3rd entry - Link 2
- Prefix for 3rd address is 4th entry - Link 3

#### P11
| Address Range                    | Link Interface
| -------------------------------- | ------------------- |
| 00000000 through 00111111        | 0                   |
| 01000000 through 01011111        | 1                   |
| 01100000 through 01111111        | 2                   |
| 10000000 through 10111111        | 2                   |

#### P12
| Address Range                    | Link Interface
| -------------------------------- | ------------------- |
| 11000000 through 11011111        | 0                   |
| 10000000 through 10111111        | 1                   |
| 11100000 through 11111111        | 2                   |
| 00000000 through 01111111        | 3                   |

#### P13
223.1.17.0/26  
223.1.17.128/25  
223.1.17.192/28  

#### P14
| Destination Address   | Link Interface
| --------------------- | ------------------- |
| 200.23.16/21          | 0                   |
| 200.23.24/24          | 1                   |
| 200.23.24/21          | 2                   |
| otherwise             | 3                   |

#### P15
Since a peer is behind a NAT it cannot act as a server and accept TCP connections, it can be mitigated with a connection reversal

#### P16
Any IP in the range 128.119.40.128 to 128.119.40.191

#### P17
Subnet A - 214.97.255/24  
Subnet B - 214.97.254.0/25  
Subnet C - 214.97.254.128/25  
Subnet D - 214.97.254.0/31  
Subnet E - 214.97.254.2/31  
Subnet F - 214.97.254.4/30  

| Router # | Longest Prefix Match             | Outgoing Interface
| -------- | -------------------------------- | ------------------- |
| Router 1 | 110101 10 011 00001 11111111     | Subnet A            |
| Router 1 | 110101 10 011 00001 11111110     | Subnet D            |
| Router 1 | 110101 10 011 00001 11111110     | Subnet F            |
| Router 2 | 110101 10 011 00001 11111111     | Subnet D            |
| Router 2 | 110101 10 011 00001 11111110     | Subnet B            |
| Router 2 | 110101 10 011 00001 11111110     | Subnet E            |
| Router 3 | 110101 10 011 00001 11111111     | Subnet F            |
| Router 3 | 110101 10 011 00001 11111110     | Subnet E            |
| Router 3 | 110101 10 011 00001 11111110     | Subnet C            |

#### P18
Open question for discussion

#### P19
The maximum size of data field in each fragment 680 (since there are 20 bytes of IP header)

#### P20
Each datagram can carry 1500-40=1460 bytes of the MP3 file

#### P21
- Home Address - 192.168.1.1, 192.168.1.2, 192.168.1.3, Router Interface is 192.168.1.4

| WAN                  | LAN                 |
| -------------------- | ------------------- |
| 24.34.112.235, 4000  | 192.168.1.1, 3345   |
| 24.34.112.235, 4001  | 192.168.1.1, 3346   |
| 24.34.112.235, 4002  | 192.168.1.2, 3345   |
| 24.34.112.235, 4003  | 192.168.1.2, 3346   |

#### P22
- Group the IP packets into a cluster. The number of clusters is the number of hosts behind the NAT
- No, it won't work

#### P23
Not possible to devise such a technique

#### P24
y-x-u, y-x-v-u, y-x-w-u, y-x-w-v-u, y-w-u, y-w-v-u, y-w-x-u, y-w-x-v-u,
y-w-v-x-u, y-z-w-v-u, y-z-w-x-u, y-z, w-x-v-u, y-z-w-v-x-u

#### P25
X to Z  
x-y-z, x-y-w-z, x-w-z, x-w-y-z, x-v-w-z, x-v-w-y-z, x-u-w-z, x-u-w-y-z, x-u-v-w-z, x-u-v-w-y-z  

Z to U  
z-w-u, z-w-v-u, z-w-x-u, z-w-u-x-u, z-w-x-v-u, z-w-y-x-u, z-w-y-x-v-u, z-y-x-u, z-y-x-v-u, z-y-x-w-u, z-y-x-w-y-u, z-y-x-v-w-u, z-y-w-v, z-y-w-x-u

Z to W  
z-w, z-y-w, z-y-x-w, z-y-x-v-w, z-y-x-u-w, z-y-x-u-v-w, z-y-x-v-u-w

#### P26
![problem26](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch4/img/p26.jpg)

#### P27
![problem27](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch4/img/p27.jpg)

#### P28
![problem28](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch4/img/p28.jpg)

#### P29
At each iteration, a node exchanges distance tables with it's neighbors. If you are node A and your neighbor is B all of B's neighbors will know the shortest cost path of one or two hops to you after one iteration. If the algorithm is run as a result of a change in link costs, there is no a priority bound in the number of iterations required

#### P30
- Dx(w) = 2, Dx(y) = 4, Dx(u) = 7
- If c(x,y) becomes larger or smaller, the least cost path from x to u will still have a cost of at least 7. If c(x,y) =< 1, then the least cost path now passes through y and has cost $+6
- Any change in link cost c(x,y) will not cause x to inform it's neighbors of a new minimum cost path to u

#### P31
![problem31](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch4/img/p31.jpg)

#### P32
No, not at all

#### P33
At each step, each update to a node's distance vectors is based on the Bellman-Ford equation, only decreasing those values in it's distance vector

#### P34
- Router z - Tells w, Dz(x) = Infinity, Tells y, Dz(x) = 6
- Router w - Tells y, Dw(x) = Infinity, Tells z, Dw(x) = 5
- Router y - Tells w, Dy(x) = 4, Tells z, Dy(x) = 4
- Yes, there will be a count to infinity problem
- Cut the link between y and z

#### P35
The full AS path information is available from an AS to a destination in BGP loop detection is simple, if a BGP peer receivrd a route that contains it's own AS number in the AS path, then using that route would result in a loop

#### P36
The chosen path is not the shortest AS-path. There are many issues in the route selection process. A long loop-free path is preferred over a shorter loop-free path due to economic reasons

#### P37
- eBGP
- iBGP
- eBGP
- iBGP

#### P38
- I1 because this interface begins the least cost path from 1d towards the router 1c
- I2, both routers have equal AS-PATH
- I1, it begins the path that has the shortest AS-PATH

#### P39
C has to only advertise it's route to D via it's east coast peering point with C

#### P40
X does not know about the AC link since X does not receive an advertised route to w or to y that contain the AC link

#### P41
BitTorrent file sharing and Skype P2P applications

#### P42
- A should advertise to B two routes, AS-paths A-W and A-V
- A should advertise to C only one route, A-V
- C receives AS path: B-A-W, B-A-V, A-V

#### P43
There's nothing Z can do from preventing traffic from X to transit through Z

#### P44
- The Minimum Spanning Tree has z connected to y via x at a cost of 14(=8+6)
- z connected to v via x at cost 11(=8+3)
- z connected to u via x and v at cost 14(=8+3+3)
- z connected to w via x, v and u at cost 17(=8+3+3+3)

#### P45
The 32 receivers are connected to the sender in the binary tree
![problem45](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch4/img/p45.jpg)

#### P46
![problem46](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch4/img/p46.jpg)

#### P47
![problem47](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch4/img/p47.jpg)

#### P48
AS-PATH and NEXT-HOP

#### P49
The topology in the original figure connects A to C, B to C, E to C and F to C directly. D connects to C via E and G connects to C via D

#### P50
It's caused it by an endless cycling of broadcast packets

#### P51
![problem51](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch4/img/p51.jpg)

#### P52
- After 1 step -> 3 copies are transmitted
- After 2 steps -> 6 copies are transmitted
- After 3 steps -> 12 copies are transmitted
- After k steps -> `3*2^k-1` copies are transmitted

#### P53
The protocol must be built at the application layer. An application may periodically multicast it's identity to all other group members in an application-layer message

#### P54
Each instance of this application would send a multicast message containing it's identity to all other members. This protocol would send a message in-band. The use of in-band signaling makes use of the existing multicast distribution mechanism, leading to a simple design

#### P55
32-4=28 bits are available for multicast addresses. The size of the address space would be `N=2^28`

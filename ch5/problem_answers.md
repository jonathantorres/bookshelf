#### P1
- 11101
- 01100
- 10010
- 11011
- 11000

#### P2
Double bit error:
- 0000
- 1001
- 0101
- 1010

#### P3
The sum would be: 10100010 00001100

#### P4
- 00011001 00011110
- 10011111 10100100
- 00000000 00000001

#### P5
R = 0100

#### P6
- R = 0101
- R = 0001
- R = 0010

#### P7
- If D contains at least two 1's, then a single bit error can always be detected
- No, since a sequence of odd-number bit errors cannot be divided by 11, so it cannot be divided by G

#### P8
- E(p) = O -> p * = 1/N
- lim E(p * ) = 1/e

#### P9
lim E(p * ) = 1/2 * 1/e = 1/2e

#### P10
- A's average throughput is pA(1-pB). Total efficiency is pA(1-pB) + pB(1-pA)
- A's throughput is pA(1-pB) = 2pB(1-pB) = 2pB - 2(pB)2
- B's throughput is pB(1-pA) = pB(1-2pB) = pB - 2(pB)2
- A's throughput is 2p(1-p)N-1

#### P11
- (1-p(A)) 4p(A)
- p(A succeeds in slot 4) = p(1-p)3
- p(B succeeds in slot 4) = p(1-p)3
- p(C succeeds in slot 4) = p(1-p)3
- p(D succeeds in slot 4) = p(1-p)3
- p(some node succeds in a slot) = 4p(1-p)3
- p(no node succeds in a slot) = 1-4p(1-p)3
- efficiency = p(success in a slot) = 4p(1-p)3

#### P12
***screenshot***

#### P13
NQ / N(Q / R + d(poll)) = R / 1+d(poll) / Q

#### P14
***screenshot***
- Forwarding table in E reveals that the datagram should be router to 192.168.3.002
- E Ethernet packet is destined to 88-88-88-88-88-88
- Router 2 receives packet and extracts datagram, datagram to be routed to 198.162.2.002
- Router 2 sends Ethernet packet to 33-33-33-33-33-33 and source 55-55-55-55-55-55 via interface 198.162.2.003
- Process continues until packet reaches host B
- ARP in E determines MAC address of 198.162.3.002. Host E sends an ARP query within a broadcast Ethernet frame. Router 2 receives the query packet and sends Host E an ARP response packet

#### P15
a) No, E can check the subnet prefix of Host F IP address, and learn that F is on the same LAN. From E to F:
- Source IP = E's IP address
- Destination IP = F's IP address
- Source MAC = E's MAC address
- Destination MAC = F's MAC address

b) No, because they are not on the same LAN. From E to R1:
- Source IP = E's IP address
- Destination IP = B's IP address
- Source MAC = E's MAC address
- Destination MAC = The MAC address of R1's interface connecting to subnet 3

c) Switch S1 will broadcast the Ethernet frame via both it's interfaces as the received ARP frame's destination address is a broadcast address. Yes, router R1 also receives the ARP request message

#### P16
a) No, E can check the subnet prefix of Host F's IP address. Ethernet from E to F:
- Source IP = E's IP address
- Destination IP = F's IP address
- Source MAC = E's MAC address
- Destination MAC = F's MAC address

b) Yes, because E would like to find B's MAC address. Ethernet frame from E to S2:
- Source IP = E's IP address
- Destination IP = B's IP address
- Source MAC = E's MAC address
- Destination MAC = broadcast MAC address: FF-FF-FF-FF-FF-FF

c) Switch S1 will broadcast the Ethernet frame via both it's interfaces as the received ARP frame's destination address is a broadcast address. Yes, router S2 also receives the ARP request message

#### P17
Waits for 51,200 bit times. For 10Mbps, this wait is 5.12ms. For 100Mbps the wait is 512 usec

#### P18
At t=0 A transmits. At t=576, A would finish transmitting. In the worst-case, B begins transmitting at t=324, which is right before the first bit of A's frame arrives at B. So, A finishes transmitting before it detects that B has transmitted

#### P19
Because A's retransmission reaches B before B's scheduled retransmission time (805+96). B refrains from transmitting while A retransmits. Thus A and B do not collide. The factor 512 in the exponential backoff algorithms is sufficiently large

#### P20
- efficiency = K / K+X = K / K + 1-Np(1-p)^N-1 / Np(1-p)^N-1
- Maximizing efficiency is equivalent to minimizing x, which is equivalent to maximizing B. B is maximized at p = 1/n
- lim efficiency = K / K + 1 - 1/e / 1/e = K / K+e-1
- Clearly K/K+e-1 approaches 1 as k -> Infinity

#### P21
***screenshot***
i) from A to left router:
- Source MAC address = 00-00-00-00-00-00
- Destination MAC address = 22-22-22-22-22-22
- Source IP = 111.111.111.001
- Destination IP = 133.333.333.003

ii) from left router to right router:
- Source MAC address = 33-33-33-33-33-33
- Destination MAC address = 55-55-55-55-55-55
- Source IP = 111.111.111.001
- Destination IP = 133.333.333.003

iii) from right router to F
- Source MAC address = 88-88-88-88-88-88
- Destination MAC address = 99-99-99-99-99-99
- Source IP = 111.111.111.001
- Destination IP = 133.333.333.003

#### P22
i) from A to switch:
- Source MAC address = 00-00-00-00-00-00
- Destination MAC address = 55-55-55-55-55-55
- Source IP = 111.111.111.001
- Destination IP = 133.333.333.003

ii) from switch to right router:
- Source MAC address = 00-00-00-00-00-00
- Destination MAC address = 55-55-55-55-55-55
- Source IP = 111.111.111.001
- Destination IP = 133.333.333.003

iii) from right router to F
- Source MAC address = 88-88-88-88-88-88
- Destination MAC address = 99-99-99-99-99-99
- Source IP = 111.111.111.001
- Destination IP = 133.333.333.003

#### P23
If all the 11=9+2 nodes send out data at the maximum possible rate of 100Mbps, a total aggregate throughput of 11x100 = 1100 Mbps is possible

#### P24
If each departamental hub can have maximum throughput of 100Mbps, and the web server and mail server send out data at their maximum rate of 100Mbps each, a maximum total aggregate throughput of 500Mbps can be achieved among the 11 end systems

#### P25
All of the 11 end systems will lie in the same collision domain. The maximum total aggregate throughput of 100Mbps is possible among the 11 end systems

#### P26
***screenshot***

#### P27
- L * 8 / 128 * 10^3 sec = L/16 msec
- 93.75 msec and 3.125 msec
- 19.4 usec and < 1 usec
- Store and forward delay is too small, but packetization delay for L=1500 is too large for real-time voice applications

#### P28
- The IP addresses for those 3 computers in EE department are: 111.111.1.1, 111.111.1.2, 111.111.1.3, the subnet mask is 111.111.1/24
- The IP addresses for those 3 computers in CS department are: 111.111.2.1, 111.111.2.2, 111.111.2.3, the subnet mask is 111.111.2/24

#### P29
***screenshot***

#### P30
***screenshot***

#### P31
- Computer uses DHCP to obtain IP address
- IP datagram destined to 255.255.255.255 in the DHCP server discovery step, puts it in an Ethernet frame and broadcast it in the Ethernet
- Computer obtains IP address with a given lease time
- DHCP server also gives your computer a list of IP addresses of first-hop routers, the subnet mask and the addresses of local DNS servers (if any)
- Use ARP protocol to get the MAC addresses of the first-hop router and the local DNS server
- Computer will get the IP address of the page you want to download, it will use the DNS protocol to find it
- Once the IP address is found an HTTP request via the first-hop router, it will be segmented into TCP packets, and then into IP packets and finally into Ethernet frames
- Once router receives the frames, they are passed to the IP layer
- IP packets are routed through the internet until they reach the web server
- The web server will send the webpage to your computer via HTTP response messages, these are encapsulated into TCP packets and then IP packets, those IP packets follow IP routes and finally reach your first-hop router, and then the router will forward those packets to your computer by encapsulating them into Ethernet frames

#### P32
- Max rate is 125Mbps
- Max rate is 1Gbps
- Max rate is 0.5 Gbps

#### P33
- Both email and video applications uses the 4th rack for 0.1 percent of the time
- Probability that both applications need fourth rack is 0.001 x 0.001 = 10^6
- With the topology of figure 5.31 both applications will have enough intra-bandwidth as long as they don't use the 4th rack at the same time. So they will use the 4th rack for no more that 0.001% of time

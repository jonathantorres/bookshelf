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











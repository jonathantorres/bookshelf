#### P1
- Bit d1: [-1,1,-1,1,-1,1,-1,1]
- Bit d0: [1,-1,1,-1,1,-1,1,-1]

#### P2
Sender 2 output: [1,-1,1,1,1,-1,1,1];[1,-1,1,1,1,-1,1,1]

#### P3
Once it's joined to the network is connected to the internet (or the network) succesfully

#### P4
- Sender 1: (1,1,1,-1,1,-1,-1,-1)
- Sender 2: (1,-1,1,1,1,1,1,1)

#### P5
- No, the two ISP's can work in parallel over the same channel, but the two ISP's will be sharing the same wireless bandwidth
- Same but there will be no collisions

#### P6
Fairness was the rationale behind the design choice

#### P7
The time required is (8256 bits) / (11Mbps) = 751

#### P8
- 1 message / 2 slots
- 2 messages / slot
- 1 message / slot
- i) 1 message / slot
- ii) 2 messages / slot
- iii) 2 messages / slot
- i) 1 message / 4 slots
- ii) slot 1: message A->B, message D->C, slot 2: Ack B->A, slot 3: Ack C->D = 2 messages / 3 slots
- iii) slot 1: Message C->D, slot 2: Ack D->C, message A->B, slot 3: Ack B->A = 2 messahes / 3 slots

#### P9
It sets the power management bit in the header of the frame to 1, a timer in the node is then set to wake up the node just before the AP is scheduled to send it's beacon frame

#### P10
- The maximum rate is 10Mbps
- Average transmission rate is 2.35Mbps
- Average transmission rate is 2.78Mbps

#### P11
- No, since the Distance Vector Algorithm is decentralized and takes some time to terminate
- Yes, this could happen when one node has left a foreign network and joined a new foreign network
- The time it takes for a router to learn a path to the mobile node depends on the number of hops between the router and the edge router of the foreign network for the node

#### P12
![problem12](https://github.com/jonathantorres/cn/blob/master/ch6/img/p12.jpg)

#### P13
Because datagrams must be first forwarded to the home agent, and from there to the mobile agent, the delays will generally be longer than via direct routing

#### P14
- The mobile node arrives at A
- The mobile node moves to B. The foreign agent at B must notify the foreign agent at A that the mobile is no longer resident in A
- The mobile node moves to C, the agent at C notifies B that the mobile is no longer resident in B but is resident in C and has the specified COA in C
- The mobile node arrives at A, moves to B and then to C

#### P15
Yes, if the care-of-address is the address of the foreign agent, then this address would be the same

#### P16
Then the value of the MSRN must be updated in the HLR whenever the MSRN changes. The advantage of having the MSRN in the HLR is that the value can be provided quickly, without querying the VLR

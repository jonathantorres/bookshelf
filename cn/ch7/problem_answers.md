#### P1
- Blocks 1, 4, 5 and 6
- Blocks from 1 to 6
- Two video blocks, numbered 3 and 4
- It should be t1 + 3d

#### P2
- Q/(r-x) seconds
- Q/x + B-Q/x-r

#### P3
- Avg. send rate is H/2
- Playback will freeze after displaying the first frame
- q(t) = Q when t = sqrt(2QT/h) = t[p]
- At time t = T, q(t) = HT/2 = Q, so that playout begins. If there is no freezing we need q(t+T) > 0 for all t >= T
- Q = v2T/8H
- H/2T t^2 - r (t - sqrt(2QT/h)) = B

#### P4
Buffer grows at rate x-r. At time E, (x-r) x E buts are in buffer and are wasted

#### P5
Red traffic lights would work as the queueing delay while cards would be acting as the packets are moving on the link (as roads)

#### P6
- Transmission rate is (64 x .4h) Kbps
- h = 40 bytes

#### P7
- u(r[1]-t[1]) + (1-u) u(r[2] - t[2]) + (1-u)^2 u(r[3] - t[3]) + (i-u)^3 (r[4] - t[4])
- d^n = u sigma (1-u)^j (r[j] - t[j]) + (1-u)^n (r[n] - t[n])
- = 1/9 sigma x 9^j(r[j] - t[j])

#### P8
- u[1Δ[1] - d^4 | + (1-u) | Δ[2] - d^3 | + (1-u)^2 | Δ 3-d^2 |] + (1-u)^3 | Δ[4] - d^1 |
- V^u = u sigma (1-u)^j-1 | Δ[j] - d^n-j+1 | + (1-u)^n | Δ[n] - d^1 |

#### P9
- d[n] = n-1/n d[n-1] + r[n] - t[n] / n
- That delay is an average of the delays. It gives equal weight to recent delays and to old delays

#### P10
Both procedures are similar, they use the same formula, resulting in exponentially decreasing weights for past samples. The sample delay q can actually be negative

#### P11
- Packet 2 delay: 7 slots
- Packet 3 delay: 9 slots
- Packet 4 delay: 8 slots
- Packet 5 delay: 7 slots
- Packet 6 delay: 9 slots
- Packet 7 delay: 8 slots
- Packet 8 delay: > 8 slots
- Packets 3, 4, 6, 7 and 8
- Packets 3 and 6
- No packets will arrive

#### P12
![problem12](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch7/img/p12.jpg)

#### P13
- Both schemes require 25% more bandwidth
- The first scheme will be able to reconstruct the original high-quality audio encoding and the second scheme will use the low quality audio encoding
- For the first scheme, many of the original packets will be lost and audio quality will be very poor. For the second scheme every audio chunk will be available at the receiver

#### P14
- Each of the other N-1 participants sends a single audio stream of rate r bps to the initiator. The call initiator sends a total rate of (N-1) r bps, and the total rate aggregated over all participants is 2(N-1)r bps
- Each of the N-1 participants sends a single video stream of rate r bps to the initiator. The call initiator sends a total rate of (N-1) x (N-1)r bps and the total over all participants is (N-1)r + (N-1) x (N-1)r = N(N-1)r bps
- N x (N-1)r bps

#### P15
- Yes, the two packets will pass through the same socket
- Yes, Alice only needs one socket. Bob and Claire will choose different SSRC's, so Alice will be able to distinguish between the two streams

#### P16
- True
- True
- False
- False
- True
- False
- False
- True
- True
- False

#### P17
- One possible sequence is: 1, 2, 1, 3, 1, 2, 1, 3, 1, 2, 1, 3
- 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3

#### P18
![problem18](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch7/img/p18.jpg)

#### P19
![problem19](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch7/img/p19.jpg)

#### P20
![problem20](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch7/img/p20.jpg)

#### P21
![problem21](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch7/img/p21.jpg)

#### P22
Is the process of how to design a network topology (where to place routers, how to interconnect routers with links, and what capacity to assign to links) to achieve a given level of end-to-end performance

#### P23
![problem23](https://github.com/jonathantorres/bookshelf/blob/master/cn/ch7/img/p23.jpg)

#### P24
No, not at all

#### P25
- The minimal rate at which this traffic is served is W[i] R / sigma W[j]
- The maximum delay for a flow -1 bit is b[j] / W[i] R1 sigma W[j] = d(max)

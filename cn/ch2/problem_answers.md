#### P1
- true
- false
- false
- false
- true

#### P2
USER, PASS, ACCT, CWD, CDUP, SMNT, QUIT, REIN, PORT, PASV, TYPE, STRU, MODE, RETR, STOR, STOU, APPE, ALLO, REST, RNFR, RNTO, ABOR, DELE, RMD, MKD, PWD, LIST, NLST, SITE, SYST, STAT, HELP, NOOP

#### P3
- The types of messages exchanged
- The syntax of the various message types
- The semantics of the fields
- Rules for determining when and how a process sends messages and responds to messages

#### P4
- /cs453/index.html
- HTTP/1.1
- No IP address, but the hostname gaia.cs.umass.edu
- Persistent connection
- A firefox browser on a Windows computer

#### P5
- Yes. Tuesday, March 7 2008 at 12:39:45 GMT
- Saturday, December 10 2005 at 18:27:46 GMT
- 3874 bytes
- `<!doc`, yes it did, for 100 miliseconds

#### P6
- Either the server or the client, can signal the close of a persistent connection
- None
- Yes
- Probably note, I don't think TCP will allow it as part of it's data delivery guarantees

#### P7
m * N (DNS servers), if each trip to resolve the address takes 100ms, with 10 m objects. Then the total time to receive all objects is 1 second

#### P8
- 1 second
- The longest of the five connections
- Less than 1 second, once the connection is established every other request won't need time for this step

#### P9
- 3.2 seconds
- 2.6 seconds

#### P10
I would say that persisten connection would be the best option, the TCP connection is just opened once and it's reused for all the objects on the request

#### P11
- Yes it's possible, since you'll be getting a faster response time
- Probably not, but it's unlikely to happen. Bob connections will be using only 1/N part of the bandwidth

#### P12
See `p12.py`

#### P13
The control connection sends user identification information such as password, username, commands to move around folders and the commands. The data connection is used to actually transfer the files

#### P14
SMTP requires each message to be in 7-bit ASCII format, binary files and other formats are encoded in this format. HTTP has no restrictions

#### P15
- Mail Transfer Agent
- The malacious host is pp33head.com

#### P16
IMAP maintains a folder hierarchy on a remote server, so the folders and structure can be accessed from any computer

#### P17
- dele 1, retr 2, dele 2, quit
- retr 2, quit
- list, retr 1, retr 2, quit

#### P18
- Is used to query databases that host domain names or any other internet resource
- Whois.net
- ***Use the nslookup tool***
- Yes, 3 IP addresses
- ***Use the tool to find the IP***
- They can use the tool to get the public information and contact info on the adminstrator of the domain
- To make offers, if you are interested in purchasing a domain that is already taken

#### P19
- Tried with my website, it returns the A record containing the IP address of the server
- Tried with a few, most of them return several A records with different IP addresses

#### P20
The browser makes a DNS request for www.somesite.com. The DNS service makes the necessary queries to translate the name to the appropriate IP address

#### P21
Probably not, you'll have to be a network administrator with access to request logs or something like that.

#### P22
***Insert chart image***

#### P23
- n * F/u
- N * F/d{min}
- min{N * F/u, N * F/d{min}}

#### P24
- D=max{NF/u, F/u}
- D=min{F/u, N * F/u}
- D=max{F/u, N * F(U[n])}

#### P25
The host with the highest amount of other hosts connected to it

#### P26
- Yes, it's possible, that's why it's called free-riding
- Pretend that he's a different host on the other computers

#### P27
It's first successor is still 4, while the second successor would be 8

#### P28
- The successor of peer 5 is updated to 6
- The second succcessor of peer 4 is updated to 6
- The successor of 6 is set to 8 and it's second successor to 10

#### P29
It hashes a new key with those metrics, to assign the key to the specified peer

#### P30
It's possible. It would cause the distribution of data among peers to be significantly slower

#### P31
- It will fail, the client won't find the server to connect to
- Same as the previous answer. The server needs to be running first
- The client won't find the server with the port to connect to. So, same as the previous answers

#### P32
The client would work like a server, since you are binding a port to it. The port number is 12000

#### P33
Whatever chunk it needs, it uses a trading algorithms to make this decision. It sends the chunks to it's closest neighbor

#### P34
Way too many requests from each peer, it grows exponentially, so the P2P server would be under heavy loads

#### P35
Half of all messages are sent for each query. This is mitigated with DHT's "shortcuts"

#### P36
It's an easier/simpler language, and you don't have to manually manage the memory that is used on your program

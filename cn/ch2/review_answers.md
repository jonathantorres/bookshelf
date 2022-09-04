#### R1
- A client process (Web browser)
- A server process (Web server)

#### R2
The network architecture is fixed and provides a specific set of services to applications. The application architecture is designed by the application developer and dictates how the application is structured over the various end systems

#### R3
- The web or a web application
- FTP
- Email
- Telnet

#### R4
A data center is used, which houses a large number of hosts to create a powerful virtual server

#### R5
An instant messaging application

#### R6
I would say UDP, since it's more lightweight, there's no handshaking or a congestion control mechanism, but it's unreliable

#### R7
You have to decide wheter or not you want a reliable transfer protocol that is also secure, versus a protocol on which may be faster but there are no reliability guarantees

#### R8
- Email: TCP
- Web: TCP
- File Transfer: TCP
- Internet Telephony: UDP or TCP

#### R9
SSL operates at the application layer. It needs to include the SSL code in both the client and server sides of the application

#### R10
HTTP defines how Web clients request Web pages from Web servers and how servers transfer Web pages to clients. Because an HTTP server maintains no information about the clients

#### R11
Because TCP is a reliable protocol that guarantees that any data sent by a client will be received by the server, in it's entirety and in order

#### R12
Once the client sends a request to make a purchase the server would send a set-cookie header in the response with an unique id of the purchase made. The browser would use this value to retrieve the purchase, as long as it's available

#### R13
It is handled by the conditional GET. By Using the If-Modified-Since: header line in a GET request. Which sends the object only if the object has been modified since the specified date

#### R14
*Use telnet to send the request*

#### R15
It maintains state information about the authenticated user, it associates the control connection with the user account and the user's current directory

#### R16
- Alice composees and sends her email
- Alice's user agent sends the message to her mail server
- Alice's mail server, on the client side of SMTP sees the message in the queue and opens a TCP connection to Bob's mail server
- After the SMTP handshaking, the SMTP client sends Alice's message into the TCP connection
- At Bob's mail server, the server side of SMTP receives the message and it places it into Bob's mailbox

#### R17
There are 7 Received: header lines. Checked in one of my emails

#### R18
Authorization, transaction and update

#### R19
Yes, it's possible with an MX Record

#### R20
Yes, I was able to find out both the sending server and the receiving server

#### R21
Yes, as long as the rate is high enough, Bob could also become one of Alice's top uploaders

#### R22
The tracker selects peers randomly and Alice attempts to establish TCP connections with all of them

#### R23
If each peer tracks all other peers, then only 1 message is sent per query, but each peer has to keep track of N peers, with a circular DHT, each peer is aware of 2 peers, but N/2 messages are sent on average for each query

#### R24
In the mesh overlay, everything is tracked but it's not scalable. The circular DHT reduces the amount of overlay information each peer must manage, but to find the node responsible for a key all N nodes will have to forward the message arounf in a circle, N/2 messages are sent on average

#### R25
Maintaining a DHT when a peer comes and goes without warning

#### R26
TCP needs one socket for the server and one socket for each connection. The TCP server would need n+1 sockets

#### R27
So that the client can establish the TCP connection to it, that's why the server needs to run first. In the case of UDP, the server must be already running first as well

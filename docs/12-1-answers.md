# 12.1 Describe the concepts and terms associated with networking fundamentals

### Objectives

- [ ] Transmission Control Protocol (TCP) / User Datagram Protocol (UDP)
- [ ] Open Systems Interconnect (OSI) model
- [ ] POSIX API/BSD sockets
- [ ] Purpose and use of sockets
- [ ] Request For Comments (RFCs)
- [ ] Purpose of subnetting

### Answers

**Transmission Control Protocol (TCP) / User Datagram Protocol (UDP)**
> TCP is part of the IP suite operating on the transport layer. It is reliable in that it ensures data over the network arrives accurately and in the correct order. To do so a connection must first be established between the sender and receiver. It allows full-duplex communication enabling simultaneous communication between the sender and receiver. Due to its nature it can be slower than UDP. UDP is 'connectionless' and unreliable as it performs no error-checking, flow control, or retransmission of packets like TCP does. However, because of this it is very fast and capable of broadcasting to all devices on a network. This makes it good for data that doesn't have to be received perfectly every time and speed is more important.

**Open Systems Interconnect (OSI) model**
> Conceptual framework that standardizes communication over a network. It consists of 7 layers: Physical, Data-link, Network, Transport, Session, Presentation, and Application. 

**POSIX API/BSD sockets**
> BSD sockets are a part of the POSIX API developed for use on Unix-like systems to communicate over a network using IP. Utilize functions such as bind() to associate to a specific ip and port number. listen() to wait for incoming connections to prepare for the connection using accept(). Then send() and recv() functions can be used to transfer and consume data.

**Purpose and use of sockets**
> Sockets allow communication between processes on the same or different computers. They are used for networking at the transport layer to send and receive data over a network. Used for client-server communication, peer-to-peer, network services (e-mail, FTP, etc) amd real-time communications.

**Request For Comments (RFCs)**
> Publications used by the IETF and other organizations to document internet protocols, procedures, programs, and concepts. A formal document that describes a proposed standard, best practices, or experimental idea related to the internet.

**Purpose of subnetting**
> Subnetting divides a single large network into smaller sub-networks. Allows the efficient use of ip address allowing smaller blocks of addresses for each sub-net. Improves network performance as it reduces the amount of broadcast traffic. Enhances security by creating logical boundaries between different parts of the network (using ACLs and firewall rules more effectively.) Facilitates scalability by allowing a network to more easily grow as new sub-nets can be created without reconfiguring the entire entwork.

# 12.2 Describe the concepts and terms associated with common protocols and their associated ports, if applicable

### Objectives

- [ ] Simple Mail Transfer Protocol (SMTP)
- [ ] Internet Control Message Protocol (ICMP)
- [ ] Dynamic Host Configuration Protocol (DHCP)
- [ ] Internet Protocol version 4 (IPv4)
- [ ] Internet Protocol version 6 (IPV6)
- [ ] Address Resolution Protocol (ARP)
- [ ] Hypertext Transfer Protocol/Secure (HTTP/HTTPS)
- [ ] Domain Name System (DNS)


### Answers

**Simple Mail Transfer Protocol (SMTP)**
> Used for sending email messages, TCP connection on port 25 by default. Does not provide authentication/encryption on its own.

**Internet Control Message Protocol (ICMP)**
> Operates at layer 3, generally used for network management, testing connectivity. Often used to ping a device. Does not use ports.

**Dynamic Host Configuration Protocol (DHCP)**
> Automates assignment of IP addresses on a network, uses UDP port 67 on the server side and UDP port 68 on the client side typically.

**Internet Protocol version 4 (IPv4)**
>32 bit format for addressing devices for routing packets across networks. IPv4 packets header contains information
including source and destination, packet length, protocol, TTL and a checksum.

**Internet Protocol version 6 (IPV6)**
>Meant to replace IPv4; 128 bit addresses allowing for essentially limitless addresses.
Overall an improved version of IPv4 with enhanced security and other features. Has a simpler header removing the
checksum and header length fields.

**Address Resolution Protocol (ARP)**
> Maps IP addresses to physical MAC addresses. operates on layer 2. ARP spoofing allows an attacker to associate their MAC with a specified IP allowing man-in-the-middle attacks.

**Hypertext Transfer Protocol/Secure (HTTP/HTTPS)**
>Used for communication between web browsers and servers; most common http methods are GET and POST to retrieve information from and server and send information to a server. HTTPS is the secure version supporting encryption and autentication. Http uses port 80 and https port 443.

**Domain Name System (DNS)**
>Used to translate domain names such as google.com to the actual ip address for routing. DNS poisoning is an attack that changes the target ip address of a web url generally to direct a user to a malicious site. DNS typically uses port 53.

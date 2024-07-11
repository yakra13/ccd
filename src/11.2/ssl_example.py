"""
SSL socket example
- [x] Establish a secure communications channel using an SSL library
"""
import socket
import ssl

context = ssl.create_default_context()

# Create the standard socket
with socket.create_connection(('www.example.com', 443)) as sock:
    # Wrap the socket with SSL
    with context.wrap_socket(sock, server_hostname='www.example.com') as w_sock:
        print(f'Connected with {w_sock.version()} encryption')

        request = 'GET / HTTP/1.1\r\nHost: www.example.com\r\nConnection: close\r\n\r\n'
        w_sock.sendall(request.encode('utf-8'))

        response = b''
        while True:
            data = w_sock.recv(4096)
            if not data:
                break
            response += data

        print(response.decode('utf-8'))

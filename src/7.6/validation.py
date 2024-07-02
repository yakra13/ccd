"""7.6 Demonstrate the ability to perform data validation

Objectives

- [x] Validating received input matches expected input
- [x] Designing and implementing a scheme for exception handling
"""
import socket
import sys

# - [ ] Validating received input matches expected input
# - [ ] Designing and implementing a scheme for exception handling
class IPv4():
    """Class to store IPv4 data and methods."""
    def __init__(self, address:str, port: int) -> None:
        # The setters are called by python here.
        self.address = address
        self.port = port

    @property
    def address(self) -> bytes:
        """address getter"""
        return self.__address

    @property
    def port(self) -> int:
        """port getter"""
        return self.__port

    @address.setter
    def address(self, value):
        """address setter"""
        try:
            self.__address = socket.inet_aton(value)
        except socket.error as exc:
            print('Invalid ip address')
            raise OSError(f'{value} is not a valid ip address.') from exc

    @port.setter
    def port(self, value):
        """port setter"""
        if not isinstance(value, int):
            try:
                value = int(value)
            except:
                print('Port is not an int.')
                raise ValueError(value, type(value))
        if value < 0 or value > 65535:
            print('Port is out of range.')
            raise ValueError(value)

        self.__port = value


def main() -> None:
    """Entry point"""
    ip: IPv4 = IPv4(sys.argv[1], sys.argv[2])
    print("ip =>", socket.inet_ntoa(ip.address))
    print("port =>", ip.port)

if __name__ == '__main__':
    main()

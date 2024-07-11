"""13.2 Demonstrate the ability to handle partial reads and writes during
serialization and de-serialization

Objectives

- N/A
"""
from typing import Tuple

class SerializableObject:
    """Sample object for demonstration."""
    def __init__(self, string_data: str, int_data: int):
        self.string_data  = string_data
        self.int_data     = int_data

    def __str__(self) -> str:
        return f'\tstring_data: {self.string_data}\n\tint_data: {self.int_data}'

    def to_bytes(self) -> bytes:
        """Converts this object to bytes."""
        name_bytes: bytes        = self.string_data.encode('utf-8')

        name_length_bytes: bytes = len(name_bytes).to_bytes(4, byteorder='big')

        value_bytes: bytes       = self.int_data.to_bytes(4, byteorder='big')

        return name_length_bytes + name_bytes + value_bytes
    
def consume_bytes(count: int, bytes_data: bytes) -> Tuple[bytes, bytes]:
    """Return a tuple containing the first count bytes and the remaining bytes.
    
    Args:
        count: The count of bytes to consume
        bytes_data: The bytes to split
    
    Returns:
        Tuple containing the consumed bytes and remaining bytes
    """
    # If there are fewer bytes remaining than count return the remaining bytes
    count = min(count, len(bytes_data))
    
    consumed = bytes_data[:count]

    remaining = bytes_data[count:]

    return consumed, remaining

def from_bytes(bytes_data: bytes) -> SerializableObject:
    """Converts byte data into SerializableObject
    
    Args:
        bytes_data: data to serialize into SerializableObject
    
    Returns:
        SerializableObject
    """
    b, bytes_data = consume_bytes(4, bytes_data)
    name_length: int = int.from_bytes(b, byteorder='big')

    b, bytes_data = consume_bytes(name_length, bytes_data)
    name: str = b.decode('utf-8')

    b, bytes_data = consume_bytes(4, bytes_data)
    value: int = int.from_bytes(b, byteorder='big')

    return SerializableObject(name, value)

def serialize_to_file(obj: SerializableObject, file_name: str, chunk_size: int=8):
    """Serialize an object to file chunk_size bytes at a time.
    
    Args:
        obj: SerializableObject to serialize
        chunk_size: number of bytes to serialize at a time
    """
    serialized_data = obj.to_bytes()

    with open(file_name, 'wb') as f:
        for i in range(0, len(serialized_data), chunk_size):
            f.write(serialized_data[i:i + chunk_size])

def deserialize_from_file(file_name: str, chunk_size=8) -> SerializableObject:
    """Deserialize data in specified file chunk_size bytes at a time.

    Args:
        file_name: file to deserialize
        chunk_size: number of bytes to deserialize at a time
    
    Returns:
        SerializableObject
    """
    serialized_data = b''

    with open(file_name, 'rb') as f:
        while True:
            chunk = f.read(chunk_size)
            if not chunk:
                break

            serialized_data += chunk

    return from_bytes(serialized_data)

if __name__ == '__main__':
    data = SerializableObject(string_data='some test string data to serialize',
                              int_data=45378)

    serialize_to_file(data, 'data_file.dat')

    deserialized_data = deserialize_from_file('data_file.dat')

    print(f'Original Object:\n{data}')

    print(f'Serialized Object:')

    with open('data_file.dat', 'rb') as f:
        print('\t', ' '.join(f'{b:02x}' for b in f.read()))

    print(f'Deserialized Object:\n{deserialized_data}')

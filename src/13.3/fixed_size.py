"""13.3 Demonstrate the ability to serialize fixed size multi-byte
types between systems of differing endianness

Objectives
- N/A
"""
import struct
import time
from datetime import datetime
from enum import Enum, auto
from typing import Any, Final

UINT16_MAX: Final[int] = 65535

class ByteEnum(Enum):
    """Base enum class to use when assigning byte values."""
    @staticmethod
    def _generate_next_value_(name: str, start: int, count: int, last_values: list[Any]) -> bytes:
        last_value = last_values[-1] if last_values else start
        return bytes([last_value[0] + 1])

class Singleton(object):
    """Base singleton class."""
    def __new__(cls):
        if not hasattr(cls, 'instance'):
            cls.instance = super(Singleton, cls).__new__(cls)
        return cls.instance

class MessageType(ByteEnum):
    """Enum of valid message types to handle. Start 0x80"""
    REQ_CREATE_USER: Final[bytes]    = b'\x80'
    REQ_DISCONNECT: Final[bytes]     = auto()
    REQ_LOGIN: Final[bytes]          = auto()
    REQ_LOGOUT: Final[bytes]         = auto()
    REQ_SAY: Final[bytes]            = auto()
    REQ_WHISPER: Final[bytes]        = auto()

class Message():
    """Stores the contents of a parsed message."""
    TYPE_FLD_LEN: Final[int] = 1 # Number of bytes in uint8
    SIZE_FLD_LEN: Final[int] = 2 # Number of bytes in uint16
    TIME_FLD_LEN: Final[int] = 8 # Number of bytes in double
    ID_FLD_LEN: Final[int]   = 2 # Number of bytes in uint16

    HEADER_LEN: Final[int]   = TYPE_FLD_LEN + SIZE_FLD_LEN + TIME_FLD_LEN + ID_FLD_LEN

    def __init__(self,
                 message_type: MessageType,
                 timestamp: float,
                 message_id: int,
                 fields: list[str],
                 length: int = None) -> None:

        self.message_type: MessageType = message_type
        self.message_id: int           = message_id
        self.timestamp: float          = timestamp
        self.fields: list[str]         = fields

        # When creating a Message directly leave the length None to
        # let the Message calculate its own size
        self.message_length: int = 0
        if length is None:
            self.message_length = self._get_total_length()
        else:
            self.message_length = length

    def __str__(self) -> str:
        field_strings: str = ''
        for fs in self.fields:
            field_strings += f'\t{fs}\n'

        return f'Type: {self.message_type}\n' \
               f'Size: {self.message_length}\n' \
               f'Time: {datetime.fromtimestamp(self.timestamp)}\n'\
               f'ID: {self.message_id}\n' \
               f'Fields:\n{field_strings}'

    def _get_total_length(self) -> int:
        """Return the total size of the message in bytes."""
        fields_length: int = 0
        for str_field in self.fields:
            # Count the null terminator
            fields_length += len(str_field) + 1

        return self.HEADER_LEN + fields_length

class MessageBuilder(Singleton):
    """Network message builder."""
    # Used to generate a message id
    _message_counter: int = 0


    @classmethod
    def as_bytes(cls, message_type: MessageType) -> bytes:
        """Returns the byte value of a message type."""
        return int.from_bytes(message_type.value, 'little')

    @classmethod
    def serialize_message(cls, message: Message) -> bytes:
        """Constructs bytes based on message type provided.
        
        Args:
            message_type: MessageId describing how the message should be handled.
            *args: Variable length of strings to append to the message.

        Raises:
            ValueError if any message is too long.

        Returns:
            Formatted bytes.
        """
        total_length: int = message.message_length

        # Max byte count for a message 65535
        if total_length > UINT16_MAX:
            raise ValueError('Message is too large.')

        # Build the header: type, length, timestamp, id
        b: bytearray = bytearray()
        b.append(cls.as_bytes(message.message_type))
        b.extend(total_length.to_bytes(Message.SIZE_FLD_LEN, byteorder='big', signed=False))
        b.extend(struct.pack('d', message.timestamp))
        b.extend(message.message_id.to_bytes(Message.ID_FLD_LEN, byteorder='big', signed=False))

        # Increment message counter and mask to a uint16
        cls._message_counter = (cls._message_counter + 1) & UINT16_MAX

        # Process string fields
        for f in message.fields:
            b.extend(f.encode('utf-8'))
            # Append null terminator
            b.append(int.from_bytes(b'\x00', 'big'))

        return bytes(b)

    @classmethod
    def deserialize_message(cls, data_bytes: bytes) -> Message:
        """Deserialize message bytes.

        Args:
            data: The bytes to deserialize.

        Returns:
            Message object.
        """
        # Parse the message type
        message_type: MessageType = MessageType(data_bytes[:Message.TYPE_FLD_LEN])
        # Remove the message id bytes
        data_bytes = data_bytes[Message.TYPE_FLD_LEN:]
        # Parse the message length
        message_len = data_bytes[:Message.SIZE_FLD_LEN]
        message_len = int.from_bytes(message_len, 'big')
        # Remove the message length bytes
        data_bytes = data_bytes[Message.SIZE_FLD_LEN:]
        #Parse the time sent bytes
        message_timestamp = data_bytes[:Message.TIME_FLD_LEN]
        message_timestamp = struct.unpack('d', message_timestamp)[0]
        # Remove the time sent bytes
        data_bytes = data_bytes[Message.TIME_FLD_LEN:]
        # Parse the id bytes
        message_id = data_bytes[:Message.ID_FLD_LEN]
        # Remove the id bytes
        data_bytes = data_bytes[Message.ID_FLD_LEN:]
        # Store the parsed strings
        message_fields: list[str] = []

        # Get how many bytes SHOULD be remaining based on the message length field
        bytes_left = message_len - Message.HEADER_LEN
        # Decode the bytes into strings separated by null bytes
        string: bytearray = bytearray()

        for _, b in enumerate(data_bytes):
            bytes_left -= 1
            if b == 0x00:
                if len(string) > 0:
                    message_fields.append(string.decode('utf-8'))
                    string.clear()
            else:
                string.append(b)

        return Message(message_type,
                        message_timestamp,
                        message_id,
                        message_fields,
                        message_len)


if __name__ == '__main__':
    # String fields to populate the message
    # The number and length of fields is variable
    # There is an upper limit of 65535 bytes per message to simulate restricted
    # network message size for efficiency/buffer overflow protection
    strings: list[str] = [
        'Username',
        'Password'
    ]

    # Create the message object
    serialize_message: Message = Message(MessageType.REQ_CREATE_USER,
                                    time.time(),
                                    0xABCD,
                                    strings)
    print(serialize_message)

    # Serialize the message into bytes
    data: bytes = MessageBuilder.serialize_message(serialize_message)

    print(f'Serialized bytes:\n {data.hex(" ")}\n')

    # Deserialize the bytes into a message object
    deserialize_msg: Message = MessageBuilder.deserialize_message(data)

    print(deserialize_msg)

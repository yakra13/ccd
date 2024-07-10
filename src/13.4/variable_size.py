"""13.4 Demonstrate the ability to serialize and de-serialize variable
sized data structures between systems of differing endianness

Objectives
- N/A
"""
import struct
import time
from enum import Enum, auto
from typing import Any, Final, Iterator

BUFFER_MIN: Final[int] = 4
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
    # Client -> Server
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
                 length: int,
                 message_id: int,
                 fields: list[str]) -> None:

        self.message_type: MessageType  = message_type
        self._message_length: int        = length
        self.message_id: int            = message_id
        self.timestamp: float   = time.time()
        self._fields: list[str] = fields

    def get_total_length(self) -> int:
        """Return the total size of the message in bytes."""
        fields_length: int = 0
        for f in self._fields:
            # Count the null terminator
            fields_length += len(f) + 1

        return self.HEADER_LEN + fields_length

    def get_next_field(self) -> Iterator[str]:
        """Consumes the next field string.
        
        Calls to this function should be wrapped in try except block.
        
        Raises:
            IndexError: When iteration continues beyond the total fields
        
        Returns:
            Each field string.
        """
        for f in self._fields:
            try:
                yield f
            except StopIteration as exc:
                raise IndexError(self.message_type, 'Not enough fields in message.') from exc

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
        total_length: int = message.get_total_length()

        # Pad the message to a multiple of BUFFER_MIN
        padding = BUFFER_MIN - (total_length % BUFFER_MIN)
        total_length += padding

        # Max byte count for a message 65535
        if total_length > UINT16_MAX:
            raise ValueError('Message is too large.')

        # Build the header: type, length, timestamp, id
        b: bytearray = bytearray()
        b.append(cls.as_bytes(message.message_type))
        b.extend(total_length.to_bytes(Message.SIZE_FLD_LEN, byteorder='big', signed=False))
        b.extend(struct.pack('d', message.timestamp))
        b.extend(cls._message_counter.to_bytes(Message.ID_FLD_LEN, byteorder='big', signed=False))

        # Increment message counter and mask to a uint16
        cls._message_counter = (cls._message_counter + 1) & UINT16_MAX

        # Append the data with null terminators
        for f in message.get_next_field():
            b.extend(arg.encode('utf-8'))
            b.append(int.from_bytes(b'\x00', 'big'))
        # Add the padding
        for _ in range(0, padding):
            b.append(int.from_bytes(b'\x00', 'big'))
        print('returning bytes from build message')
        print(b.hex())
        print(bytes(b).hex())
        return bytes(b)
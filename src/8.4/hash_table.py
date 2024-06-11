from collections import deque
from collections.abc import Hashable
from typing import Any, Final, NamedTuple, Tuple

MIN_HASH_TBL_CAP: Final[int] = 10

class Pair(NamedTuple):
    key: Hashable
    value: Any

class HashTable():
    """"""
    def __init__(self,
                 capacity: int = MIN_HASH_TBL_CAP,
                 lf_threshold: float = 0.6) -> None:
        if capacity < MIN_HASH_TBL_CAP:
            capacity = MIN_HASH_TBL_CAP
        if not 0 < lf_threshold <= 1:
            lf_threshold = 0.6
        self._keys: list[Hashable] = []
        self._buckets: deque       = [deque() for _ in range(capacity)]
        self._lf_threshold: float  = lf_threshold

    def __len__(self):
        return len(self.pairs)

    def __iter__(self):
        yield from self.keys

    #NOTE: Removing selected items from a hash table
    def __delitem__(self, key: Hashable):
        match self._find(key):
            case bucket, index, _:
                del bucket[index]
                self._keys.remove(key)
            case _:
                raise KeyError(key)

    #NOTE: Implement functionality to mitigate hash collisions within the hash table
    #NOTE: Inserting an item into a hash table
    def __setitem__(self, key: Hashable, value: Any):
        if self.load_factor >= self._lf_threshold:
            self._resize_and_rehash()

        match self._find(key):
            case deque() as bucket, index, (key, _):
                bucket[index] = Pair(key, value)
            case bucket:
                bucket.append(Pair(key, value))
                self._keys.append(key)

    #NOTE:  Finding an item in a hash table
    def __getitem__(self, key: Hashable):
        match self._find(key):
            case _, _, pair:
                return pair.value
            case _:
                raise KeyError(key)

    def __contains__(self, key: Hashable):
        try:
            self[key]
        except KeyError:
            return False

        return True

    def __eq__(self, other: 'HashTable'):
        if self is other:
            return True

        if type(self) is not type(other):
            return False

        return set(self.pairs) == set(other.pairs)

    def __str__(self):
        pairs = []
        for key, value in self.pairs:
            pairs.append(f'{key!r}: {value!r}')
        s = ', '.join(pairs)
        return f'{{ {s} }}'

    def __repr__(self):
        cls = self.__class__.__name__
        return f'{cls}.from_dict({str(self)})'

    @property
    def buckets(self) -> deque:
        """Should only be used internally.
        Probably a better way to do this.
        """
        return self._buckets

    @property
    def capacity(self) -> int:
        """Return the current capacity of the hash table."""
        return len(self._buckets)

    @property
    def keys(self) -> list[Hashable]:
        """Returns a list of keys in the hash table."""
        return self._keys.copy()

    @property
    def load_factor(self) -> float:
        """Returns a float represent how full the hash table is."""
        return len(self) / self.capacity

    @property
    def pairs(self) -> list[Tuple[Hashable, Any]]:
        """Returns a list of key, value pairs in the hash table."""
        return [(key, self[key]) for key in self.keys]

    @property
    def values(self) -> list[Any]:
        """Returns a list containing the hash table values."""
        return [self[key] for key in self.keys]

    #NOTE: Creating a hash table with n number of items
    @classmethod
    def from_dict(cls, dictionary: dict, capacity: int | None = None) -> 'HashTable':
        """Converts a dict to a HashTable."""
        hash_table = cls(capacity or len(dictionary))
        for key, value in dictionary.items():
            hash_table[key] = value
        return hash_table

    def _find(self, key) -> Any | Tuple[Any, int, Pair]:
        bucket = self._buckets[self._index(key)]
        for index, pair in enumerate(bucket):
            if pair.key == key:
                return bucket, index, pair
        return bucket

    def _index(self, key) -> int:
        return hash(key) % self.capacity

    def _resize_and_rehash(self):
        copy = HashTable(capacity=self.capacity * 2)
        for key, value in self.pairs:
            copy[key] = value
        self._buckets = copy.buckets

    def clear(self):
        """Empty the hash table."""
        #TODO
        self._keys.clear()
        self._buckets.clear()

    #NOTE: Removing all items from the hash table
    def copy(self):
        """Returns a copy of the hash table."""
        return HashTable.from_dict(dict(self.pairs), self.capacity)

    def get(self, key: Hashable, default: Any = None) -> Any:
        """Gets the value from the associated key."""
        try:
            return self[key]
        except KeyError:
            return default

    #NOTE: Navigating through a hash table to find the nth item
    # I don't think this really makes sense but its an objective.
    def get_by_index(self, index: int, default: Any = None) -> Any:
        """Returns the value associated with the key at index."""
        if 0 > index > len(self.keys):
            raise IndexError()
        return self.get(self.keys[index], default)

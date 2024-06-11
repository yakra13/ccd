"""7.2 Demonstrate the proper declaration and use of Python data
   types and object-oriented constructs

    Objectives

    - [x] List (list)
    - [x] Multi-dimensional list
    - [x] String (str)
    - [x] Integer (int)
    - [x] Float (float)
    - [x] Dictionary (dict)
    - [x] Tuple (tuple)
    - [x] Singleton
"""
from typing import List

# [ ] List (list)
# [ ] String (str)
def objective_list() -> List[str]:
    """Returns a single dimension list of strings, a thru z."""
    l: List[str] = []
    # Fill the list with the alphabet.
    for i in range(ord('a'), ord('z') + 1):
        l.append(chr(i))

    return l

# [ ] Multi-dimensional list
# [ ] Integer (int)
def objective_multi_dimensional_list() -> List[List[int]]:
    """Returns a multi-dimensional list. A list of lists."""
    ml: List[List[int]] = []

    w: int = 5
    h: int = 5

    for y in range(0, h):
        # Append an empty list to multi list
        ml.append([])
        for x in range (0, w):
            # Fill the new list with some ints
            ml[y].append(x * y)

    return ml

# [ ] Float (float)
# [ ] Dictionary (dict)
# [ ] Tuple (tuple)
def objective_dictionary_tuple() -> dict[float, tuple]:
    """Dictionary, tuple and float example."""
    d: dict[float, tuple] = {}
    # Fill the dictionary with keys and values
    for x in [0.1, 0.5]:
        for y in range(0, 4):
            d[y + x] = (y, x)

    return d

# [ ] Singleton
class ObjectiveSingleton(object):
    """Singleton example."""
    # Use a global class variable to store the first instance of this class that is created
    _instance = None

    # Override __new__ to intercept the creation of the class object
    def __new__(cls):
        # If the instance of the class doesn't exist create one.
        # If it does exists return a reference to the single instance.
        if cls._instance is None:
            cls._instance = super(ObjectiveSingleton, cls).__new__(cls)
        return cls._instance


def main() -> None:
    """Entry point."""

    # List / string example
    list_ex: List[str] = objective_list()
    print('List of strings:\n', list_ex)

    # Multi-dimensional list / int example
    multi_list_ex: List[List[int]] = objective_multi_dimensional_list()
    print('\nMulti-dimensional list:')
    for row in multi_list_ex:
        for col in row:
            print(f"{col:>5}", end='')
        print('\n')

    # Dictionary / tuple / float example
    dictionary_ex: dict[float, tuple] = objective_dictionary_tuple()
    print('\nDictionary of tuples with float keys:\n   KEY : VALUE')
    for k, v in dictionary_ex.items():
        print(f'   {k} : {v}')

    # Singleton example
    singleton1: ObjectiveSingleton = ObjectiveSingleton()
    print('\nPrint singleton1:', singleton1)
    singleton2: ObjectiveSingleton = ObjectiveSingleton()
    print('Print singleton2:', singleton2)

    if singleton1 is singleton2:
        print('They are the same thus it is a singleton.')
    else:
        print('They are not the same thus not a singleton.')

if __name__ == "__main__":
    main()

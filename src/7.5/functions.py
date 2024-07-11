"""7.5 Demonstrate the ability to create and implement functions to meet a requirement

Objectives

- [x] A function that returns multiple values
- [x] A function that receives input from a user
- [x] A recursive function
"""

from typing import Tuple

# - [ ] A function that returns multiple values
def return_multiple_values(string1: str, string2: str) -> Tuple[str, int]:
    """Returns a string, int tuple."""
    concat: str = string1 + string2
    return concat, len(concat)

# - [ ] A function that receives input from a user
def get_input() -> None:
    """Gets user input."""
    user_input = input('Type something: ')
    print(f'You typed \'{user_input}\'.')

# - [ ] A recursive function
def recursive_function(fact: int) -> int:
    """A recursive factorial function."""
    if fact > 5 or fact <= 0:
        # factorials get really big and I'm just avoiding it for the example.
        # and 0! = 1
        return 1

    return fact * recursive_function(fact - 1)

def main() -> None:
    """Entry point."""
    print(f'Return multiple values: {return_multiple_values("First string", "second string")}')

    get_input()

    print(f'4! = {recursive_function(4)}')

if __name__ == '__main__':
    main()

"""8.5 Demonstrate skill in creating and using a stack that accepts any data type
Objectives
- [x] Removing all items from the stack
- [x] Create a stack (cannot be fixed sized)
- [x] Adding an item in a stack (enforce FILO)
- [x] Removing n items from a stack
- [x] Destroying a stack
- [x] Preventing a stack overrun
"""
import sys
from typing import Any, List


class Stack(object):
    """Built in list has all methods to function as a stack.
    This class acts as a wrapper around a list to prevent direct calls to
    non-stack like functions on the list.
    """
    def __init__(self) -> None:
        self._stack = []

    def __repr__(self) -> str:
        return f'stack={self._stack}'

    def size(self) -> int:
        """Returns the number of items in the stack"""
        return len(self._stack)

    def peek(self) -> Any:
        """Returns that value of the top of the stack without removing it"""
        if len(self._stack) < 1:
            raise IndexError('Error: Attempt to peek an empty stack.')
        return self._stack[-1]

    # - [ ] Adding an item in a stack (enforce FILO)
    def push(self, element: Any = None) -> None:
        """Pushes an element to the top of the stack"""
        if element is None:
            return
        # - [ ] Preventing a stack overrun
        if len(self._stack) == sys.maxsize:
            raise IndexError('Unlikely, unless the running machine has little memory.')
        self._stack.append(element)

    # - [ ] Removing n items from a stack
    def pop_list(self, count:int = 1) -> List[Any]:
        """Removes up to n elements from the stack and returns as a list."""
        if count <= 0:
            return []
        result = []
        for _ in range(0, count - 1):
            if len(self._stack) == 0:
                break
            result.append(self.pop())
        return result

    def pop(self) -> Any:
        """Removes the top element at returns it"""
        if len(self._stack) < 1:
            raise IndexError('Error: Attempt to pop from empty stack.')
        return self._stack.pop()

    # - [ ] Removing all items from the stack
    def empty(self) -> None:
        """Remove all elements from the stack"""
        self._stack.clear()

if __name__ == '__main__':
    # - [ ] Create a stack (cannot be fixed sized)
    s = Stack()
    # s.peek()
    # ret = s.pop()
    s.push()
    # print(ret)

    s.push(1)
    s.push(2)
    s.push(3)
    print(s)
    print('Peek:', s.peek())
    print(s)
    print('Popped:', s.pop())
    print(s)
    print('Stack size:', s.size())
    print('Empty stack')
    s.empty()
    print(s)
    # - [ ] Destroying a stack
    del s

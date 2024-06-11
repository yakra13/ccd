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
from functools import wraps
from typing import Any, List

def is_stack_initialized(func):
    """Decorator to check stack initialization.
    
    Used to decorate any Stack function that utilizes _stack attribute.
    """
    @wraps(func)
    def wrapper(*args):
        try:
            return func(*args)
        except AttributeError:
            print('ERROR: stack not initialized.')
            return None

    return wrapper

class Stack():
    """Built in list has all methods to function as a stack.
    This class acts as a wrapper around a list to prevent direct calls to
    non-stack like functions on the list.
    """
    def __init__(self) -> None:
        self._stack = []

    def __repr__(self) -> str:
        if hasattr(self, '_stack'):
            return f'stack={self._stack}'
        return 'PRINT: stack not initialized.'

    def re_init(self) -> None:
        """Re-initializes a destroyed stack."""
        if not hasattr(self, '_stack'):
            self._stack = []

    # - [ ] Destroying a stack
    @is_stack_initialized
    def destroy(self) -> None:
        """Destroys the stack."""
        del self._stack

    @is_stack_initialized
    def size(self) -> int:
        """Returns the number of items in the stack"""
        return len(self._stack)

    @is_stack_initialized
    def peek(self) -> Any:
        """Returns that value of the top of the stack without removing it"""
        if len(self._stack) < 1:
            raise IndexError('Error: Attempt to peek an empty stack.')
        return self._stack[-1]

    # - [ ] Adding an item in a stack (enforce FILO)
    @is_stack_initialized
    def push(self, element: Any = None) -> None:
        """Pushes an element to the top of the stack"""
        if element is None:
            return
        # - [ ] Preventing a stack overrun
        if len(self._stack) == sys.maxsize:
            raise IndexError('Unlikely, unless the running machine has little memory.')
        self._stack.append(element)

    # - [ ] Removing n items from a stack
    @is_stack_initialized
    def pop_list(self, count:int = 1) -> List[Any]:
        """Removes up to n elements from the stack and returns as a list."""
        if count <= 0:
            return []
        result = []
        for _ in range(0, count):
            if len(self._stack) == 0:
                break
            result.append(self.pop())
        return result

    @is_stack_initialized
    def pop(self) -> Any:
        """Removes the top element at returns it"""
        if len(self._stack) < 1:
            raise IndexError('Error: Attempt to pop from empty stack.')
        return self._stack.pop()

    # - [ ] Removing all items from the stack
    @is_stack_initialized
    def empty(self) -> None:
        """Remove all elements from the stack"""
        self._stack.clear()


if __name__ == '__main__':
    # - [ ] Create a stack (cannot be fixed sized)
    s = Stack()
    s.push()
    s.push(1)
    print(s)
    print('Peek:', s.peek())
    print('Popped:', s.pop())
    print(s)

    print('Destroy stack')
    s.destroy()
    s.push(1)
    print(s)

    print('Re-initialize stack')
    s.re_init()

    print('Push 3 items')
    s.push(2)
    s.push(3)
    s.push(4)
    print(s)
    print('Stack size:', s.size())
    print('Pop 2 items:', s.pop_list(2))
    print(s)
    print('Empty the stack')
    s.empty()
    print(s)

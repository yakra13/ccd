"""8.6 Demonstrate skill in implementing a priority queue that accepts any data type
Objectives
- [x] Defining the underlying structures required for priority queues (cannot be fixed sized)
- [x] Assigning a priority to each element
- [x] Inserting an element into the priority queue
- [x] Removing the element with the highest priority from the priority queue
- [x] Destroying a priority queue
- [x] Define possible applications of a priority queue
"""

from typing import Any

# - [ ] Assigning a priority to each element
class PQElement:
    """Priority Queue Element"""
    def __init__(self, value: Any, priority: int = 0) -> None:
        self.value: Any = value
        self.priority: int = priority

# - [ ] Defining the underlying structures required for priority queues (cannot be fixed sized)
class PriorityQueue:
    """Priroty queue class"""
    def __init__(self) -> None:
        self._queue: list[PQElement] = []

    # - [ ] Inserting an element into the priority queue
    def enqueue(self, value: Any, priority: int):
        """Adds an element to the queue
        
        Prioritization takes place here. It could instead be done in dequeue.
        Doing it this way allows dequeue to simply pop index 0 from the list instead
        of searching the whole list to find the highest priority item.

        When enqueueing we only need to find the first index with a lower priority
        and then insert before that index.
        """
        size = len(self._queue)
        if size == 0:
            self._queue.append(PQElement(value, priority))
            return

        i = 0
        while i < size:
            if self._queue[i].priority <= priority:
                break
            i += 1

        self._queue.insert(i, PQElement(value, priority))

    # - [ ] Removing the element with the highest priority from the priority queue
    def dequeue(self) -> PQElement | None:
        """Removes the highest priority item.
        This should always be index 0 as long as enqueue() is used to add items.
        """
        if len(self._queue) > 0:
            return self._queue.pop(0)
        return None

    def peek(self) -> PQElement | None:
        """Returns highest priority item without removing it from the queue."""
        if len(self._queue) > 0:
            return self._queue[0]
        return None

    def print_queue(self):
        """Print the priority queue in highest to lowest priority."""
        for e in self._queue:
            print(f'{e.value} | {e.priority}')

if __name__ == '__main__':
    pq = PriorityQueue()
    print('Enqueueing items (value, priority):(3, 3), (4, 4), (1, 1), (3, 4), (5, 5)')
    pq.enqueue(3, 3)
    pq.enqueue(4, 4)
    pq.enqueue(1, 1)
    pq.enqueue(3, 4)
    pq.enqueue(5, 5)
    print('Printing priority queue, in priority order')
    pq.print_queue()
    print('Dequeueing highest priority item')
    dequeued_item = pq.dequeue()
    print(f'Dequeued: ({dequeued_item.value}, {dequeued_item.priority})')
    print('Printing priority queue, in priority order')
    pq.print_queue()

    # - [ ] Destroying a priority queue
    del pq


# - [ ] Define possible applications of a priority queue
# Shortest path algorithms  like A* can utilize a priority queue to give priority to weighted
# path nodes. Can also be used to execute tasks based on importance or even prioritize system
# resources to specified users/processes based on importance or criticality.

"""9.3 Demonstrate the ability to analyze sorting routines to determine the most efficient one to use,
using an approximation of Big-O notation

Objectives
- [ ] Merge sort
- [ ] Selection sort
- [ ] Insertion sort
- [ ] Hashing
- [ ] Heap sort
- [ ] Quick sort
"""
import random
import timeit
from typing import List

SAMPLE_SIZE = 1000
MIN_RANDOM = -1000
MAX_RANDOM =  1000

def merge_sort(input: List[int]) -> List[int]:
    """"""
    pass

def selection_sort(input: List[int]) -> List[int]:
    """"""

def insertion_sort(input: List[int]) -> List[int]:
    """"""

def hashing(input: List[int]) -> List[int]:
    """"""

def heap_sort(input: List[int]) -> List[int]:
    """"""

def quick_sort(input: List[int]) -> List[int]:
    """"""

if __name__ == '__main__':
    rand_list = random.sample(range(MIN_RANDOM, MAX_RANDOM), SAMPLE_SIZE)
    print(rand_list)

    timeit.timeit('merge_sort()', number=1000, globals=)
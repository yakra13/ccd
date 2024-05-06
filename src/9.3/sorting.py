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
import functools

ARRAY_SIZE: int = 100
MIN_RANDOM: int = -1000
MAX_RANDOM: int =  1000
RUN_COUNT: int = 1000
RAND_LIST: List[int] = random.sample(range(MIN_RANDOM, MAX_RANDOM), ARRAY_SIZE)

def _merge(arr1: List[int], arr2: List[int]) -> List[int]:
        """"""
        i = 0
        j = 0
        result = []

        while i < len(arr1) and j < len(arr2):
            if arr2[j] > arr1[i]:
                result.append(arr1[i])
                i += 1
            else:
                result.append(arr2[j])
                j += 1
        while i <len(arr1):
            result.append(arr1[i])
            i += 1
        while j < len(arr2):
            result.append(arr2[j])
            j += 1
        
        return result

def merge_sort(arr: List[int]) -> List[int]:
    """"""
    if len(arr) <= 1:
        return arr
    
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    
    return _merge(left, right)

def selection_sort(arr: List[int]) -> List[int]:
    """"""
    for i in range(len(arr) - 1):
        min_idx = i
        for j in range(i + 1, len(arr)):
            if arr[min_idx] > arr[j]:
                min_idx = j
                       
        arr[i], arr[min_idx] = arr[min_idx], arr[i]

def insertion_sort(input: List[int]) -> List[int]:
    """"""

def hashing(input: List[int]) -> List[int]:
    """"""

def _heapify(h_arr, h_arr_len, i):
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2

    if left < h_arr_len and h_arr[largest] < h_arr[left]:
        largest = left

    if right < h_arr_len and h_arr[largest] < h_arr[right]:
        largest = right

    if largest != i:
        h_arr[i], h_arr[largest] = h_arr[largest], h_arr[i]

        _heapify(h_arr, h_arr_len, largest)

def heap_sort(arr: List[int]) -> List[int]:
    """"""
    arr_len = len(arr)

    for i in range(arr_len // 2 - 1, -1, -1):
        _heapify(arr, arr_len, i)

    for i in range(arr_len - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        _heapify(arr, i, 0)

    return arr

def _partition(p_arr, low, high):
        pivot = p_arr[high]
        i = low - 1

        for j in range(low, high):
            if p_arr[j] <= pivot:
                i += 1
                p_arr[i], p_arr[j] = p_arr[j], p_arr[i]

        p_arr[i + 1], p_arr[high] = p_arr[high], p_arr[i + 1]

        return i + 1

def quick_sort(arr: List[int], low: int, high: int) -> List[int]:
    """"""
    size = high - low + 1
    stack = [0] * (size)
 
    top = 0 # -1
 
    # top = top + 1
    stack[top] = low
    top += 1
    stack[top] = high
 
    while top >= 0:
        high = stack[top]
        top -= 1
        low = stack[top]
        top -= 1
 
        pivot = _partition(arr, low, high )
 
        if pivot - 1 > low:
            top += 1
            stack[top] = low
            top += 1
            stack[top] = pivot - 1
 
        if pivot + 1 < high:
            top += 1
            stack[top] = pivot + 1
            top += 1
            stack[top] = high

    return arr

if __name__ == '__main__':
   
    list_length = len(RAND_LIST)

    # print(RAND_LIST)
    # sorted = quick_sort(RAND_LIST, 0, list_length - 1)
    # print(sorted)
   
    # quit()


    print(timeit.timeit(stmt='merge_sort(RAND_LIST)',
                        setup='from __main__ import merge_sort, RAND_LIST',
                        number=1000))

    merge_timer = timeit.Timer(functools.partial(merge_sort, RAND_LIST))
    merge_time_result: float = merge_timer.timeit(1000)
    print(f'merge sort {RUN_COUNT} executions: ', merge_time_result)
    print(timeit.timeit(stmt='merge_sort(RAND_LIST)',
                        setup='from __main__ import merge_sort, RAND_LIST',
                        number=1000))
    quit()




    selection_timer = timeit.Timer(functools.partial(selection_sort, RAND_LIST))
    insertion_timer = timeit.Timer(functools.partial(insertion_sort, RAND_LIST))
    # # hashing?
    heap_timer = timeit.Timer(functools.partial(heap_sort, RAND_LIST))
    quick_timer = timeit.Timer(functools.partial(quick_sort, RAND_LIST, 0, list_length - 1))

    selection_time_result: float = selection_timer.timeit(RUN_COUNT)
    insertion_time_result: float = insertion_timer.timeit(RUN_COUNT)
    # # hashing
    heap_time_result: float = heap_timer.timeit(RUN_COUNT)
    quick_time_result: float = quick_timer.timeit(RUN_COUNT)

    print(f'selection sort {RUN_COUNT} executions: ', selection_time_result)
    print(f'insertion sort {RUN_COUNT} executions: ', insertion_time_result)
    print(f'heap sort {RUN_COUNT} executions: ', heap_time_result)
    print(f'quick sort {RUN_COUNT} executions: ', quick_time_result)

    
    # unsorted = [2, 3, -9, 15, 1, -3, 3, 2, 14]
    # print(RAND_LIST)
    # sorted = merge_sort(RAND_LIST)
    # print(sorted)
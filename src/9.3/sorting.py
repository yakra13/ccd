"""9.3 Demonstrate the ability to analyze sorting routines to determine the most efficient one to use,
using an approximation of Big-O notation

Objectives
- [x] Merge sort
- [x] Selection sort
- [x] Insertion sort
- [x] Hashing
- [x] Heap sort
- [x] Quick sort
"""
from copy import deepcopy
from time import perf_counter
from typing import Callable, List
from functools import wraps
import random
import textwrap
import tracemalloc

ARRAY_SIZE: int = 100
MIN_RANDOM: int = -1000
MAX_RANDOM: int =  1000
RUN_COUNT: int = 10000
RAND_LIST: List[int] = random.sample(range(MIN_RANDOM, MAX_RANDOM), ARRAY_SIZE)


def sort_performance(func):
    """Decorator to handle performance checking."""
    line_width = 60

    @wraps(func)
    def wrapper(*args):
        original = deepcopy(args[2])
        tracemalloc.start()
        start_time = perf_counter()
        res = func(*args)
        current, peak = tracemalloc.get_traced_memory()
        finish_time = perf_counter()
        elapsed = finish_time - start_time
        average = elapsed / args[1]
        tracemalloc.stop()

        print(f"╔{'═' * line_width}╗")
        print(f'║█▓▒░{args[0].__name__: ^{line_width - 8}}░▒▓█║')
        print(f"╚{'═' * line_width}╝")
        formatted_doc = textwrap.fill(args[0].__doc__, width=line_width + 2,
                                      replace_whitespace=False, expand_tabs=False)
        print(f'{formatted_doc : ^{line_width}}', '\n')
        print(f"{'Iterations:' : <50} {args[1]}")
        print(f"{'Memory usage:' : <50} {current / 10**6:.6f} MB")
        print(f"{'Peak memory usage:' : <50} {peak / 10**6:.6f} MB")
        print(f"{'Avg time per iteration:' : <50} {average:.6f}s")
        print(f"{'Total time elapsed:' : <50} {elapsed:.6f}s")

        if len(original) > 10:
            print('Before sort:', *original[:5], '...', *original[-5:])
            print('After sort:', *res[:5], '...', *res[-5:])
        else:
            print('Before sort:', *original)
            print('After sort:', *res)

        print('─' * (line_width + 2))

        return res

    return wrapper

@sort_performance
def measure_performance(func: Callable, iterations:int, *args):
    """Middle-man function to allow multiple iterations of a sort method."""
    for _ in range(0, iterations):
        res = func(*args)
    return res

def _merge(arr1: List[int], arr2: List[int]) -> List[int]:
    """Helper function for merge sort."""
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

# - [ ] Merge sort
def merge_sort(arr: List[int]) -> List[int]:
    """Ω(n log(n))    Θ(n log(n))    O(n log(n))"""
    if len(arr) <= 1:
        return arr

    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])

    return _merge(left, right)

# - [ ] Selection sort
def selection_sort(arr: List[int]) -> List[int]:
    """Ω(n²)    Θ(n²)    O(n²)"""
    for i in range(len(arr) - 1):
        min_idx = i
        for j in range(i + 1, len(arr)):
            if arr[min_idx] > arr[j]:
                min_idx = j

        arr[i], arr[min_idx] = arr[min_idx], arr[i]

    return arr

# - [ ] Insertion sort
def insertion_sort(arr: List[int]) -> List[int]:
    """Ω(n)    Θ(n²)    O(n²)"""
    for i in range(1, len(arr)):
        key = arr[i]

        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1

        arr[j + 1] = key

    return arr

# - [ ] Hashing
def hash_sort(data, count, low, dimensions) -> dict[int]:
    """O(n) **values must be unique."""
    swap_count = 0
    hysteresis_count = 0
    position = 0
    value = 0

    while ((swap_count < count) and (hysteresis_count < count)):
        value = data[(position) // dimensions][(position) % dimensions]
        d = (value - low) // dimensions
        m = (value - low) % dimensions


        if data[d][m] == value:
            position += 1
            hysteresis_count += 1
        else:
            temp = data[(position) // dimensions][(position) % dimensions]
            data[(position) // dimensions][(position) % dimensions] = data[d][m]
            data[d][m] = temp
            swap_count += 1

    return data

def _heapify(h_arr, h_arr_len, i):
    """Helper function for heap sort."""
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

# - [ ] Heap sort
def heap_sort(arr: List[int]) -> List[int]:
    """Ω(n log(n))    Θ(n log(n))    O(n log(n))"""
    arr_len = len(arr)

    for i in range(arr_len // 2 - 1, -1, -1):
        _heapify(arr, arr_len, i)

    for i in range(arr_len - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        _heapify(arr, i, 0)

    return arr

def _partition(p_arr, low, high):
    """Helper function for quick sort."""
    pivot = p_arr[high]
    i = low - 1

    for j in range(low, high):
        if p_arr[j] <= pivot:
            i += 1
            p_arr[i], p_arr[j] = p_arr[j], p_arr[i]

    p_arr[i + 1], p_arr[high] = p_arr[high], p_arr[i + 1]

    return i + 1

# - [ ] Quick sort
def quick_sort(arr: List[int], low: int, high: int) -> List[int]:
    """Ω(n log(n))    Θ(n log(n))    O(n²)"""
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
    measure_performance(merge_sort, RUN_COUNT, deepcopy(RAND_LIST))
    measure_performance(selection_sort, RUN_COUNT, deepcopy(RAND_LIST))
    measure_performance(insertion_sort, RUN_COUNT, deepcopy(RAND_LIST))

    hash_sort_data = [[8, 3, 1],
                      [5, 4, 9],
                      [7, 2, 6]]
    measure_performance(hash_sort, RUN_COUNT, hash_sort_data, 9, 1, 3)

    measure_performance(heap_sort, RUN_COUNT, deepcopy(RAND_LIST))
    measure_performance(quick_sort, RUN_COUNT, deepcopy(RAND_LIST), 0, len(RAND_LIST) - 1)

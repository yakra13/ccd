"""8.4 Demonstrate skill in creating and using a hash table that accepts any data type

Objectives

- [x] Creating a hash table with n number of items
- [x] Navigating through a hash table to find the nth item
- [x] Finding an item in a hash table
- [x] Removing selected items from a hash table
- [x] Inserting an item into a hash table 
- [x] Implement functionality to mitigate hash collisions within the hash table
- [x] Removing all items from the hash table
"""
from typing import Any
from hash_table import HashTable

def new_table_with_n_items(**kwargs) -> HashTable:
    print('- [ ] Creating a hash table with n number of items')
    table: HashTable = HashTable.from_dict(kwargs)
    print(table)
    return table

def find_nth_item(table: HashTable, index: int = 0) -> Any | None:
    print('- [ ] Navigating through a hash table to find the nth item')
    return table.get_by_index(index)

def find_item(table: HashTable, key: Any) -> Any | None:
    print('- [ ] Finding an item in a hash table')
    try:
        return table[key]
    except KeyError:
        print(f'Key \'{key}\' does not exist in table.')
        return None

def remove_item_from_table(table: HashTable, key: Any):
    print('- [ ] Removing selected items from a hash table')
    print(table)
    del table[key]
    print(table)

def insert_item(table: HashTable, key: Any, value: Any):
    print('- [ ] Inserting an item into a hash table')
    print(table)
    if key not in table.keys:
        table[key] = value
    print(table)

def remove_all_items(table: HashTable):
    print('- [ ] Removing all items from the hash table')
    print(table)
    table.clear()
    print(table)

if __name__ == '__main__':
    t: HashTable = new_table_with_n_items(one=1, two=2, three=3, four=4)
    print(entry := find_nth_item(t, 2))
    print(entry2 := find_item(t, 'three'))
    remove_item_from_table(t, 'three')
    insert_item(t, 'seven', 7)
    # - [ ] Implement functionality to mitigate hash collisions within the hash table
    # See hash_table.py line 39
    remove_all_items(t)

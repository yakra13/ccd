"""7.4 Demonstrate the ability to perform file management operations in Python

Objectives

- [x] Read data from a file
- [x] Parse data from a file
- [x] Write data to a file
- [x] Modify data in a file
- [x] Close an open file
- [x] Print file information to the console
- [x] Create a new file
- [x] Append data to an existing file
- [x] Delete a file
- [x] Determine the size of a file
- [x] Determine location within a file
- [x] Insert data into an existing file
- [x] Open an existing file
"""
import csv
import os
from pathlib import Path

def main() -> None:
    """Entry point."""
    string_data: str = '''Login email;Identifier;First name;Last name
laua@examplecom;20;Laura;Gy
craig@example.com;4081;Craig;Johnson
mary@example.com;9346;Mary;Jenkins
jamie@example.com;5079;Jamie;Smith'''

    search_string: str = 'Laura'
    line_modify_data: str = 'laura@example.com;2070;Laura;Grey\n'
    new_line_data: str = 'timmy@example.com;1234;Timmy;Smith'

    file_path: Path = Path.cwd().joinpath('test_file.csv')

    print(f'Write the file: {file_path}')
    write_to_file(file_path, string_data)

    print(f'Get the line containing \'{search_string}\'')
    line_number = get_line_containing(file_path, search_string)

    if line_number > 0:
        print(f'Modify line number {line_number}')
        modify_file_by_line(file_path, line_number, line_modify_data)
    else:
        print(f'Search string \'{search_string}\' not found.')

    print('Append another line to the file')
    append_csv_entry(file_path, new_line_data)

    print('Parse the file to find all the emails')
    parse_csv_file(file_path, 'Login email')

    print('Show file info')
    print_file_info(file_path)

    print('Delete the file')
    delete_file(file_path)

# - [ ] Create a new file
# - [ ] Write data to a file
def write_to_file(file_path: Path, data: str) -> None:
    """Write specified string to file path."""
    with open(file_path, 'w', encoding='utf-8') as file:
        file.writelines(data)

# - [ ] Delete a file
def delete_file(file_path: Path) -> None:
    """Deletes the specified file."""
    if not file_path.is_file():
        print('Specified path is not a file.')
        return
    os.remove(file_path)

# - [ ] Open an existing file
# - [ ] Read data from a file
# - [ ] Modify data in a file
# - [ ] Insert data into an existing file
# - [ ] Close an open file
def modify_file_by_line(file_path: Path, line_number: int, data: str) -> None:
    """Replaces a line in the specified file."""
    if not file_path.is_file():
        print('Specified path is not a file.')
        return

    file = open(file_path, 'r', encoding='utf-8')
    file_data = file.readlines()
    file.close()

    if len(file_data) >= line_number and line_number >= 0:
        file_data[line_number] = data
    else:
        print('Specified line number out of range.')
        return

    file = open(file_path, 'w', encoding='utf-8')
    file.writelines(file_data)
    file.close()

# - [ ] Determine location within a file
def get_line_containing(file_path: Path, search_string: str) -> int:
    """Returns the first line index containint the specified string."""
    index = -1
    with open(file_path, 'r', encoding='utf-8') as file:
        file_data = file.readlines()
        for i in range(0, len(file_data)):
            if search_string in file_data[i]:
                index = i
                break
    return index

# - [ ] Parse data from a file
def parse_csv_file(file_path: Path, column: str) -> None:
    """Parse the file to get a specified column"""
    with open(file_path, encoding='utf-8') as csv_file:
        csv_data = csv.DictReader(csv_file, delimiter=';')
        for row in csv_data:
            print(row[column])

# - [ ] Append data to an existing file
def append_csv_entry(file_path: Path, data:str) -> None:
    """Appends a line to the end of the file."""
    with open(file_path, 'a', encoding='utf-8') as file:
        file.write('\n' + data)

# - [ ] Determine the size of a file
# - [ ] Print file information to the console
def print_file_info(file_path: Path) -> None:
    """Prints file information."""
    size: int = os.path.getsize(file_path)
    all_info = os.stat(file_path)

    print(f'File size: {size}')
    print(all_info)


if __name__ == '__main__':
    main()

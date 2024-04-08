"""7.7 Demonstrate skill in creating and implementing conditional statements,
expressions, and constructs

Objectives

- [x] for loop
- [x] while loop
- [x] with statement
- [x] if statement
- [x] if/else statement
- [x] if/elif/else statement
- [x] try/except/finally
"""

# - [ ] for loop
def objective_for() -> None:
    """for example"""
    for i in range(0, 6):
        print(i, end=' ')
    print('\n')

# - [ ] while loop
def objective_while() -> None:
    """while example"""
    i: int = 0
    while i <= 5:
        print(i, end=' ')
        i += 1
    print('\n')

# - [ ] with statement
def objective_with() -> None:
    """with example"""
    with open(__file__, encoding='utf-8') as f:
        print(f.readline())

# - [ ] if statement
# - [ ] if/else statement
# - [ ] if/elif/else statement
def objective_ifs() -> None:
    """ifs example"""
    i: int = 0
    if i == 0:
        i += 1

    if i == 0:
        i -= 1
    else:
        i += 1

    if i == 0:
        i -= 1
    elif i == 1:
        i -= 1
    else:
        print(f'i should be 2: i is {i}\n')


# - [ ] try/except/finally
def objective_try() -> None:
    """try example"""
    i: int
    s: str = 'a'

    try:
        i = int(s)
        print(f'{i}')
    except(ValueError) as e:
        print(f'{s} is not a valid int: {e}')
    finally:
        print('finally')


def main() -> None:
    """Entry point."""
    print('for loop:')
    objective_for()
    print('while loop:')
    objective_while()
    print('with:')
    objective_with()
    print('ifs:')
    objective_ifs()
    print('try:')
    objective_try()

if __name__ == '__main__':
    main()

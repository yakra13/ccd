"""7.3 Demonstrate the ability to perform basic arithmetic operations using Python operators
while ensuring proper order of operations (PEMDAS)

Objectives

- [x] Modulus
- [x] Addition
- [x] Subtraction
- [x] Multiplication
- [x] Division
"""

def main() -> None:
    """Entry point"""
    int_x: int = 5
    int_y: int = 8
    int_z: int = 3
    mul_a: float = 2.0
    div_b: float = 1.5
    mod_c: int = 4

    # - [ ] Addition
    print(f'Addition: {int_x} + {int_y} = {int_x + int_y}')
    # - [ ] Subtraction
    print(f'+ Subtraction: {int_x} + {int_y} - {int_z} = {int_x + int_y - int_z}')
    # - [ ] Multiplication
    print(f'+ Multiplication: {int_x} + {int_y} - {mul_a} * {int_z} =',
          f' {int_x + int_y - mul_a * int_z}')
    # - [ ] Division
    print(f'+ Division: ({int_x} + {int_y} - {mul_a} * {int_z}) / {div_b} =',
          f' {(int_x + int_y - mul_a * int_z) / div_b}')
    # - [ ] Modulus
    print(f'+ Modulus: (({int_x} + {int_y} - {mul_a} * {int_z}) / {div_b}) % {mod_c} =',
          f' {((int_x + int_y - mul_a * int_z) / div_b) % mod_c}')

if __name__ == '__main__':
    main()

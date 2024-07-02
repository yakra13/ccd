# 6.18 Describe how and when bitwise operators are used

### Objectives

- [ ] or (|)
- [ ] xor (^)
- [ ] bitwise complement (~) 
- [ ] and (&)
- [ ] shift left (<<)
- [ ] shift right (>>)
- [ ] Add, removing, and testing for single-bit flags
- [ ] Extracting arbitrary bytes from multi-byte data types


### Answers

**or (|)**   
>Results in 1(true) when either/both bits are 1 => 1001 | 0001 = 1001

**xor (^)**
>Results in 1 when only one of the bits is a 1 => 1001 ^ 0001 = 1000

**bitwise complement (~)**
>Returns the complement of the bits => ~1001 = 0110

**and (&)**
>Results in 1 when both bits are 1 => 1001 & 0001 = 0001

**shift left (<<)**
>Shift each bit to the left, causes the high bit to 'fall off'; the low bit will be 0 => 1001 << 1 = 0010
This effectively multiples the number by 2 as long as the high bit is 0.

**shift right (>>)**
>Shift each bit to the right causing the low bit to 'fall off', the high bit will be filled with a 0 => 1001 >> 1 = 0100
This effectively divides the number by 2 and floors it (ie 3 / 2 = 1)

**Add, removing, and testing for single-bit flags**
>A single variable can be used to effectively hold several boolean values using each bit as a true/false flag. Setting a bit can be done in a few ways but a simple method is the following:
int bitmask = 0;
bitmask |= 1 << 4;
We start with an empty bitmask then or(|) it with the result of left shifting 1 by the position of the bit we want to turn on. In this case we are turning on the 4th bit (from right to left with the far right bit being the 0th bit).

**Extracting arbitrary bytes from multi-byte data types**
>You can use a mask to extract any particular range of bits from a piece of data. This could be used to tak a 32 bit variable and break it into 4 8bit variables for network transmission or other reason then to be reassembled at a later time.
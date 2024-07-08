"""14.3 In Python, demonstrate the ability to incorporate regular expression processing into a program

Objectives

- [ ] Matching
- [ ] Use of capture groups
"""
import re
from typing import Final

# - [ ] Use of capture groups
REGEX_PASSWORD: Final[str] = r"^(?=.*([a-z]))(?=.*([A-Z]))(?=.*(\d))(?=.*([@$!%*?&]))([A-Za-z\d@$!%*?&\s]{8,})+$"

def regex_str(input_string: str):
    """Validates that a string conforms to a regex pattern.
    In this case a password complexity pattern of minimum 8 characters.
    
    Args:
        input_string: a string to match against the regex
    """
    pattern = re.compile(REGEX_PASSWORD)
    m = pattern.match(input_string)
    if not m:
        print(f'\'{input_string}\' does not match')
    else:
        print(f'\'{input_string}\' does match')
        print(f'\tlower case: {m.group(1)}')
        print(f'\tupper case: {m.group(2)}')
        print(f'\tdigit: {m.group(3)}')
        print(f'\tspecial character: {m.group(4)}')
        print(f'\tfull match: {m.group(5)}')

if __name__ == '__main__':
    regex_str('invalid pass')
    regex_str('InValId PasS')
    regex_str('InVal1d Pas5')
    regex_str('iNV@l1d')
    regex_str('V@l1dP@s5')

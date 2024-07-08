"""14.3 In Python, demonstrate the ability to incorporate regular expression processing into a program

Objectives

- [ ] Matching
- [ ] Use of capture groups
"""
import re

def regex_str(cls, pattern: str = REGEX_PASSWORD):
        """Validates that a string conforms to a regex pattern.
        
        Args:
            pattern: A regex pattern to match
        
        Raises:
            RuntimeError: start() was not called first
            TypeError: The variable is not a valid type (str)
            ValueError: The variable does not match the pattern
        """
        if cls._variable is None:
            raise RuntimeError('start() method must be called first')

        pattern = re.compile(pattern)

        try:
            if not bool(pattern.match(cls._variable)):
                err = f'{cls._var_name} does not match {pattern}'
                cls._reset()
                raise ValueError(err)
        except TypeError as exc:
            raise TypeError('Only str are valid for str_contains_chars()') from exc

        return cls
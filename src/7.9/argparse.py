""" 7.9 Demonstrate the ability to parse command line arguments using built-in functionality

Objectives
N/A
"""
import getopt
import sys

class ArgOpts(object):
    """Singleton to store command line args."""
    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super(ArgOpts, cls).__new__(cls)
        return cls._instance

    def __init__(self) -> None:
        self._show_help: bool = False
        self._message: str = None
        self._output: str = None

        opts = "hm:o:"
        lopts = ["help", "message=", "output="]

        try:
            arguments, values = getopt.getopt(sys.argv[1:], opts, lopts)

            if values:
                # Values not appearing at the end of the command turn all args
                # following it into values. It could be allowed by iterating
                # thru values and finding -m/-o/-h etc and taking the next value
                # in the list as that args value. However, that will likely be more
                # trouble than it is worth so instead we just strictly enforce
                # command line arg syntax.
                raise getopt.error(f'Invalid value found: {values[0]}')

            for cur_arg, cur_val in arguments:
                if self._show_help is False and cur_arg in ('-h', '--help'):
                    # Could exit from the program here since usually when help is shown
                    # execution doesn't continue. So instead of using a bool just show
                    # the help message and exit.
                    self._show_help = True
                elif self._message is None and cur_arg in ('-m', '--message'):
                    # Sanitization could occur here depending on how this value
                    # will be used.
                    self._message = cur_val
                elif self._output is None and cur_arg in ('-o', '--output'):
                    # Path/permission validation could occur here.
                    self._output = cur_val

        except getopt.error as e:
            print(str(e))

    @property
    def show_help(self) -> bool:
        """Get show help arg"""
        return self._show_help

    @property
    def message(self) -> str:
        """Get message arg"""
        return self._message

    @property
    def output(self) -> str:
        """Get output arg"""
        return self._output

# getopt version
def getopt_version():
    """Using getopt to parse the args."""
    print('getopt version')
    args = ArgOpts()

    print(f'\thelp = {args.show_help}')
    print(f'\tmessage = {args.message}')
    print(f'\toutput = {args.output}\n')

# Using kwargs
def kwargs_version(**kwargs):
    """Iterating kwargs to parse the args."""
    print('kwargs version')
    for key, val in kwargs.items():
        # Perform arg and value validation here as appropriate.
        # Could store the final results in a singleton like ArgOpts above.
        print(f'\targ = {key}, value = {val}')

if __name__ == '__main__':
    # For demonstration purposes if the first argument is 'k' do the kwargs version.
    if len(sys.argv) < 2:
        print('For sample purposes only. Provide \'k\' as the first argument for the kwargs version:')
        print('\t.\\argparse.py k some_label=some_value ...')
        print('Any label and value is allowed and will only be parsed and displayed.')
        print('\nDo not use \'k\' as the first argument to use the getopt version:')
        print('Valid arguments are:')
        print('\t-h\n\t-m *messsage*\n\t-o *output path*')
        print('NOTE: this code doesn\'t actually do anything with the args beyond parse them')
        print('and display the results of parsing.')
        exit()
    if sys.argv[1] == 'k':
        # This is very simple and requires all args be in the format arg=value
        # A more ellaborate version could be made to handle quoted strings and
        # different formats like '-a value' but at that point we're just recreating
        # getopt (which I assume is native c?)
        try:
            kwargs_version(**dict(arg.split('=') for arg in sys.argv[2:]))
        except ValueError as e:
            print('Kwargs version requires format:')
            print('\t.\\argparse.py k some_label=some_value ...')
    else:
        getopt_version()

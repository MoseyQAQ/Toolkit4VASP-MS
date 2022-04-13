import formatconverter as fc
from sys import argv
from os import path
for file in argv[1:]:
    if path.exists(f'{file}.vasp'):
        print('File already exists, it\'ll be covered\n');
    fc.formatconverter(file, originalformat = 'cif', toformat = 'vasp',outfile = f'{file}.vasp');

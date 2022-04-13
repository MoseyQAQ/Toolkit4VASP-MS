import formatconverter as fc
from sys import argv
from os import path
for file in argv[1:]:
    if path.exists(f'{file}.cif'):
        print('File already exists, it\'ll be covered\n');
    fc.formatconverter(file, originalformat = 'xsd', toformat = 'cif',outfile = f'{file}.cif');

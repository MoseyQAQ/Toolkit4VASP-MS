from ase import io

def formatconverter(infile = 'POSCAR', originalformat = 'vasp', toformat = 'xsd', outfile = f'file.xsd'):
    atomic_config = io.read(infile, format = originalformat);
    io.write(outfile, images = atomic_config, format = toformat);
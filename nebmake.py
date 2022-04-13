#!/bin/python
import os
from ase import io
from ase.neb import NEB
from sys import argv
from os import path
from ase.optimize import  BFGS
'''IO读取数据'''
if len(argv) != 5:
    print("4 inputs are required. \n")
    exit(1)
def write_st(images):
    k=0
    for i in images:
        os.mkdir(f'0{k}')
        os.chdir(f'0{k}')
        io.write(images = i,format = 'vasp',filename = f'POSCAR')
        k+=1
        os.chdir('..')

inital = argv[1]; final = argv[2]; num = int(argv[3]);method = argv[4];
if path.exists(inital) == False or path.exists(final) == False:
    print("File doesn't exists\n");
    exit(1);

inital_config = io.read(inital)
final_config = io.read(final)
'''读取数据结束，下面开始生成'''
images = [inital_config]
images += [inital_config.copy() for i in range(num)]
images += [final_config]
#插入指定数目
neb = NEB(images)
if ((method == 'IDPP') or (method == 'idpp')):
    neb.interpolate(method='idpp')
    write_st(images)

elif method == 'li' :
    neb.interpolate()
    write_st(images)
else:
    print('Unvaild method.\n');
    exit(1);

io.write('XDATCAR',images)

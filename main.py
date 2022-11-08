from sys import argv
import xml.etree.ElementTree as xee

'''
print(argv[1])
'''
charge_result = []
old="Charge=\"1\""
def input_charge_reader():
    for temp in open(argv[2],'r',encoding='utf-8').readlines():
        if temp.isspace():
            pass
        else:
            charge_result.append(temp.strip())

def change():
    file_data = ""
    i=0;
    with open(argv[1],'r',encoding='utf-8') as f:
        for line in f:
            if old in line:
                line=line.replace(old,f'Charge=\"{charge_result[i]}\"')
                i=i+1
            file_data+=line

    with open(argv[1],'w',encoding='utf-8') as f:
        f.write(file_data)


input_charge_reader();
change();
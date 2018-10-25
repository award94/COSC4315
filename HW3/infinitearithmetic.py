import sys
import inputhandler
from compute import *

#print('hw3')

digitsPerNode = int(str.split(sys.argv[1], '=')[2])
temp = (str.split(sys.argv[1], '=')[1])
temp = temp.split(';')[0]

#get filename and dpn from console arguments
#digitsPerNode = int(sys.argv[2])
lines = list(open(str(temp), 'r'))

#print("DPN=",digitsPerNode)
j = lines.__len__()

def main(i, digitsPerNode):
    if (i > 0):
        input = lines[j - i].replace('\n', '')
        result = str(compute(input, 0, input.__len__(), digitsPerNode))
        if int(result) >= 0:
            print(input+'='+result)
        else:
            print(input + '=' + "ERROR: Invalid input")
        main(i - 1, digitsPerNode)

main(j, digitsPerNode)
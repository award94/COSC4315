import sys
import inputhandler
from compute import *

print('hw3')

digitsPerNode = int(str.split(sys.argv[1], '=')[2])
temp = (str.split(sys.argv[1], '=')[1])
temp = temp.split(';')[0]

#get filename and dpn from console arguments
#digitsPerNode = int(sys.argv[2])
lines = list(open(str(temp), 'r'))

print("DPN=",digitsPerNode)
j = lines.__len__()

def main(i, digitsPerNode):
    if (i > 0):
        # getline
        input = lines[j - i]
        input = input.replace('\n', '')
        #print('\n')
        result = str(compute(input, 0, input.__len__(), digitsPerNode))
        print(input+'='+result)
        #print('\n')
        main(i - 1, digitsPerNode)

main(j, digitsPerNode)
import sys
from compute import *

digitsPerNode = int(str.split(sys.argv[1], '=')[2])
temp = (str.split(sys.argv[1], '=')[1])
temp = temp.split(';')[0]

#get filename and dpn from console arguments
lines = list(open(str(temp), 'r'))

j = lines.__len__()

#Loop through the input strings
#i is the line number
#digitsPerNode is a positive integer
def main(i, digitsPerNode):
    if (i > 0):
        input = lines[j - i].replace('\n', '')
        result = str(compute(input, 0, input.__len__(), digitsPerNode))
        if int(result) >= 0:
            print(input+'='+result)
        else:
            print(input + '=' + "invalid expression")
        main(i - 1, digitsPerNode)

main(j, digitsPerNode)
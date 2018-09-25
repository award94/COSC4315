import inputhandler
import sys


#Parsing the command line argument
digitsPerNode = int(str.split(sys.argv[1], '=')[2])
temp = (str.split(sys.argv[1], '=')[1])
temp = temp.split(';')[0]

#get filename and dpn from console arguments
#digitsPerNode = int(sys.argv[2])
lines = list(open(str(temp), 'r'))

#find number of lines in the .txt
j = 0

for x in lines:
    j += 1


def main(i):
    if(i > 0):
        #getline
        input = lines[j - i]
        #create new instance of class
        ih = inputhandler.inputhandler(input, digitsPerNode)
        #turns input strings into appropraite variables
        ih.parseraw()
        #splits term list objects by digits per node
        ih.splitlistbydpn()
        #find 3rd term by addition or multiplication
        ih.domath()
        #parsing of results to look pretty
        ih.printResult()
        #go to next line
        main(i-1)

main(j)
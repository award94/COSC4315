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

#Had to use a for loop here because the size of lines isn't the actual number of lines read from the file
#for x in range gives the valid number of lines though
for x in lines:
    j += 1


def main(i):
    if(i > 0):
        #getline
        input = lines[j - i]
        #create new instance of class
        ih = inputhandler.inputhandler(input, digitsPerNode)
        #turns input strings into appropraite variables
        errorCode = 2
        if(ih.dpn == 0):
            errorCode = -1
        if(errorCode != -1):
            errorCode = ih.parseraw()
            #print(errorCode)
            if(errorCode == 0):
                #splits term list objects by digits per node
                ih.splitlistbydpn()
                #find 3rd term by addition or multiplication
                ih.domath()
                #parsing of results to look pretty
                ih.printResult()
                #go to next line
            main(i-1)

main(j)
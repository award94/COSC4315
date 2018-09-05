class inputhandler:

#   constructor
    def __init__(self, rawInput, dpn):
        self.rawInput = rawInput            #the math term we're equating
        self.dpn = dpn                      #digits per node
        if(dpn == 0):
            print("ERROR: digitsPerNode = 0")
            return -1
        self.term1 = []                     #left hand term
        self.term2 = []                     #right hand term
        self.term3 = []                     #the result
        self.listTerm1 = [];
        self.listTerm2 = [];
        self.listTerm3 = [];
        self.op = ['a']                     #+ or *

#   will change input string into managable data
    def parseraw(self):
        print("inside parseraw()")

#       for iterating through rawInput
        parsingIndex = 0

#       will iterate through each character in the string and add them
#       to their appropriate list in term1, term2, or op
        def recurparse(rawInput, term, parsingIndex, op):
#           if not done
            if(parsingIndex < len(rawInput)):
#               add numbers to term list when digit found
                if rawInput[parsingIndex].isdigit():
                    #print(term1, op, term2, rawInput, parsingIndex)
                    term.append(rawInput[parsingIndex])
                    recurparse(rawInput, term, parsingIndex+1, op)
#                add operator to op
                else:
                    if (op[0] == "a"):
                        del(op[0])
                        op.append(rawInput[parsingIndex])
                        #print(rawInput, term2, parsingIndex, op)
#                       switches to term2
                        recurparse(rawInput, self.term2, parsingIndex+1, op)

        recurparse(self.rawInput, self.term1, 0, self.op)

#       prints to see what's happening. Can delete
        print(self.term1)
        print(self.op)
        print(self.term2)

#   Splits the list into dpn sized nodes
    def splitlistbydpn(self):
        #print("inside splitlistbydpn()")
        #print(self.term1.__len__()%self.dpn)
        offset1 = self.term1.__len__()%self.dpn
        offset2 = self.term2.__len__()%self.dpn
        #print(offset1)
        tempList1 = []
        tempList2 = []
        tempString = ""
        #print(tempList1)
        #print(tempList2)

        #if head node is a different size than dpn
        def addHead(tempList, oldList, tempString, i, offset):
            print("i=", i)
            if(i >= offset):
                print("if")
                tempList.append(tempString)
                return -1
            else:
                print("else")
                print("oldList[",i,"]=",oldList[i])
                print("before=", tempString)
                tempString = tempString + oldList[i]
                print("after=", tempString)
                addHead(tempList, oldList, tempString, i+1, offset)

        #if head node is equal size to dpn
        if(offset1 != 0):
            addHead(tempList1, self.term1, tempString, 0, offset1)
            print("tempList1[0]=", tempList1[0])

        if(offset2 != 0):
            addHead(tempList2, self.term2, tempString, 0, offset2)
            print("tempList2[0]=", tempList2[0])

        #number of nodes - headnode
        numNodes1 = (self.term1.__len__() - offset1) / self.dpn
        numNodes2 = (self.term2.__len__() - offset2) / self.dpn
        print(numNodes1)
        print(numNodes2)

        #nested loop
        #adds the individual chars to each node
        def addCharsToNode(tempList, oldList, tempString, i, j, offset):
            print('inside addCharsToNode')
            if i >= self.dpn:
                print("if")
                tempList.append(tempString)
                return -1
            else:
                print("else")
                print("self.term[", i+offset + self.dpn*j, "]=", oldList[i + offset + self.dpn*j])
                tempString = tempString + oldList[i + offset + self.dpn*j]
                addCharsToNode(tempList, oldList, tempString, i+1, j, offset)

        #adds the nodes to the list
        def addNodesToList(tempList, oldList, j, numNodes, offset):
            print('inside addNodesToList')
            if j >= numNodes:
                print("if")
                return -1
            else:
                print("else")
                addCharsToNode(tempList, oldList, tempString, 0, j, offset)
                addNodesToList(tempList, oldList, j+1, numNodes, offset)

        addNodesToList(tempList1, self.term1, 0, numNodes1, offset1)
        addNodesToList(tempList2, self.term2, 0, numNodes2, offset2)
        print(tempList1)
        print(tempList2)

        self.listTerm1 = tempList1
        self.listTerm2 = tempList2

#   Does the math operation
    def domath(self):
        print("inside domath()")

        def addition(term1, term2):
            print("inside addition()")
            print(term1, '+',  term2)
            print(term1.__len__())
            print(term2.__len__())

        def multiplication(term1, term2):
            print("inside multiplication()")
            print(term1, '*', term2)

        print(self.op)
        if(self.op[0] == '+'):
            print("Addition")
            addition(self.listTerm1, self.listTerm2)
        elif(self.op[0] == '*'):
            print("Multiplication")
            multiplication(self.listTerm1, self.listTerm2)
        else:
            print("Invalid Operator");


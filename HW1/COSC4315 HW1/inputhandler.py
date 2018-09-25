class inputhandler:

#   constructor
    def __init__(self, rawInput, dpn):
        self.rawInput = rawInput            #the math term we're equating
        self.dpn = dpn                      #digits per node
        if(dpn == 0 or str(dpn).isalpha()):
            print("ERROR: digitsPerNode is invalid")
            return -1
        self.term1 = []                     #left hand term
        self.term2 = []                     #right hand term
        self.term3 = ""                     #the result
        self.listTerm1 = []
        self.listTerm2 = []
        self.listTerm3 = []
        self.term3Len = 0
        self.op = ['a']                     #+ or *

#   will change input string into managable data
    def parseraw(self):
#       for iterating through rawInput
        parsingIndex = 0

#       will iterate through each character in the string and add them
#       to their appropriate list in term1, term2, or op
        def recurparse(rawInput, term, parsingIndex, op):
#           if not done
            if(parsingIndex < len(rawInput)):
#               add numbers to term list when digit found
                if rawInput[parsingIndex].isdigit():
                    term.append(rawInput[parsingIndex])
                    recurparse(rawInput, term, parsingIndex+1, op)
#                add operator to op
                else:
                    if (op[0] == "a"):
                        del(op[0])
                        op.append(rawInput[parsingIndex])
#                       switches to term2
                        recurparse(rawInput, self.term2, parsingIndex+1, op)

        recurparse(self.rawInput, self.term1, 0, self.op)


#   Splits the list into dpn sized nodes
    def splitlistbydpn(self):
        offset1 = self.term1.__len__()%self.dpn
        offset2 = self.term2.__len__()%self.dpn
        tempList1 = []
        tempList2 = []
        tempString = ""

        #if head node is a different size than dpn
        def addHead(tempList, oldList, tempString, i, offset):
            if(i >= offset):
                tempList.append(tempString)
                return -1
            else:
                tempString = tempString + oldList[i]
                addHead(tempList, oldList, tempString, i+1, offset)

        #if head node is equal size to dpn
        if(offset1 != 0):
            addHead(tempList1, self.term1, tempString, 0, offset1)

        if(offset2 != 0):
            addHead(tempList2, self.term2, tempString, 0, offset2)

        #number of nodes - headnode
        numNodes1 = (self.term1.__len__() - offset1) / self.dpn
        numNodes2 = (self.term2.__len__() - offset2) / self.dpn

        #nested loop
        #adds the individual chars to each node
        def addCharsToNode(tempList, oldList, tempString, i, j, offset):
            if i >= self.dpn:
                tempList.append(tempString)
                return -1
            else:
                tempString = tempString + oldList[i + offset + self.dpn*j]
                addCharsToNode(tempList, oldList, tempString, i+1, j, offset)

        #adds the nodes to the list
        def addNodesToList(tempList, oldList, j, numNodes, offset):
            if j >= numNodes:
                return -1
            else:
                addCharsToNode(tempList, oldList, tempString, 0, j, offset)
                addNodesToList(tempList, oldList, j+1, numNodes, offset)

        addNodesToList(tempList1, self.term1, 0, numNodes1, offset1)
        addNodesToList(tempList2, self.term2, 0, numNodes2, offset2)

        self.listTerm1 = tempList1
        self.listTerm2 = tempList2

#   Does the math operation
    def domath(self):

        def addition(term1, term2, term3):
            #print("inside addition()")
            #print(term1, '+', term2)
            #print("t1len=",term1.__len__())
            #print("t2len=",term2.__len__())
            # Saving indices as i and j
            i = term1.__len__()
            j = term2.__len__()

            if term1.__len__() >= term2.__len__():
                term3length = term1.__len__() + 1
            elif term2.__len__() > term1.__len__():
                term3length = term2.__len__() + 1

            #print("t3len=",term3length)
            k = term3length - 1

            def addEmptyNodes(term3, i):
                if i > 0:
                    term3.append(0)
                    addEmptyNodes(term3, i - 1)

            addEmptyNodes(term3, term3length)

            #print("t3=",term3)
            modShift = 10 ** self.dpn\

            def baseaddition(term1, term2, term3, i, j, k):
                #print("inside basedaddition")
                #print("i=", i, " j=", j, " k=",k)

                # move right to left adding the nodes-------------------------------------------
                if i > 0 and j > 0:
                    #print("term1[",i-1,",]=",term1[i-1]," term2[",j-1,"]=",term2[j-1])
                    result = int(term1[i-1]) + int(term2[j-1])
                    #print("result=",result)

                    term3[k] = term3[k] + result
                    carryOver = term3[k]/modShift
                    #print("carryOver=", carryOver)
                    term3[k-1] = term3[k-1] + carryOver
                    term3[k] = term3[k]%modShift
                    #print(term3)
                    baseaddition(term1, term2, term3, i-1, j-1, k-1)

                #if term 1 is longer than term2-----------------------------------------------------
                elif i > 0 and j <= 0:
                    #print("sending to addrestofterm()")
                    #print("term=",term1,"term3=",term3,"counter=",i-1)
                    addrestofterm(term1, term3, i-1)

                #if term2 is longer than term1------------------------------------------------------
                elif j > 0 and i <= 0:
                    #print("sending to addrestofterm()")
                    #print("term=",term2,"term3=",term3,"counter=",j-1)
                    addrestofterm(term2, term3, j-1)

            def addrestofterm(term, term3, counter):
                if(counter >= 0):
                    #print("inside addrestofterm()")
                    #print("counter=",counter)
                    #print("term[k]=",term[counter-1])
                    term3[counter+1] = term3[counter+1] + int(term[counter])
                    carryOver = term3[counter+1]/modShift
                    term3[counter] = term3[counter] + carryOver
                    term3[counter+1] = term3[counter+1]%modShift
                    #print(term3)

                    addrestofterm(term, term3, counter-1)


            baseaddition(term1, term2, term3, i, j, k)
            #print(term3)

        def multiplication(term1, term2, term3):
            #print("inside multiplication()")
            #print(term1, '*', term2)
            #print(term1, '*', term2)
            #print("term1.len=",term1.__len__())
            #print("term2.len=",term2.__len__())
            term3length = term1.__len__() + term2.__len__()
            #print("term3.len=", term3length)

            def addEmptyNodes(term3, i):
                if(i > 0):
                    term3.append(0)
                    addEmptyNodes(term3, i-1)

            addEmptyNodes(term3, term3length)
            modShift = 10**self.dpn
            #print(modShift)
            #print(term3)
            #print("t3len=", term3length)

            def multiply(term3, i, j, carryOver):
                if(i >= 0):
                    #print("inside multiply, i=",i)
                    multiplyNested(term3, i, j, carryOver)
                    multiply(term3, i-1, j, carryOver)

            def multiplyNested(term3, i, j, carryOver):
                if j >= 0:
                    #Help for debugging
                    #print("\n\n-------------------------------------------")
                    #print("inside multiplyNested, j=", j)
                    #print(term3)
                    #print("\t term1[", i, "]=", term1[i], "term2[", j, "]=", term2[j])
                    #print("\t carryOver=", carryOver, "\n")

                    #Finding the right index to add product to
                    t1Index = term1.__len__() - i - 1
                    t2Index = term2.__len__() - j - 1
                    #print("t1Index=",t1Index)
                    #print("t2Index=",t2Index)
                    k = term3length - t1Index - t2Index - 1
                    #print("k=",k)

                    #tricky math stuff
                    product = int(term1[i]) * int(term2[j])
                    #print("product=",product)
                    #adding carry from current mult to k-1
                    carryOver = int(product/modShift)
                    term3[k-1] = term3[k-1] + carryOver
                    #print("carryOver=",carryOver)
                    #print("adding to ", int(product%modShift))
                    #adding actual product to k
                    term3[k] = term3[k] + int(product%modShift)
                    #adding any overflow in k from addition to k-1 and trimming k to dpn size
                    carryOver = int(term3[k] / modShift)
                    term3[k] = int(term3[k]%modShift)
                    term3[k-1] = term3[k-1] + carryOver
                    #resulting k node
                    #print("resulting node=", term3[k])

                    multiplyNested(term3, i, j-1, carryOver)

            multiply(term3, term1.__len__()-1, term2.__len__()-1, 0)

            #print("\n------------------------\n------------------------\nResult of all math=",term3)

        if(self.op[0] == '+'):
            addition(self.listTerm1, self.listTerm2, self.listTerm3)
        elif(self.op[0] == '*'):
            multiplication(self.listTerm1, self.listTerm2, self.listTerm3)
        else:
            print("Invalid Operator");

    def printResult(self):
        self.term3Len = self.listTerm3.__len__()

        #Removes any leading zeroes
        def trimEmptyHeads(listTerm3, i, j):
            if(i < j and j != 1):
                if(int(listTerm3[i]) == 0):
                    listTerm3.pop(i)
                    self.term3Len -= 1
                else:
                    return 0
                trimEmptyHeads(listTerm3, i, self.term3Len)

        if(self.term3Len != 1):
            trimEmptyHeads(self.listTerm3, 0, self.term3Len)

        #Adds appropriate # of 0's to a 0 node
        def padZeroes(i, k):
            if(i > 1):
                self.listTerm3[k] = '0' + self.listTerm3[k]
                padZeroes(i-1, k)

        #Converts each node to strings for joining
        def convertNodesFromIntToString(i):
            if(i < self.term3Len):
                self.listTerm3[i] = str(self.listTerm3[i])

                if(str(self.listTerm3[i]).__len__() < self.dpn):
                    padZeroes(self.dpn, i)

                convertNodesFromIntToString(i+1)

        self.listTerm3[0] = str(self.listTerm3[0])
        convertNodesFromIntToString(1)

        #Result
        self.term3 = ''.join(self.listTerm3)
        print(''.join(self.term1) + ''.join(self.op) + ''.join(self.term2) + '=' + self.term3)
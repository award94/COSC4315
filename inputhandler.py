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
        #print("inside parseraw()")

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
        #print(self.term1)
        #print(self.op)
        #print(self.term2)

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
            #print("i=", i)
            if(i >= offset):
                #print("if")
                tempList.append(tempString)
                return -1
            else:
                #print("else")
                #print("oldList[",i,"]=",oldList[i])
                #print("before=", tempString)
                tempString = tempString + oldList[i]
                #print("after=", tempString)
                addHead(tempList, oldList, tempString, i+1, offset)

        #if head node is equal size to dpn
        if(offset1 != 0):
            addHead(tempList1, self.term1, tempString, 0, offset1)
            #print("tempList1[0]=", tempList1[0])

        if(offset2 != 0):
            addHead(tempList2, self.term2, tempString, 0, offset2)
            #print("tempList2[0]=", tempList2[0])

        #number of nodes - headnode
        numNodes1 = (self.term1.__len__() - offset1) / self.dpn
        numNodes2 = (self.term2.__len__() - offset2) / self.dpn
        #print(numNodes1)
        #print(numNodes2)

        #nested loop
        #adds the individual chars to each node
        def addCharsToNode(tempList, oldList, tempString, i, j, offset):
            #print('inside addCharsToNode')
            if i >= self.dpn:
                #print("if")
                tempList.append(tempString)
                return -1
            else:
                #print("else")
                #print("self.term[", i+offset + self.dpn*j, "]=", oldList[i + offset + self.dpn*j])
                tempString = tempString + oldList[i + offset + self.dpn*j]
                addCharsToNode(tempList, oldList, tempString, i+1, j, offset)

        #adds the nodes to the list
        def addNodesToList(tempList, oldList, j, numNodes, offset):
            #print('inside addNodesToList')
            if j >= numNodes:
                #print("if")
                return -1
            else:
                #print("else")
                addCharsToNode(tempList, oldList, tempString, 0, j, offset)
                addNodesToList(tempList, oldList, j+1, numNodes, offset)

        addNodesToList(tempList1, self.term1, 0, numNodes1, offset1)
        addNodesToList(tempList2, self.term2, 0, numNodes2, offset2)

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
            # Saving indices as i and j
            i = term1.__len__() - 1
            j = term2.__len__() - 1

            if term1.__len__() > term2.__len__():
                term3length = term1.__len__()
            elif term2.__len__() > term1.__len__():
                term3length = term2.__len__()
            else:
                term3length = term1.__len__() + 1
            k = term3length - 1

            term3 = []
            # initialize term3 as a list with n elements

            def addEmptyNodes(term3, i):
                if i > 0:
                    term3.append(0)
                    addEmptyNodes(term3, i-1)

            addEmptyNodes(term3, term3length)
            modShift = 10**self.dpn
            print(modShift)
            print(term3)
            print("t3len=", term3length)

            # I know I don't need to create another def but it wasn't working when I tried to add a third parameter
            # so I just made another function and it seems to work, super hacky and ratchet but I'm just trying to
            # make it work for now
            def baseaddition(term1, term2, term3, i, j, k):
                # Saving indices as i and j, I need  a  better way to pass these to the function so that they don't get
                # reset causing an infinite loop
                print("inside basedaddition")
                if i > j:
                    # subtract until j is 0
                    if j > 0:
                        # The program  should recurse and add the values together until the shorter term ends
                        print("case 1: i > j")
                        result = int(term1[i]) + int(term2[j])
                        term3[k] = result
                        i -= 1
                        j -= 1
                        k -= 1
                        baseaddition(term1, term2, term3, i, j, k)
                        #commenting out for now because otherwise it will cause infinite recursion because I messed up
                        #on my function passing
                    else:
                        # case where j substring has ended
                        if i > 0:
                            print("Case 1: j has ended")
                            term3[k] = term1[i]
                            i -= 1
                            k -= 1
                            baseaddition(term1, term2, term3, i, j, k)
                elif j > i:
                    # subtract until i is 0
                    if i > 0:
                        print("Case 3: j > i")
                        result = int(term1[i]) + int(term2[j])
                        term3[k] = result
                        i -= 1
                        j -= 1
                        k -= 1
                        baseaddition(term1, term2, term3, i, j, k)
                    else:
                        if j > 0:
                            print("Case 2: i has ended")
                            term3[k] = term2[j]
                            j -= 1
                            k -= 1
                            baseaddition(term1, term2, term3, i, j, k)
                else:
                    # exit condition
                    # I'm going  to code for overflow after I get the basic version working
                    print("Case 3: i = j")
                    if i > 0:
                        result = int(term1[i]) + int(term2[j])
                        term3[k] = result
                        print(term3[k])
                        i -= 1
                        j -= 1
                        k -= 1
                        baseaddition(term1, term2, term3, i, j, k)
                    else:
                        result = int(term1[i]) + int(term2[j])
                        term3[k] = result
                        print(result)
                print(term3)
                # IDK why this shit prints 3 times, I'll troubleshoot it more tomorrow

                    #baseaddition(term1, term2, term3)
                    # i and j are the same, therefore just iterate one at a time, maybe modify this to  elif (i == j)
                    # in order to use else to just catch all other stuff

            baseaddition(term1, term2, term3, i, j, k)


        def multiplication(term1, term2, term3):
            print("inside multiplication()")
            print(term1, '*', term2)
            print(term1, '*', term2)
            print("term1.len=",term1.__len__())
            print("term2.len=",term2.__len__())
            term3length = term1.__len__() + term2.__len__()
            print("term3.len=", term3length)

            def addEmptyNodes(term3, i):
                if(i > 0):
                    term3.append(0)
                    addEmptyNodes(term3, i-1)

            addEmptyNodes(term3, term3length)
            modShift = 10**self.dpn
            print(modShift)
            print(term3)
            print("t3len=", term3length)

            def multiply(term3, i, j, carryOver):
                if(i >= 0):
                    print("inside multiply, i=",i)
                    multiplyNested(term3, i, j, carryOver)
                    multiply(term3, i-1, j, carryOver)

            def multiplyNested(term3, i, j, carryOver):
                if j >= 0:
                    #Help for debugging
                    print("\n\n-------------------------------------------")
                    print("inside multiplyNested, j=", j)
                    print(term3)
                    print("\t term1[", i, "]=", term1[i], "term2[", j, "]=", term2[j])
                    print("\t carryOver=", carryOver, "\n")

                    #Finding the right index to add product to
                    t1Index = term1.__len__() - i - 1
                    t2Index = term2.__len__() - j - 1
                    print("t1Index=",t1Index)
                    print("t2Index=",t2Index)
                    k = term3length - t1Index - t2Index - 1
                    print("k=",k)

                    #tricky math stuff
                    product = int(term1[i]) * int(term2[j])
                    print("product=",product)
                    #adding carry from current mult to k-1
                    carryOver = int(product/modShift)
                    term3[k-1] = term3[k-1] + carryOver
                    print("carryOver=",carryOver)
                    print("adding to ", int(product%modShift))
                    #adding actual product to k
                    term3[k] = term3[k] + int(product%modShift)
                    #adding any overflow in k from addition to k-1 and trimming k to dpn size
                    carryOver = int(term3[k] / modShift)
                    term3[k] = int(term3[k]%modShift)
                    term3[k-1] = term3[k-1] + carryOver
                    #resulting k node
                    print("resulting node=", term3[k])

                    multiplyNested(term3, i, j-1, carryOver)

            multiply(term3, term1.__len__()-1, term2.__len__()-1, 0)

            print("\n------------------------\n------------------------\nResult of all math=",term3)

        print(self.op)
        if(self.op[0] == '+'):
            print("Addition")
            addition(self.listTerm1, self.listTerm2)
        elif(self.op[0] == '*'):
            print("Multiplication")
            multiplication(self.listTerm1, self.listTerm2, self.listTerm3)
        else:
            print("Invalid Operator");
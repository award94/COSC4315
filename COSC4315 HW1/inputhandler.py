class inputhandler:
    
#   constructor
    def __init__(self, rawInput, dpn):
        self.rawInput = rawInput            #the math term we're equating
        self.dpn = dpn                      #digits per node
        self.term1 = []                     #left hand term
        self.term2 = []                     #right hand term
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
        print("inside splitlistbydpn()")

#   Does the math operation
    def domath(self):
        print("inside domath()")
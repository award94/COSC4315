import inputhandler

#Precondition: input is a string, i is an index in the string
#Postcondition: if the ith index of input is a letter, return that character and the recursive call
#               if not, return nothing

def parseoper(input, i):
    if(str(input[i]).isalpha()):
        return str(input[i]) + parseoper(input, i+1)

    return ''

#Precondition: argument is a stirng, i is an index in the string, parenstack is a parenthesis stack
#Postcondition: if the stack is empty, return i
#               if the stack is not empty, return a recursive call with i+=1
def findargend(argument, i, parenstack):
    if(parenstack.__len__() == 0):
        return i

    if(argument[i] == '('):
        parenstack += '('

    if(argument[i] == ')'):
        parenstack.pop()

    return findargend(argument, i+1, parenstack)

#Precondition: rawinput is a string, i is an index, parenend is an index, parenstack is a parenthesis stack
#Postcondition: if i >= parenend, the function exits with an error
#               if the stack is empty and a comma is in the ith index, return i
#               else return recursive call i+=1
def parsecomma(rawinput, i, parenend, parenstack):
    if(i >= parenend):
        return -1

    if(rawinput[i] == '('):
        parenstack += '('
    if(rawinput[i] == ')'):
        parenstack.pop()

    if(parenstack.__len__() == 0 and rawinput[i] == ','):
        return i

    return parsecomma(rawinput, i+1, parenend, parenstack)

#Precondition: term is a string, start and end are indexes, digitsPerNode is a positive integer
#Postcondition: if term.isdigit() return term
#               else return compute()'s integer value
def findtermvalue(term, start, end, digitsPerNode):
    if(term.isdigit()):
        return term
    else:
        return compute(term, start, end, digitsPerNode)

#Precondition: rawinput is a string, start and end are indexes, digitsPerNode is a positive integer
#Postcondition: if the input is valid, return an integer
#               if the input is invalid, return -1
def compute(rawinput, start, end, digitsPerNode):
    oper = parseoper(rawinput, 0)
    argstart = oper.__len__()

    parenstack = ['(']
    argend = findargend(rawinput, argstart+1, parenstack)

    parenstart = argstart+1
    parenend = argend-1

    parenstack2 = []
    commaindex = parsecomma(rawinput, parenstart, parenend, parenstack2)

    term1 = rawinput[parenstart:commaindex]
    term2 = rawinput[commaindex+1:parenend]

    if (str(term1).__len__() == 0 or str(term2).__len__() == 0):
        return -1

    term1value = findtermvalue(term1, parenstart, commaindex, digitsPerNode)
    term2value = findtermvalue(term2, commaindex+1, parenend, digitsPerNode)

    if(int(term1value) < 0 or int(term2value) < 0):
        return -1

    if(oper == 'add'):
        expression = str(term1value) + "+" + str(term2value)
    if oper == 'multiply':
        expression = str(term1value) + "*" + str(term2value)

    #HOMEWORK 1 CODE
    ih = inputhandler.inputhandler(expression, digitsPerNode)
    errorCode = 2
    if (ih.dpn == 0):
        errorCode = -1
    if (errorCode != -1):
        errorCode = ih.parseraw()
        if (errorCode == 0):
            # splits term list objects by digits per node
            ih.splitlistbydpn()
            # find 3rd term by addition or multiplication
            ih.domath()
            # parsing of results to look pretty
            ih.printResult()

    return ih.term3

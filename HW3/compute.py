import inputhandler

#Read the first word to find which operator it is (add or multiply)
def parseoper(input, i):
    #if this index is a character, keep going
    if(str(input[i]).isalpha()):
        #return value = this char + recursive call result
        return str(input[i]) + parseoper(input, i+1)

    #if this index isn't a character, return
    return ''

#add(add(2,2),3)

#Finding the end index of the argument add(2,3)
#                                      -------^
def findargend(argument, i, parenstack):
    if(parenstack.__len__() == 0):
        return i

    if(argument[i] == '('):
        parenstack += '('

    if(argument[i] == ')'):
        parenstack.pop()

    return findargend(argument, i+1, parenstack)

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

def findtermvalue(term, start, end, digitsPerNode):
    if(term.isdigit()):
        return term
    else:
        return compute(term, start, end, digitsPerNode)
    return 0

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

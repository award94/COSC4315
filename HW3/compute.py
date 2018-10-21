import inputhandler

def parseoper(input, i):
    if(str(input[i]).isalpha()):
        return str(input[i]) + parseoper(input, i+1)

    return ''

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
    #print("inside compute")
    #print("rawinput=",rawinput)
    #print("start=", start, "end=", end)

    oper = parseoper(rawinput, 0)
    argstart = oper.__len__()


    argument = rawinput[argstart:]

    parenstack = ['(']
    argend = findargend(rawinput, argstart+1, parenstack)
    #print("oper=", oper)
    #print("argument=", argument)
    #print("argstart=", argstart, "argend=",argend)

    parenstart = argstart+1
    parenend = argend-1

    insideparen = rawinput[parenstart:parenend]
    #print("insideparen=",insideparen)

    parenstack2 = []
    commaindex = parsecomma(rawinput, parenstart, parenend, parenstack2)
    #print("commaindex=",commaindex)

    term1 = rawinput[parenstart:commaindex]
    term2 = rawinput[commaindex+1:parenend]

    #print("term1=",term1,"term2=",term2)

    term1value = findtermvalue(term1, parenstart, commaindex, digitsPerNode)
    term2value = findtermvalue(term2, commaindex+1, parenend, digitsPerNode)
    #print(term1value, term2value)

    if(oper == 'add'):
        expression = str(term1value) + "+" + str(term2value)
    if oper == 'multiply':
        expression = str(term1value) + "*" + str(term2value)

    #print("expression=",expression)


    ih = inputhandler.inputhandler(expression, digitsPerNode)
    # turns input strings into appropraite variables
    errorCode = 2
    if (ih.dpn == 0):
        errorCode = -1
    if (errorCode != -1):
        errorCode = ih.parseraw()
        # print(errorCode)
        if (errorCode == 0):
            # splits term list objects by digits per node
            ih.splitlistbydpn()
            # find 3rd term by addition or multiplication
            ih.domath()
            # parsing of results to look pretty
            ih.printResult()

    return ih.term3
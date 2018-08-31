import inputhandler as ih

digitsPerNode = 4
input = "1234+2222"

ih = ih.inputhandler(input, digitsPerNode)
ih.parseraw()
ih.splitlistbydpn()
ih.domath()

#Just messing around with .split()
#I don't see a feasable way to split
#the strings into correct size nodes
#without using iteration.
print(input)
print([input[i:i+2] for i in range(0, len(input), 2)])
print(input.split())
newLists = input.split('+')
print(newLists)
newString1 = "".join(newLists[0])
newString2 = "".join(newLists[1])
print(newString1)
print(newString2)

print(ih.term1.__len__())
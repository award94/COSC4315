import inputhandler as ih

digitsPerNode = 4
input = "1234+2222"

ih = ih.inputhandler(input, digitsPerNode)
ih.parseraw()
ih.splitlistbydpn()
ih.domath()
import inputhandler as ih

#Need to read these two variables inline, but can do that later
digitsPerNode = 5
input = "9999*9999"

#main(){
ih = ih.inputhandler(input, digitsPerNode)
ih.parseraw()
ih.splitlistbydpn()
ih.domath()
ih.printResult()
#}

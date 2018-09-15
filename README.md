# COSC4315
Adam and Henry's Homework Repo

1184184 COSC 3004
1351222 COSC 3007

The input file was parsed by reading the string input line by line and removing all whitespace by replacing all the spaces with nothing. The terms were then divided by the number of digits per node and appended to a new list. Afterwards we checked to make sure there were only integers in the string and then we parsed the raw input to decide with arithmetic function to perform. The addition function splitst the raw input into two terms for the numbers on either side of the operator and proceeds to add them together node by node starting at the right most node and moving towards the left most node. If there is overflow or if the sum of the nodes is greater than 10**dpn (digits per node) there will be a modshift and the value will be added  to the nodes to the left of the nodes where the overflow occured. The multiplication operator works by multiplying an entire term with the individual elements of all nodes of the other term and adding together the products of the aforementioned multiplication recursively. 

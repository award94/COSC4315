Adam Ward 1184184 cosc3004
Henry Ying 1351222 cosc3007

compile:
g++ -std=c++11 -o mypython.exe mypython.cpp
run:
./mypython.exe input.py

Limitations-
Should be able to handle everything that was specified on the assignment document

Implmentation of Program-
	Parsing: Find the first token in a statement then determine what kind of statement it is (print("asdf") -> print : go to a print function)
		 each statement type has its own function for parsing/evaluation. Each function generally just parses the data inside the statement and
		 does the appropriate action with it (print() finds the data inside () and couts it and also will evaluate expressions inside it)
	Indentation: Each function call has its own scope level which determines the number of spaces required for statements to be within its scope.
 		     For example if we are in main and call f(), all lines with 3 spaces are in the scope of (), all lines with 0 spaces are in main. 
  		     Function calls increase the scopelevel by 1.
	Storage: A structure for variables which includes string name, float value, and int scope. There is a global list of variables initialized at
		 the start of the program. When a variable is declared in an assignment statement, it is created dynamically and pushed onto the list.
		 When a function exits scope, all variables with that function's scope level are deleted.
		 A class for functions. A list of functions is initialized at the start of the program.
		 The data members are string name, int startline, endline, returnline, and return value, bool doesreturn and the
		 defintion string. Whenever a function object is declared, a bunch of functions initialize its data. The function object is pushed onto the list.
		 Whenever a function is called, the statements within the function scope are executed and the return value is calculated is there is one.
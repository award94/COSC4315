#include <iostream>
#include <string>
#include <ctype.h>
#include <list>
#include <stack>
#include <cstdlib>
#include <unistd.h>
#include <iomanip>

#include "variable.h"
list<variable*> Variables;

void processstatement(list<variable*> & Variables, int & lineNum, string line, int scopelevel);

#include "postfixconverter.h"
#include "token_assignment.h"
#include "token_function.h"
#include "token_ifelse.h"
#include "token_print.h"

using namespace std;



int main(int argc, char* argv[]){
	cout<< "Homework 2"<<endl;

	string line;
	
	
	int lineNum = 0;

	while (getline(cin, line) && !cin.eof()) {			//Iterate through each statement
		lineNum++;
		processstatement(Variables, lineNum, line, 0);
		cout << endl;
	}

	printVariables(Variables);
	deleteVariables(Variables);
	
	return 0;	
}

void processstatement(list<variable*> & Variables, int & lineNum, string line, int scopelevel) {
	cout << "inside processstatement: " << line<< " ("<<lineNum<< ")"<<endl;

	int i = 0;							//char index of the statement
	string nextVar;

	while (line[i] == ' ' && i < line.length()) {
		i++;
	}
	while ((isalnum(line[i]) || line[i] == '#') && i < line.length()) {
		nextVar.append(line, i, 1);
		i++;
	}

	if (!line.empty() && !(nextVar[0] == '#')) {

		cout << "nextVar = " << nextVar << endl;

		if (nextVar.compare("def") == 0) {
			//cout << "Function definition" << endl;
			createNewFunc(line, lineNum, Variables, scopelevel);
		}
		else if (nextVar.compare("print") == 0) {
			//cout << "Print statement" << endl;
			print(line,  Variables);
		}
		else if (nextVar.compare("if") == 0) {
			cout << "If/Else statement" << endl;
			cout << "rest of cin" << endl;


			while (!cin.eof()) {
				string dummy;
				getline(cin, dummy);
				cout << dummy << endl;
			}

			list<string> branch;
			int linestoskip = 0;

			ifelse(line, lineNum, Variables, branch, linestoskip);

			cout << "linestoskip=" << linestoskip << endl;

			cin.clear();
			cin.seekg(0, cin.beg);
			for (int i = 0; i < lineNum + linestoskip; i++) {
				getline(cin, line);
			}

			cout << "branchdata" << endl;
			for (list<string>::iterator it = branch.begin(); it != branch.end(); it++)
				cout << (*it) << endl;

			for (list<string>::iterator it = branch.begin(); it != branch.end(); it++) {
				processstatement(Variables, lineNum, (*it), scopelevel);
			}
			cout << endl;
		}
		else if (nextVar.compare("else") == 0) {
			cout << "ERROR: No if for this else" << endl;
		}
		else {
			//cout << "Variable Assignment/Arithmetic" << endl;
			assignment(line, Variables, scopelevel);
		}
	}
	else {
		cout << "Line empty or comment" << endl;
	}
	cout << endl;
}

//IDENTIFY WHAT KIND OF STATEMENT THIS IS
//
//ASSIGNMENT, 
//	1. Keep LHS as it's variable name, change RHS to all constants
//	2. Change LHS to postfix form
//	3. Send line through assignment() to be evaluated

//
//FUNCTION,
//	Idk yet, but it's gonna eventually create a variable with the func name and value
//
//PRINT
//	1. Grab all values from variables
//	2. concatenate the values into a string and cout it
//
//IF/ELSE
//	Idk yet, but it's gonna eventually evaluate x inside if(x) and then branch
//ALSO COMMENTS #
//Comments at the start of line
//Comments in the middle of a line

/*
if (nextVar.compare("def") == 0) {
createNewFunc(line, i, Variables);
}
else if()

else if (isalnum(line[i])) {
while (isalnum(line[i]) && i < line.length()) {
cout << "i=" << i << ", line[i]=" << line[i] << endl;
nextVar.append(line, i, 1);
i++;
}



if (checkifconst(nextVar) == true) {
cout << "nextVar is constant" << endl;
}
else {
//Search for if the variable exists already
//if so add it's value the string in place of variable name
//if not create a new one
createNewVar(nextVar, Variables);
}

cout << "nextVar=" << nextVar << endl;
}

else if (line[i] == '=' || line[i] == '+') {
cout << "next var is an arithmetic operator" << endl;

while (line[i] == '=' || line[i] == '+') {
cout << "i=" << i << ", line[i]=" << line[i] << endl;
nextVar.append(line, i, 1);
i++;
}

cout << "nextVar=" << nextVar << endl;
if (nextVar.compare("=") == 0) {
cout << "Assignment" << endl;

assignment(line);

}

}
*/

#include <iostream>
#include <string>
#include <ctype.h>
#include <list>
#include <stack>
#include <cstdlib>

#include "variable.h"
#include "postfixconverter.h"
#include "token_function.h"
#include "token_assignment.h"
#include "token_ifelse.h"
#include "token_print.h"

using namespace std;

/*
bool checkifconst(string Var) {
	for (int i = 0; i < Var.length(); i++) {
		if (isdigit(Var[i]) == false)
			return false;
	}
	return true;
}
*/

int main(int argc, char* argv[]){
	cout<< "Homework 2"<<endl;
	
	string line;
	list<variable*> Variables;
	int tokenNum = 1;						//id of next token to be created
	int lineNum = 0;

	while (getline(cin, line)){				//Iterate through each statement
		lineNum++;
		cout<<"next statment(" << lineNum << "):"<<line<<endl;					//Current statement
		
		int i = 0;							//char index of the statement

		//IDENTIFY WHAT KIND OF STATEMENT THIS IS
		//
		//IF ASSIGNMENT, 
		//	1. Keep LHS as it's variable name, change RHS to all constants
		//	2. Change LHS to postfix form
		//	3. Send line through assignment() to be evaluated
		//
		//IF FUNCTION,
		//	Idk yet, but it's gonna eventually create a variable with the func name and value
		//
		//IF PRINT
		//	1. Grab all values from variables
		//	2. concatenate the values into a string and cout it
		//
		//IF IF/ELSE
		//	Idk yet, but it's gonna eventually evaluate x inside if(x) and then branch
		//ALSO COMMENTS #


		//Read in next variable and branch

		string nextVar;
			
		while (line[i] == ' ' && i < line.length()) {
			i++;
		}
		while (isalnum(line[i]) && i < line.length()) {
			nextVar.append(line, i, 1);
			i++;
		}

		//cout << "nextVar=" << nextVar << endl;

		if (nextVar.compare("def") == 0) {
			cout << "Function definition" << endl;
			createNewFunc(line, i, Variables);
		}
		else if (nextVar.compare("print") == 0) {
			cout << "Print statement" << endl;
			print();
		}
		else if (nextVar.compare("if") == 0) {
			cout << "If/Else statement" << endl;
			ifelse(line, lineNum, Variables);
		}
		else {
			cout << "Variable Assignment/Arithmetic" << endl;
			assignment(line, Variables);
		}
		cout << endl;
		cout << "finished statement" << endl;
	}
	
	return 0;	
}




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
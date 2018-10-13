#include <iostream>
#include <string>
#include <ctype.h>
#include <list>
#include <stack>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <iomanip>
#include "postfixconverter.h"

#include "variable.h"
list<variable*> Variables;
vector<string> fileLines;



void processstatement(int & lineNum, string line, int lastLine,
	int scopelevel, string scopename);
float computeresult(string exp);
#include "function_type.h"

list<func_type*> Functions;


#include "token_assignment.h"
#include "token_function.h"
#include "token_ifelse.h"
#include "token_print.h"
#include "token_return.h"

using namespace std;



int main(int argc, char* argv[]){
	//cout<< "Homework 2"<<endl;

	string line;
	
	int lineNum = 0;

	while (getline(cin, line) && !cin.eof()) {			//Iterate through each statement
		lineNum++;
		fileLines.push_back(line);
	}

	//cout << "Size of File=" << fileLines.size() << endl;
	int lastLine = fileLines.size() - 1;
	//cout << "lastLine = " << lastLine << endl;

	for (int lineNum = 0; lineNum < fileLines.size(); lineNum++) {
		//cout << "==================MAIN SCOPE BEGIN=====================" << endl;
		processstatement(lineNum, fileLines[lineNum], lastLine, 0, "main");
		//cout << "lineNum after = " << lineNum << endl;
		//cout << "==================MAIN SCOPE END=====================" << endl;
	}

	//printFunctions(Functions);
	//printVariables(Variables);
	deleteVariables(Variables);
	
	return 0;	
}

void processstatement(int & lineNum, string line, int lastLine, 
	int scopelevel, string scopename) {
	//cout << "inside processstatement: " << line<< " ("<<lineNum<< ")"<<endl;
	//cout << "lineNum = " << lineNum << endl;
	//cout << fileLines[lineNum] << endl;
	//cout << "scopename=" << scopename << endl;

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
		
		//cout << "nextVar = " << nextVar << endl;

		if (nextVar.compare("def") == 0) {
			//cout << "Function definition" << endl;
			createNewFunc(line, lineNum, scopelevel);
		}
		else if (nextVar.compare("print") == 0) {
			//cout << "Print statement" << endl;
			print(line, scopelevel);
		}
		else if (nextVar.compare("if") == 0) {
			//cout << "If/Else statement" << endl;
			ifelse(line, lineNum, lastLine, scopelevel, scopename);
		}
		else if (nextVar.compare("else") == 0) {
			cout << "ERROR: No if for this else" << endl;
		}
		else if (nextVar.compare("return") == 0) {
			//cout << "return found" << endl;
			setreturn(line, lineNum, lastLine, scopelevel, scopename);
		}
		else if (line[i] == '(' && line[i + 1] == ')') {
			//cout << "function found" << endl;
			func_type * temp = getFunction(nextVar, Functions);
			//cout << "temp=" << temp->name << endl;

			temp->execute();
				
		}
		else {
			//cout << "Variable Assignment/Arithmetic" << endl;
			assignment(line, scopelevel, scopename);
		}
	}
	else {
		//cout << "Line empty or comment" << endl;
	}
	//cout << endl;
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


float computeresult(string exp) {
	//cout << "inside computeresult" << endl;
	//cout <<"expression="<< exp << endl;

	list<string> explist;
	int i = 0;
	while (exp[i] == ' ')
		i++;

	while (i < exp.length()) {
		string toadd = "";
		while (i < exp.length() && exp[i] != ' ') {
			toadd += exp[i];
			i++;
		}
		//cout << toadd << endl;
		while (exp[i] == ' ')
			i++;
		explist.push_back(toadd);
	}

	stack<float> numbers;

	while (explist.size() != 0) {
		if (explist.front().compare("+") != 0 && explist.front().compare("-") != 0 &&
			explist.front().compare("*") != 0 && explist.front().compare("/") != 0) {
			//cout << "number found" << endl;
			float tempfloat = stof(explist.front());
			numbers.push(tempfloat);
			explist.pop_front();
		}
		else {
			//cout << "operator found" << endl;
			char op = explist.front()[0];
			explist.pop_front();

			float term2 = numbers.top();
			numbers.pop();
			float term1 = numbers.top();
			numbers.pop();
			float term3;

			//cout << "term1=" << term1 << " term2=" << term2 << endl;

			switch (op) {
			case('+'):
				term3 = term1 + term2;
				break;
			case('-'):
				//cout << "subtraction" << endl;
				term3 = term1 - term2;
				break;
			case('*'):
				//cout << "multiplication" << endl;
				term3 = term1 * term2;
				break;
			case('/'):
				//cout << "division" << endl;
				term3 = term1 / term2;
				break;
			default:
				//cout << "error" << endl;
				break;
			}

			//cout << "term3 = " << term3 << endl;
			numbers.push(term3);
		}
	}

	return numbers.top();
}
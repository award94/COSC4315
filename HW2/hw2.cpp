#include <iostream>
#include <string>
#include <ctype.h>
#include <list>
#include <cstdlib>

#include "variable.h"
#include "postfixconverter.h"
#include "token_function.h"
#include "token_variable.h"

using namespace std;

bool checkifconst(string Var) {
	for (int i = 0; i < Var.length(); i++) {
		if (isdigit(Var[i]) == false)
			return false;
	}
	return true;
}

int main(int argc, char* argv[]){
	cout<< "Homework 2"<<endl;
	
	string line;
	list<variable*> Variables;
	int tokenNum = 1;						//id of next token to be created
	
	while (getline(cin, line)){				//Iterate through each statement
		cout<<line<<endl;					//Current statement
		list<string> currentline;

		int i = 0;							//char index of the statement

		while (i < line.length()) {

			//Read in next variable
			while (line[i] == ' ' && i < line.length())
				i++;

			string nextVar;

			if (isalnum(line[i])) {
				while (isalnum(line[i]) && i < line.length()) {
					cout << "i=" << i << ", line[i]=" << line[i] << endl;
					nextVar.append(line, i, 1);
					i++;
				}

				if (nextVar.compare("func") == 0) {
					createNewFunc(line, i, Variables);
				}
				else if (checkifconst(nextVar) == true) {
					cout << "nextVar is constant" << endl;
				}
				else {
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
			}
		}
	}
	printVariables(Variables);
	deleteVariables(Variables);
	
	return 0;	
}

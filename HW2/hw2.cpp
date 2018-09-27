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

bool checkifconst(string token) {
	for (int i = 0; i < token.length(); i++) {
		if (isdigit(token[i]) == false)
			return false;
	}
	return true;
}

int main(int argc, char* argv[]){
	cout<< "Homework 2"<<endl;
	cout << checkifconst("1") << endl;

	postfixconverter pfx;
	bool temp = pfx.precedence('a', 'b');
	pfx.convertToPostfix();
	
	string line;
	list<token*> Tokens;
	int tokenNum = 1;						//id of next token to be created
	
	while (getline(cin, line)){				//Iterate through each statement
		cout<<line<<endl;					//Current statement
		
		int i = 0;							//char index of the statement
		while (i < line.length()) {

			//Read in next token
			while (line[i] == ' ' && i < line.length())
				i++;

			string nextToken;

			if (isalnum(line[i])) {
				while (isalnum(line[i]) && i < line.length()) {
					cout << "i=" << i << ", line[i]=" << line[i] << endl;
					nextToken.append(line, i, 1);
					i++;
				}

				if (nextToken.compare("func") == 0) {
					createNewFunc(line, i, Tokens);
				}
				else if (checkifconst(nextToken) == true) {
					cout << "nextToken is constant" << endl;
				}
				else {
					createNewVar(nextToken, Tokens);
				}

				cout << "nextToken=" << nextToken << endl;
			}

			else if (line[i] == '=' || line[i] == '+') {
				cout << "next token is an arithmetic operator" << endl;

				while (line[i] == '=' || line[i] == '+') {
					cout << "i=" << i << ", line[i]=" << line[i] << endl;
					nextToken.append(line, i, 1);
					i++;
				}

				cout << "nextToken=" << nextToken << endl;
			}
		}
	}
	printTokens(Tokens);
	deleteTokens(Tokens);
	
	return 0;	
}

using namespace std;

void convertToConstants(string & line, string & RHS,
	string & LHS, int scopelevel);

void assignment(string line, int scopelevel, string scopename) {
	cout <<endl<< "==========ASSIGNMENT SCOPE BEGIN============" << endl;
	//cout << line << endl;
	//cout << "scope = " << scopelevel << endl;
	//printVariables(Variables);
	string RHS;
	string LHS;
	string pfxRHS;

	//converts RHS to a series of constants
	convertToConstants(line, RHS, LHS, scopelevel);
	//cout << "convertToConstants done" << endl;
	//converts RHS to postfix notation
	postfixconverter converter;
	//cout << "RHS:" << RHS << endl;
	pfxRHS = converter.convertToPostfix(RHS);
	//cout << "postfixconversion done" << endl;

	//computes result
	float result = computeresult(pfxRHS);
	//cout << "result computed" << endl;
	//assigns result to LHS Variable
	variable * lhsvar = getvariablescope(LHS, Variables, scopelevel);
	lhsvar->value = result;
	//cout << lhsvar->name << '=' << lhsvar->value << endl;
	lhsvar = NULL;
	cout << "==========ASSIGNMENT SCOPE END============" << endl;
}

void convertToConstants(string & line, string & RHS,
	string & LHS, int scopelevel) {
	//cout << "inside convertToConstants" << endl;
	//cout << "line=" << line << endl;
	int i = 0;

	//parse LHS variable

	while (line[i] == ' ')
		i++;

	while (isalnum(line[i])) {
		LHS.append(line, i, 1);
		i++;
	}
	//cout << "LHS=" << LHS << ';' << endl;

	//Check if LHS Var has been declared yet
	//If not, declare it
	if (!checkforvariableinscope(LHS, Variables, scopelevel)) {
		//cout << "creating new variables in scope" << scopelevel << endl;
		createNewVar(LHS, Variables, scopelevel);
		//printVariables(Variables);
	}
	else {
		string nothing = "nothing";
		//cout << "found new variable in scope" << scopelevel << endl;
	}
	//cout << "LHS Found or declared" << endl;

	//cout << "line[i]=" << line[i] << ';' << int(line[i])<<';'<<endl;
	//Skipping whitespaces
	while (line[i] == ' ')
		i++;

	//cout << "line[i]=" << line[i] << ';' << endl;

	//Error checking for '='
	if (line[i] != '=')
		cout << "Error invalid assignment format" << endl;
	else
		i++;

	while (line[i] == ' ')
		i++;

	//cout << "Found = " << endl;

	//Finding First term in RHS
	string tempterm;
	/*
	if (line[i] == '-') {
		tempterm += line[i];
		i++;
	}

	while (isalnum(line[i])) {
		//cout << line[i] << endl;
		tempterm.append(line, i, 1);
		i++;
	}

	//cout <<"tempterm="<< tempterm << endl;
	if ((i + 2) <= line.length()) {
		//cout << "next 2:"<<line[i] << line[i + 1] << endl;
		if (line[i] == '(' && line[i + 1] == ')') {
			i += 2;
		}
	}
	*/

	stack<char> parenstack;
	while (i < line.length()) {
		if ((line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/' || 
			line[i] == ' ')&& parenstack.empty()) {
			break;
		}
		if (line[i] == '(') {
			parenstack.push('(');
		}
		if (line[i] == ')') {
			parenstack.pop();
		}
		tempterm += line[i];
		i++;
	}


	//cout << "tempterm=" << tempterm << ';' << endl;

	//If constant append it to RHS
	//If variable lookup value and append it to RHS

	RHS += evaluatenewterm(tempterm, scopelevel);
	/*
	if (checkifconst(tempterm)) {
		//cout << "is a constant: " << tempterm <<";"<< endl;
		RHS.append(tempterm);
		RHS += ' ';
	}
	else {
		//cout << "variable:" << tempterm<<endl;

		string getfuncname;
		int i = 0;
		while (tempterm[i] != '(' && i < tempterm.length()) {
			getfuncname += tempterm[i];
			i++;
		}
		cout << "getfuncname=" << getfuncname << endl;

		if (checkforfunction(getfuncname, Functions)) {
			//cout << "found function" << endl;
			func_type * temp = getFunction(getfuncname, Functions);

			if (temp->doesreturn) {
				//cout << temp->returnvalue << endl;
				temp->setreturn(tempterm);

				RHS += to_string(temp->returnvalue);
				RHS += ' ';
			}
			else {
				cout << "ERROR: Function does not return a value" << endl;
			}

			temp = NULL;
		}
		else {
			for (int j = scopelevel; j >= 0; j--) {
				//cout << "scope=" << j << endl;

				if (checkforvariableinscope(tempterm, Variables, j)) {
					//cout << "found variable in this scope:" << j << endl;
					variable * temp = getvariablescope(tempterm, Variables, j);
					RHS += to_string(temp->value);
					RHS += ' ';
					temp = NULL;
					break;
				}
				else
					cout << "error: variable does not exist:" << tempterm << endl;
			}
		}
	}
	*/

	//RHS After first time is appended
	//cout << "RHS=" << RHS << endl;
	//cout << i << ' ' << line.length() << endl;

	//Loops through rest of RHS
	//Finds Opertator and appends to RHS
	//Then finds Constant and appends to RHS
	while (i < line.length()) {
		tempterm = "";
		//cout << line[i] << endl;

		//cout << "inside loop" << endl;
		while (line[i] == ' ') {
			i++;
		}
		//cout << line[i] << endl;

		if (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/') {
			tempterm.append(line, i, 1);
			i++;
		}
		//cout << i<<" tempterm=" << tempterm << 'a'<<endl;
		//cout << tempterm.compare("-") << endl;

		if ((tempterm.compare("+") == 0) || (tempterm.compare("-") == 0 ||
			tempterm.compare("*") == 0) || (tempterm.compare("/") == 0)) {
			//cout << "operator=" << tempterm << endl;
			RHS.append(tempterm);
			RHS += ' ';
		}

		while (line[i] == ' ')
			i++;

		tempterm = "";

		if (line[i] == '-') {
			tempterm += line[i];
			i++;
		}

		stack<char> parenstack2;
		while (i < line.length()) {
			if ((line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/' ||
				line[i] == ' ') && parenstack2.empty()) {
				break;
			}
			if (line[i] == '(') {
				parenstack2.push('(');
			}
			if (line[i] == ')') {
				parenstack2.pop();
			}
			tempterm += line[i];
			i++;
		}

		while (line[i] == ' ')
			i++;

		//cout << tempterm << endl;

		RHS += evaluatenewterm(tempterm, scopelevel);

		/*
		if (checkifconst(tempterm)) {
			//cout << "is a constant:" <<tempterm<<";"<< endl;
			RHS.append(tempterm);
			RHS += ' ';
		}
		else {
			//cout << "variable:" << tempterm << endl;

			string getfuncname;
			int i = 0;
			while (tempterm[i] != '(' && i < tempterm.length()) {
				getfuncname += tempterm[i];
				i++;
			}
			cout << "getfuncname=" << getfuncname << endl;
			if (checkforfunction(getfuncname, Functions)) {
				//cout << "found function" << endl;
				func_type * temp = getFunction(tempterm, Functions);
				//cout << temp->returnvalue << endl;

				

				if (temp->doesreturn) {
					temp->setreturn(tempterm);
					RHS += to_string(temp->returnvalue);
					RHS += ' ';
				}
				else
					cout << "ERROR: Function does not return" << endl;

				temp = NULL;
			}
			else {
				for (int j = scopelevel; j >= 0; j--) {
					//cout << "scope=" << j << endl;

					if (checkforvariableinscope(tempterm, Variables, j)) {
						//cout << "found variable in this scope:" << j << endl;
						variable * temp = getvariablescope(tempterm, Variables, j);
						RHS += to_string(temp->value);
						RHS += ' ';
						temp = NULL;
						break;
					}
					else
						cout << "error: variable does not exist:" << tempterm << endl;
				}
			}
		}
		*/

		//cout << "RHS=" << RHS << endl;
	}
}


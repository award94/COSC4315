using namespace std;

void findargument(string line, int & parenthesis1, int & parenthesis2);

void print(string line) {
// Argument is used as a temporary variable to hold the contents before the delimiter
	// When the delimiter is reached, the strings are checked and appended to finalOutputt
	string argument;
	string finalOutput;
		
	int i = 0;
	int parenthesis1;
	int parenthesis2;
	string arg;
	
	
	findargument(line, parenthesis1, parenthesis2);
	
	arg.append(line, parenthesis1+1, parenthesis2 - parenthesis1-1);
	
	do {
		// Remove whitespace
		if (arg[i] == ' ') {
			//cout << "Whitespace removed" << endl;
			i++;
		}
		// Takes care of constants
		if (arg[i] == '"') {
			//cout << "First quote encountered " << endl;
			i++;
			while (arg[i] != '"') {
				//cout << "Searching for second quote " << endl;
				argument += arg[i];
				i++;
			}
			finalOutput += argument;
			finalOutput += ' ';
			argument.clear();
			// Need a second increment to skip over the comma
			i++;
		} 
		// Starting the check to see if arg is a variable
		if (arg[i] != ',') {
			//cout << "Searching for a comma " << endl;
			argument += arg[i];
			i++;
		}	
		if (arg[i] == ',' || i == arg.length()) {
		// Seems like this block of code is repeated later
		
		// Testing for duplicate
	while (i < arg.length()) {
		//cout << line[i] << endl;

		//cout << "inside loop" << endl;
		
		while (arg[i] == ' ') {
			i++;
		}
		cout << arg[i] << endl;

		if (arg[i] == '+' || arg[i] == '-' || arg[i] == '*' || arg[i] == '/') {
			argument.append(arg, i, 1);
			i++;
		}
		//cout << i<<" tempterm=" << tempterm << 'a'<<endl;
		//cout << tempterm.compare("-") << endl;

		if ((argument.compare("+") == 0) || (argument.compare("-") == 0 ||
			argument.compare("*") == 0) || (argument.compare("/") == 0)) {
			//cout << "operator=" << argument << endl;
			finalOutput.append(argument);
			finalOutput += ' ';
			// Testing
			argument.clear();
			i++;
		}

		while (arg[i] == ' ')
			i++;

		//argument = "";

		if (arg[i] == '-') {
			argument += arg[i];
			i++;
		}

		while (isalnum(arg[i])) {
			//cout << line[i] << endl;
			argument.append(arg, i, 1);
			i++;
		}

		if ((i + 2) <= arg.length()) {
			//cout << "next 2:"<<line[i] << line[i + 1] << endl;
			if (arg[i] == '(' && arg[i + 1] == ')') {
				i += 2;
			}
		}

		while (arg[i] == ' ')
			i++;
// End of insertion		

			//If constant append it to RHS
	// Changed the argument//If variable lookup value and append it to RHS
	if (checkifconst(argument)) {
		//cout << "is a constant: " << argument <<";"<< endl;
		finalOutput.append(argument);
		finalOutput += ' ';
		//Testing
		argument.clear();
		i++;
	}
	else {
		//cout << "variable:" << argument <<endl;
		if (checkforfunction(argument, Functions)) {
			//cout << "found function" << endl;
			func_type * temp = getFunction(argument, Functions);
			cout << temp->returnvalue << endl;

			finalOutput += to_string(temp->returnvalue);
			finalOutput += ' ';

			temp = NULL;
			// Testing
			i++;
		}
		else {
			for (int j = 2; j >= 0; j--){
			//for (int j = scopelevel; j >= 0; j--) {
				cout << "scope=" << j << endl;

				if (checkforvariableinscope(argument, Variables, j)) {
					//cout << "found variable in this scope:" << j << endl;
					variable * temp = getvariablescope(argument, Variables, j);
					finalOutput += to_string(temp->value);
					finalOutput += ' ';
					temp = NULL;
					// Testing
					i++;
					argument.clear();
					break;
				}
				else
					cout << "error: variable does not exist:" << argument << endl;
			}
		}
	}
	

	//RHS After first time is appended
	//cout << "RHS=" << RHS << endl;
	//cout << i << ' ' << line.length() << endl;

	//Loops through rest of RHS
	//Finds Opertator and appends to RHS
	//Then finds Constant and appends to RHS
				
		finalOutput += argument;
			// Delete 
		finalOutput += ' ';
			// Delete
		argument.clear();
		i++;
		
		}
	} // Added in

	} while (i < arg.length());


	cout << "Line is: " << line << endl;
	cout << "arg=" << arg << endl;
	cout << "Final output is: " << finalOutput << endl;
}

void findargument(string line, int & parenthesis1, int & parenthesis2) {
	int i = 0;
	while (i < line.length()) {
		while (line[i] != '(' && i < line.length())
			i++;
		if (line[i] == '(' && line[i + 1] != ')') {
			parenthesis1 = i;
			break;
		}
		else
			i++;
	}
	i = 0;
	while (i < line.length()) {
		while (line[i] != ')' && i < line.length()) {
			i++;
		}
		if (line[i] == ')' && line[i - 1] != '(') {
			parenthesis2 = i;
			break;
		}
		else
			i++;
	}
	cout << "p1=" << parenthesis1 << " p2=" << parenthesis2 << endl;
}

	

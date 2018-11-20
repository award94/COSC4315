using namespace std;

class func_type{
	public:
		string name;
		
		int startline;
		int endline;
		int scope;

		void createarglist();
		vector<string> arglist;

		string defline;

		int returnvalue;
		bool doesreturn;
		int returnline;

		void findfuncname();
		int findlastline();
		func_type();

		void execute(int stackscope, int nestlevel);	
		void checkreturn();
		void setreturn(string funccall, int stackscope, int nestlevel);
		void getreturn();

		vector<string> parsedfuncparam(string funccall);
};

void func_type::createarglist() {
	//cout << "inside createarglist()" << endl;
	//cout << "defline=" << defline << endl;
	int i = 0;
	while (defline[i] != '(')
		i++;
	i++;
	int argstart = i;
	stack<char> parenstack;

	while (i < defline.length()) {
		if (parenstack.empty() && defline[i] == ')')
			break;
		if (defline[i] == '(')
			parenstack.push('(');
		if (defline[i] == ')')
			parenstack.pop();
		i++;
	}

	string argument;
	argument.append(defline, argstart, i-argstart);
	//cout << "argument=" << argument << ';'<<endl;

	i = 0;
	while (i < argument.length()) {
		string temp;
		while (argument[i] == ' ' && i < argument.length())
			i++;
		while (argument[i] != ',' && i < argument.length()) {
			temp += argument[i];
			i++;
		}
		if (argument[i] == ',' && i < argument.length())
			i++;
		arglist.push_back(temp);
	}
	for (int j = 0; j < arglist.size(); j++) {
		//cout << arglist[j] << endl;
	}
}

void func_type::execute(int stacklevel, int nestlevel) {
	//cout << "inside execute()" << endl;
	//cout << "scope=" << stacklevel << endl;
	//cout << "startline=" << startline << endl;
	//cout << "returnline=" << returnline << endl;
	//cout << "endline=" << endline << endl;

	int i = startline + 1;
	string currentLine;

	if (returnline != -1) {
		for (; i <= returnline; i++) {
			currentLine = fileLines[i];
			//cout << currentLine << endl;
			
			if (!currentLine.empty()) {
				bool lineinscope = 1;
				for (int j = 0; j < scope * 3; j++) {
					if (currentLine[j] != ' ')
						lineinscope = 0;
				}
				//cout << "lineinscope=" << lineinscope << endl;
				if (currentLine[(scope * 3)] == ' ') {
					//cout << "funcscope=" << funcscope << endl;
					//cout << currentLine[(funcscope * 3)] << endl;
					lineinscope = 0;
				}
				//cout << "lineinscope=" << lineinscope << endl;
				//cout << "isthisline in scope=" << lineinscope << endl;
				if (lineinscope)
					processstatement(i, currentLine, endline, stacklevel, name, nestlevel);
			}

		}
	}
	else {
		for (; i <= endline; i++) {
			currentLine = fileLines[i];
			//cout << currentLine << endl;

			if (!currentLine.empty()) {
				bool lineinscope = 1;
				for (int j = 0; j < scope * 3; j++) {
					if (currentLine[j] != ' ')
						lineinscope = 0;
				}
				//cout << "lineinscope=" << lineinscope << endl;
				if (currentLine[(scope * 3)] == ' ') {
					//cout << "funcscope=" << funcscope << endl;
					//cout << currentLine[(funcscope * 3)] << endl;
					lineinscope = 0;
				}
				//cout << "lineinscope=" << lineinscope << endl;
				//cout << "isthisline in scope=" << lineinscope << endl;
				if (lineinscope)
					processstatement(i, currentLine, endline, stacklevel, name, nestlevel);
			}
		}
	}

	deleteScope(Variables, stacklevel);
}

void func_type::checkreturn() {
	//cout << "inside checkreturn()" << endl;
	for (int i = startline; i <= endline; i++) {
		//cout << fileLines[i] << endl;
		string currentline = fileLines[i];

		int j = 0;
		string firstvar;
		while (currentline[j] == ' ')
			j++;
		while (isalnum(currentline[j]))
			firstvar += currentline[j++];
		if (firstvar.compare("return") == 0) {
			//cout << "found a return" << endl;
			doesreturn = true;
			returnline = i;
			return;
		}
	}
	doesreturn = false;
}

vector<string> func_type::parsedfuncparam(string funccall) {
	
	//cout << "inside parsedfuncparam()" << endl;
	//cout << "funccall=" << funccall << endl;
	vector<string> parameters;
	
	int i = 0;
	stack<char> parenstack2;
	string temp;
	/*
	string funccallargument;
	while (funccall[i] != '(')
		i++;
	i++;
	while (i < funccall.length()) {
		if (funccall[i] == ')' && parenstack2.empty())
			break;
		if (funccall[i] == '(')
			parenstack2.push('(');
		if (funccall[i] == ')' && !parenstack2.empty())
			parenstack2.pop();

		cout << funccall[i] << ' ' << parenstack2.empty()<<endl;

		
		funccallargument += funccall[i];
		i++;
	}
	*/
	string funccallargument = funccall;
	//cout << "funccallargument=" << funccallargument << endl;

	i = 0;
	stack<char> parenstack;
	while (i < funccallargument.length()) {
		if (funccallargument[i] == '(')
			parenstack.push('(');
		if (funccallargument[i] == ')')
			parenstack.pop();
		if (funccallargument[i] == ',' && parenstack.empty()) {
			//cout << "pushing temp=" << temp << endl;
			parameters.push_back(temp);
			temp = "";
			i++;
		}
		else {
			if( funccallargument[i] != ' ')
				temp += funccallargument[i];
			//cout << "temp=" << temp << endl;
			i++;
		}
	}
	//cout << "pushing to parameters=" << temp << ';' << endl;
	if(temp.compare("") != 0)
		parameters.push_back(temp);
	
	return parameters;
	
}

void func_type::setreturn(string funccall, int stackscope, int nestlevel) {
	//cout << "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl;
	//cout << "inside setreturn() stackdepth=" << stackscope<<endl;
	if (stackscope >= 2000) {
		//cout << "INFINITE RECURSION" << endl;
		recursionList[recursionList.size() - 1] = "No";
		return;
	}
	//cout << "returnline=" << returnline << endl;
	//cout << "funccall=" << funccall << endl;

	//---------------THIS PART CREATES LOCAL VARIABLES BASED ON PARAMETERS
	
	vector<string> parameters = parsedfuncparam(funccall);

	if (parameters.size() != arglist.size()) {
		cout << "ERROR: Parameters don't match function arguments; " << funccall << endl;
		//cout << parameters.size() << ' ' << arglist.size() << endl;
	}

	//cout << "arglist:" << endl;
	for (int k = 0; k < arglist.size(); k++) {
		//cout << arglist[k] << endl;
	}
	//cout << "parameters:" << endl;
	for (int k = 0; k < parameters.size(); k++) {
		//cout << parameters[k] << endl;
	}

	for (int i = 0; i < parameters.size(); i++) {
		createNewVar(arglist[i], Variables, stackscope);
		variable * temp = getvariablescope(arglist[i], Variables, stackscope);
		temp->value = stof(parameters[i]);
		temp = NULL;
	}

	//cout << "assigned parameters" << endl;

	//printVariables(Variables);

	//---------------------------------------------------------------------------


	//-----------THIS PART EXECUTES ALL STATEMENTS WITHIN THE FUNCTION SCOPE------
	for (int i = startline+1; i < returnline; i++) {
		//cout << "\t\t\t"<<fileLines[i] << endl;
		string currentLine = fileLines[i];

		if (!currentLine.empty()) {
			bool lineinscope = 1;
			for (int j = 0; j < scope * 3; j++) {
				if (currentLine[j] != ' ')
					lineinscope = 0;
			}
			//cout << "lineinscope=" << lineinscope << endl;
			if (currentLine[(scope * 3)] == ' ') {
				//cout << "funcscope=" << funcscope << endl;
				//cout << currentLine[(funcscope * 3)] << endl;
				lineinscope = 0;
			}
			//cout << "lineinscope=" << lineinscope << endl;
			//cout << "isthisline in scope=" << lineinscope << endl;
			if (lineinscope) {
				string nextvar;
				int k = 0;
				while (currentLine[k] == ' ') {
					k++;
				}
				while (isalnum(currentLine[k])) {
					nextvar += currentLine[k];
					k++;
				}
				if (!(nextvar.compare("print") == 0)) {
					processstatement(i, currentLine, endline, stackscope, name, nestlevel);
				}
			}
		}
	}

	//------------------------------------------------------------------------------



	//------------------------THIS PART COMPUTES THE RETURN VALUE-------------------
	//cout << "computing return value now" << endl;

	string alreadypassed;
	string RHS;
	int i = 0;


	//SKIPPING return
	string line = fileLines[returnline];

	while (line[i] == ' ' && i < line.length()) {
		alreadypassed += line[i];
		i++;
	}
	while (isalnum(line[i]) && i < line.length()) {
		alreadypassed += line[i];
		i++;
	}
	while (line[i] == ' ' && i < line.length()) {
		alreadypassed += line[i];
		i++;
	}

	//cout << "alreadypassed:" << alreadypassed << ';' << endl;

	//EVALUATING THE RETURN VALUE
	string tempterm;

	while (line[i] == ' ')
		i++;

	if (line[i] == '-') {
		tempterm += line[i];
		i++;
	}

	stack<char> parenstack;
	while (i < line.length()) {
		if ((line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/' ||
			line[i] == ' ') && parenstack.empty()) {
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

	RHS += evaluatenewterm(tempterm, stackscope, nestlevel);

	while (line[i] == ' ')
		i++;

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
		else {
			//cout << "operator missing" << endl;
		}
		//cout << i << " tempterm=" << tempterm << 'a' << endl;
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

		RHS += evaluatenewterm(tempterm, stackscope, nestlevel);
	}

	/*
	while (isalnum(line[i])) {
		tempTerm += line[i];
		i++;
	}
	if ((i + 2) <= line.length()) {
		//cout << "next 2:"<<line[i] << line[i + 1] << endl;
		if (line[i] == '(' && line[i + 1] == ')') {
			tempTerm += "()";
			i += 2;
		}
	}

	if (checkifconst(tempTerm)) {
		//cout << "constant value" << endl;
		RHS += tempTerm;
		RHS += ' ';
	}
	else {
		//cout << "not a constant value" << endl;
		for (int j = scope; j >= 0; j--) {
			//cout << "scope=" << j << endl;
			if (checkforvariableinscope(tempTerm, Variables, j)) {
				//cout << "found variable in this scope:" << j << endl;
				variable * temp = getvariablescope(tempTerm, Variables, j);
				//cout << "value=" << temp->value << endl;
				RHS += to_string(temp->value);
				RHS += ' ';
				temp = NULL;
				break;
			}
			else
				cout << "error: variable does not exist:" << tempTerm << endl;
		}
	}

	while (line[i] == ' ') {
		i++;
	}

	while (i < line.length()) {
		tempTerm = "";

		while ((!isalnum(line[i]) && line[i] != ' ') && i < line.length()) {
			tempTerm += line[i];
			i++;
		}
		if ((tempTerm.compare("+") == 0) || (tempTerm.compare("-") == 0 ||
			tempTerm.compare("*") == 0) || (tempTerm.compare("/") == 0)) {
			RHS += tempTerm;
			RHS += ' ';
		}

		while (line[i] == ' ' && i < line.length())
			i++;

		tempTerm = "";

		if (line[i] == '-') {
			tempTerm += line[i];
			i++;
		}

		while (isalnum(line[i]) && i < line.length()) {
			//cout << line[i] << endl;
			tempTerm.append(line, i, 1);
			i++;
		}
		if ((i + 2) <= line.length()) {
			//cout << "next 2:"<<line[i] << line[i + 1] << endl;
			if (line[i] == '(' && line[i + 1] == ')') {
				tempTerm += "()";
				i += 2;
			}
		}

		while (line[i] == ' ' && i < line.length())
			i++;

		if (checkifconst(tempTerm)) {
			RHS += tempTerm;
			RHS += ' ';
		}
		else {
			for (int j = scope; j >= 0; j--) {
				//cout << "scope=" << j << endl;
				if (checkforvariableinscope(tempTerm, Variables, j)) {
					//cout << "found variable in this scope:" << j << endl;
					variable * temp = getvariablescope(tempTerm, Variables, j);
					//cout << "value=" << temp->value << endl;
					RHS += to_string(temp->value);
					RHS += ' ';
					temp = NULL;
					break;
				}
				else
					cout << "error: variable does not exist:" << tempTerm << endl;
			}
		}
	}

	*/

	//cout << "RHS:" << RHS << 'a'<<endl;
	//for (int i = 0; i < RHS.length(); i++) {
	//	if (RHS[i] != ' ' && RHS[i] != '\n')
	//		empty = 0;
	//}
	//cout << "empty=" << empty << endl;
	//if (empty == 0) {
	postfixconverter converter;
	RHS = converter.convertToPostfix(RHS);
	//cout << "RHS:" << RHS << ';' << endl;
	//returnvalue = computeresult(RHS);
	//cout << "returnvalue inside func_type=" << returnvalue << endl;
	//returnvalue = temp->value;
	//temp = NULL;
	//}
	//else
	//	cout << "no return value" << endl;
	//cout << "Variables after computing return value within func_type()" << endl;	
	//printVariables(Variables);
	deleteScope(Variables, stackscope);
}

void func_type::getreturn() {
	//cout << "inside getreturn()" << endl;
}

void func_type::findfuncname() {
	//cout << "inside findfuncname()" << endl;

	int i = 0;

	while (defline[i] == ' ')
		i++;

	while (isalnum(defline[i]))
		i++;

	while (defline[i] == ' ')
		i++;

	while (isalnum(defline[i]) && i < defline.length()) {
		name += defline[i];
		i++;
	}

	//cout << "name=" << name << endl;
}

int func_type::findlastline() {
	//cout << "inside findlastline()" << endl;

	
	//cout << "findlastline" << endl;
	//cout << startline << endl;
	//cout << "filesize=" << fileLines.size() << endl;

	int i = startline;
	while (i < fileLines.size() - 1) {
		i++;
		string currentLine = fileLines[i];

		int k = 0;
		string commentCheck;
		while (currentLine[k] == ' ' && k < currentLine.length()) {
			k++;
		}
		while ((isalnum(currentLine[k]) || currentLine[k] == '#') && k < currentLine.length()) {
			commentCheck += currentLine[k];
			k++;
		}

		if (!currentLine.empty() && (commentCheck[0] != '#')) {
			//cout << currentLine << " ("<<i<<")"<<endl;

			bool checkscope = 1;
			for (int j = 0; j < 3 * scope; j++) {
				//cout << currentLine[j];
				if (currentLine[j] != ' ') {
					checkscope = 0;
				}
			}
			//cout << "checkscope=" << checkscope << endl;
			if (checkscope == 0) {
				i -= 1;
				break;
			}
		}
	}
	//cout << "endline=" << i << endl;
	endline = i;
	
}

func_type::func_type() {
	returnline = -1;
	doesreturn = false;
}

void printFunctions(list<func_type*> & Functions) {
	//cout << "All functions in system" << endl;

	func_type * temp = NULL;
	for (list<func_type*>::iterator it = Functions.begin();
		it != Functions.end(); it++) {
		cout << "name=" << (*it)->name << " scope="<<(*it)->scope<< " value="<< (*it)->returnvalue<< 
			" returnvalue=" << (*it)->returnvalue << " startline=" << (*it)->startline << 
			" endline=" << (*it)->endline << endl;
	}
}

bool checkforfunction(string name, list<func_type*> & Functions) {
	//cout << "inside checkforFunction()" << endl;
	//cout << name << endl;
	for (list<func_type*>::iterator it = Functions.begin();
		it != Functions.end(); it++) {
		//cout << (*it)->name << endl;
		if ((*it)->name.compare(name) == 0) {
			return true;
		}
	}
	return false;
}

func_type * getFunction(string name, list<func_type*> & Functions) {
	//cout << "inside getFunction" << endl;
	//cout << "funcname=" << name << ";"<<endl;

	func_type * temp = NULL;
	for (list<func_type*>::iterator it = Functions.begin();
		it != Functions.end(); it++) {
		if ((*it)->name == name) {
			//cout << "found the function" << endl;
			temp = (*it);
			return temp;
		}
	}
	cout << "Function is not defined" << endl;
	return NULL;	
}

func_type * getFunctionScope(string name, list<func_type*> & Functions, int stackscope) {
	//cout << "inside getFunctionScope" << endl;
	//cout << "funcname=" << name << " scope="<<stackscope<<";"<<endl;

	//printFunctions(Functions);

	func_type * temp = NULL;
	for (list<func_type*>::iterator it = Functions.begin(); it != Functions.end(); it++) {
		if ((*it)->name == name && (*it)->scope == stackscope) {
			//cout << "found the function" << endl;
			temp = (*it);
			return temp;
		}
	}
	cout << "Function is not defined" << endl;
	return NULL;
}

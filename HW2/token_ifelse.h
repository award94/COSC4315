using namespace std;

string getarg(string ifline);
bool evaluatearg(string arg);
list<string> findbranchdata(list<string> & branch, bool iftruth, int & linestoskip);
int findlastlineifelse(int startLineNum, int & elseline, int currentscope);

string parseexpr(string line);

void ifelse(string ifline, int & iflineNum, int funclastline, 
	int prevscope, string scopename) {
	//cout << endl<<"============IF ELSE SCOPE BEGIN==========" << endl;
	

	int currentscope = prevscope;
	//cout << "scopelevel=" << currentscope << endl;
	//cout << "scopename=" << scopename << endl;

	int elseline = -1;
	int lastline = findlastlineifelse(iflineNum, elseline, currentscope+1);
	
	//cout << "if start line Num=" << iflineNum << endl;
	//cout << "else start line=" << elseline << endl;
	//cout << "if/else last line=" << lastline << endl;
	//cout << "function last line=" << funclastline << endl;
	
	

	string line;
	string firstWord;

	string arg = getarg(ifline);
	//cout << "arg=" << arg << endl;
	bool iftruth = evaluatearg(arg);
	//cout << "iftruth=" << iftruth << endl;

	if (iftruth == 1) {
		if (elseline == -1) {
			//cout << "start1" << endl;
			int i = iflineNum + 1;
			for (; i <= lastline; i++) {
				//cout << "i=" << i <<endl;
				string currentLine = fileLines[i];
				processstatement(i, currentLine, funclastline, currentscope, scopename);
			}
			iflineNum = i;
			//cout << "iflineNum=" << iflineNum << endl;
			//cout << "done1" << endl;
		}
		else {
			int i = iflineNum + 1;
			//cout << "start2" << endl;
			for (; i < elseline; i++) {
				//cout << "i=" << i << endl;
				string currentLine = fileLines[i];
				processstatement(i, currentLine, funclastline, currentscope, scopename);
			}
			iflineNum = i;
			//cout << "iflineNum=" << iflineNum << endl;
			//cout << "done2" << endl;
		}
	}
	else {
		if (elseline == -1) {
			//cout << "start3" << endl;
			iflineNum = lastline;
			//cout << "done3" << endl;
		}
		else {
			int i = elseline + 1;
			//cout << "start4" << endl;
			for (; i <= lastline; i++) {
				//cout << "i=" << i << endl;
				string currentLine = fileLines[i];
				processstatement(i, currentLine, funclastline, currentscope, scopename);
			}
			iflineNum = i;
			
			//cout << "done4" << endl;
		}
	}

	iflineNum = lastline;
	//cout << "lineNum=" << iflineNum << endl;
	//cout << "============IF ELSE SCOPE END==========" << endl;
	
}

int findlastlineifelse(int startLineNum, int & elseline, int currentscope) {
	//cout << "findlastline" << endl;
	//cout << "currentscope=" << currentscope << endl;
	//cout << "filesize=" << fileLines.size() << endl;
	int i = startLineNum+1;
	for(; i < fileLines.size(); i++){
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

		if (!fileLines[i].empty() && (commentCheck[0] != '#')) {
			//cout << currentLine << endl;
			//cout << "i=" << i << endl;

			bool checkscope = 1;
			for (int j = 0; j < 3 * currentscope; j++) {
				if (currentLine[j] != ' ')
					checkscope = 0;
			}
			//cout << "checkscope=" << checkscope << endl;
			if (checkscope == 0) {
				int j = 0;
				while (currentLine[j] == ' ')
					j++;

				string nextvar;

				while (currentLine[j] != ' ' && j < currentLine.length())
					nextvar += currentLine[j++];

				//cout << "nextvar=" << nextvar << ';' << endl;

				if (nextvar.compare("else:") == 0) {
					//cout << "found an else" << endl;
					elseline = i;
				}
				else {
					//cout << "returning" << endl;
					return i - 1;
				}
			}
		}
		//cout << "here" << endl;
	}
	//cout << "there" << endl;
	//cout << i-1 << endl;
	return i-1;
}

//returns string of argument
string getarg(string ifline) {
	//cout << "inside getarg" << endl;
	string arg;
	int i = 0;

	while (ifline[i] == ' ')
		i++;

	while (isalnum(ifline[i]))
		i++;

	while (ifline[i] == '(' || ifline[i] == ' ')
		i++;

	while (ifline[i] != ':') {
		arg += ifline[i];
		i++;
	}


	if (arg[arg.length() - 1] == ':')
		arg.erase(arg.length() - 1);
	if (arg[arg.length() - 1] == ')' && arg[arg.length()-2] != '(')
		arg.erase(arg.length() - 1);

	return arg;
}

string parseexpr(string line) {
	//cout << "inside parseexpr" << endl;
	//cout << "line=" << line << endl;
	string newexpr;

	string tempterm;
	int i = 0;	

	while (line[i] == ' ')
		i++;

	if (line[i] == '-') {
		tempterm += line[i];
		i++;
	}

	while (isalnum(line[i])) {
		//cout << line[i] << endl;
		tempterm.append(line, i, 1);
		i++;
	}

	//cout << "tempterm=" << tempterm << endl;
	if ((i + 2) <= line.length()) {
		//cout << "next 2:" << line[i] << line[i + 1] << endl;
		if (line[i] == '(' && line[i + 1] == ')') {
			i += 2;
		}
	}

	//cout << "tempterm=" << tempterm << endl;

	if (checkifconst(tempterm)) {
		//cout << "is a constant: " << tempterm << ";" << endl;
		newexpr.append(tempterm);
		newexpr += ' ';
	}
	else {
		//cout << "variable:" << tempterm << endl;
		if (checkforfunction(tempterm, Functions)) {
			//cout << "found function" << endl;
			func_type * temp = getFunction(tempterm, Functions);

			

			if (temp->doesreturn) {
				//cout << temp->returnvalue << endl;
				temp->setreturn();
				newexpr += to_string(temp->returnvalue);
				newexpr += ' ';
			}
			else {
				cout << "ERROR: Function does not return a value" << endl;
			}
			temp = NULL;
		}
		else {
			variable * grabValue = getvariable(tempterm, Variables);
			if (grabValue == NULL)
				cout << "error: " << tempterm << " is undefined at this point" << endl;
			else {
				// << to_string(grabValue->value) << endl;
				newexpr.append(to_string(grabValue->value));
				newexpr += ' ';
				grabValue = NULL;
			}
		}
	}

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
			newexpr.append(tempterm);
			newexpr += ' ';
		}

		while (line[i] == ' ')
			i++;

		tempterm = "";

		if (line[i] == '-') {
			tempterm += line[i];
			i++;
		}

		while (isalnum(line[i])) {
			//cout << line[i] << endl;
			tempterm.append(line, i, 1);
			i++;
		}
		if ((i + 2) <= line.length()) {
			//cout << "next 2:" << line[i] << line[i + 1] << endl;
			if (line[i] == '(' && line[i + 1] == ')') {
				i += 2;
			}
		}


		while (line[i] == ' ')
			i++;

		//cout << tempterm << endl;

		if (checkifconst(tempterm)) {
			//cout << "is a constant:" << tempterm << ";" << endl;
			newexpr.append(tempterm);
			newexpr += ' ';
		}
		else {
			//cout << "variable:" << tempterm << endl;
			if (checkforfunction(tempterm, Functions)) {
				//cout << "found function" << endl;
				func_type * temp = getFunction(tempterm, Functions);

				if (temp->doesreturn) {
					//cout << temp->returnvalue << endl;
					temp->setreturn();
					newexpr += to_string(temp->returnvalue);
					newexpr += ' ';
				}
				else {
					cout << "ERROR: Function does not return a value" << endl;
				}

				temp = NULL;
			}
			else {
				variable * grabValue = getvariable(tempterm, Variables);
				if (grabValue == NULL)
					cout << "error: " << tempterm << " is undefined at this point" << endl;
				else {
					// << to_string(grabValue->value) << endl;
					newexpr.append(to_string(grabValue->value));
					newexpr += ' ';
					grabValue = NULL;
				}
			}
		}

		//cout << "newexpr=" << newexpr << endl;
	}

	return newexpr;
}

//parses out the values from the argument and determines the truth of it
bool evaluatearg(string arg) {
	string rawexpr1;
	string rawexpr2;
	string compoper;

	int i = 0;
	while (arg[i] == ' ')
		i++;

	while (arg[i] != '=' && arg[i] != '<' && arg[i] != '>' && arg[i] != '!') {
		//cout << arg[i] << endl;
		rawexpr1 += arg[i++];
	}

	//cout << "rawexpr1=" << rawexpr1 << endl;

	while (arg[i] == '=' || arg[i] == '<' || arg[i] == '>' || arg[i] == '!') {
		//cout << "i" << i << endl;
		compoper += arg[i++];
	}

	//cout << "compoper=" << compoper << endl;

	while (i < arg.length())
		rawexpr2 += arg[i++];

	//cout << "rawexpr2=" << rawexpr2 << endl;

	postfixconverter converter;

	//cout << "rawexpr1=" << rawexpr1 << endl;
	//cout << "rawexpr2=" << rawexpr2 << endl;

	string expr1 = parseexpr(rawexpr1);
	string expr2 = parseexpr(rawexpr2);

	//cout << "expr1=" << expr1 << endl;
	//cout << "expr2=" << expr2 << endl;

	expr1 = converter.convertToPostfix(expr1);
	expr2 = converter.convertToPostfix(expr2);

	float term1f = computeresult(expr1);
	float term2f = computeresult(expr2);

	//cout << "expr1=" << expr1 << endl;
	//cout << "term1=" << term1f << endl;
	//cout << "expr2=" << expr2 << endl;
	//cout << "term2=" << term2f << endl;
	//cout << "compoper=" << compoper << endl;
	
	if (compoper.compare("==") == 0) {
		//cout << "is equal to" << endl;
		if (term1f == term2f)
			return true;
		else
			return false;
	}
	else if (compoper.compare(">=") == 0) {
		//cout << "greater than or equal to" << endl;
		if (term1f >= term2f)
			return true;
		else
			return false;
	}
	else if (compoper.compare(">") == 0) {
		//cout << "greater than" << endl;
		if (term1f > term2f)
			return true;
		else
			return false;
	}
	else if (compoper.compare("<=") == 0) {
		//cout << "less than or equal to" << endl;
		if (term1f <= term2f)
			return true;
		else
			return false;
	}
	else if (compoper.compare("<") == 0) {
		//cout << "less than" << endl;
		if (term1f < term2f)
			return true;
		else
			return false;
	}
	else if (compoper.compare("!=") == 0) {
		//cout << "not equal to" << endl;
		if (term1f != term2f)
			return true;
		else
			return false;
	}
	return false;
}
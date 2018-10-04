using namespace std;

string getarg(string ifline);
bool evaluatearg(string arg);
list<string> findbranchdata(list<string> & branch, bool iftruth, int & linestoskip);
int findlastlineifelse(int startLineNum, int currentscope);

string parseexpr(string line);

void ifelse(string ifline, int iflineNum, list<string> & branch, int & linestoskip, int prevscope) {
	cout << "inside if()" << endl;
	

	int currentscope = prevscope + 1;
	cout << "scopelevel=" << currentscope << endl;
	int lastline = findlastlineifelse(iflineNum, currentscope);
	

	string line;
	string firstWord;

	string arg = getarg(ifline);
	cout << "arg=" << arg << endl;
	bool iftruth = evaluatearg(arg);
	cout << "iftruth=" << iftruth << endl;

	branch = findbranchdata(branch, iftruth, linestoskip);
	cout << "linestoskip=" << linestoskip << endl;
}

int findlastlineifelse(int startLineNum, int currentscope) {
	cout << "findlastline" << endl;
	cout << startLineNum << endl;

	int i = startLineNum + 1;
	while (i < fileLines.size()) {
		string currentLine = fileLines[i];
		cout << currentLine << endl;
		i++;

		bool checkscope = 1;
		for (int j = 0; j < 3 * currentscope; j++) {
			if (currentLine[j] != ' ')
				checkscope = 0;
		}
		cout << "checkscope=" << checkscope << endl;
		if (checkscope == 0)
			break;

	}
	cout << i - 1 << endl;
	return i - 1;
}

//returns string of argument
string getarg(string ifline) {
	string arg;
	int i = 0;
	while (ifline[i] != '(')
		i++;
	i++;
	while (ifline[i] != ':') {
		arg += ifline[i];
		i++;
	}

	arg.erase(arg.length() - 1);
	return arg;
}

string parseexpr(string line) {
	//cout << "inside parseexpr" << endl;
	string newexpr;

	string tempterm;
	int i = 0;	


	while (isalnum(line[i]) || line[i] == '-') {
		//cout << line[i] << endl;
		tempterm.append(line, i, 1);
		i++;
	}

	//cout << "tempterm=" << tempterm << endl;
	if ((i + 2) <= line.length()) {
		//cout << "next 2:" << line[i] << line[i + 1] << endl;
		if (line[i] == '(' && line[i + 1] == ')') {
			tempterm += "()";
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

	while (i < line.length()) {
		tempterm = "";
		//cout << line[i] << endl;

		//cout << "inside loop" << endl;
		while (line[i] == ' ') {
			i++;
		}
		//cout << line[i] << endl;

		while (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/') {
			tempterm.append(line, i, 1);
			i++;
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

		while (isalnum(line[i])) {
			//cout << line[i] << endl;
			tempterm.append(line, i, 1);
			i++;
		}
		if ((i + 2) <= line.length()) {
			//cout << "next 2:" << line[i] << line[i + 1] << endl;
			if (line[i] == '(' && line[i + 1] == ')') {
				tempterm += "()";
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
			//cout << "variable" << endl;
			variable * grabValue = getvariable(tempterm, Variables);
			if (grabValue == NULL)
				cout << "error: " << tempterm << " is undefined at this point" << endl;
			else {
				newexpr.append(to_string(grabValue->value));
				newexpr += ' ';
				grabValue = NULL;
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

	cout << "rawexpr1=" << rawexpr1 << endl;

	while (arg[i] == '=' || arg[i] == '<' || arg[i] == '>' || arg[i] == '!') {
		cout << "i" << i << endl;
		compoper += arg[i++];
	}

	cout << "compoper=" << compoper << endl;

	while (i < arg.length())
		rawexpr2 += arg[i++];

	cout << "rawexpr2=" << rawexpr2 << endl;

	postfixconverter converter;

	string expr1 = parseexpr(rawexpr1);
	string expr2 = parseexpr(rawexpr2);

	expr1 = converter.convertToPostfix(expr1);
	expr2 = converter.convertToPostfix(expr2);

	float term1f = computeresult(expr1);
	float term2f = computeresult(expr2);

	cout << "expr1=" << expr1 << endl;
	cout << "term1=" << term1f << endl;
	cout << "expr2=" << expr2 << endl;
	cout << "term2=" << term2f << endl;
	cout << "compoper=" << compoper << endl;
	
	if (compoper.compare("==") == 0) {
		cout << "is equal to" << endl;
		if (term1f == term2f)
			return true;
		else
			return false;
	}
	else if (compoper.compare(">=") == 0) {
		cout << "greater than or equal to" << endl;
		if (term1f >= term2f)
			return true;
		else
			return false;
	}
	else if (compoper.compare(">") == 0) {
		cout << "greater than" << endl;
		if (term1f > term2f)
			return true;
		else
			return false;
	}
	else if (compoper.compare("<=") == 0) {
		cout << "less than or equal to" << endl;
		if (term1f <= term2f)
			return true;
		else
			return false;
	}
	else if (compoper.compare("<") == 0) {
		cout << "less than" << endl;
		if (term1f < term2f)
			return true;
		else
			return false;
	}
	else if (compoper.compare("!=") == 0) {
		cout << "not equal to" << endl;
		if (term1f != term2f)
			return true;
		else
			return false;
	}
	return false;

}

list<string> findbranchdata(list<string> & branch, bool iftruth, int & linestoskip) {
	
	list<string> branch1;
	list<string> branch2;
	string b1line;
	string b2line;
	
	

	//getline(cin, b1line);
	//cout <<"b1line="<< b1line << endl;
	linestoskip++;
	
	while ((b1line[0] == ' ' || b1line.empty()) && !cin.eof()) {

		cout << "next line=" << b1line << endl;

		if (!b1line.empty()) {
			branch1.push_back(b1line);
		}
		//else {
		//	cout << "skipping empty line in b1" << endl;
		//}
		linestoskip++;
		getline(cin, b1line);
	} 

	getline(cin, b2line);
	cout << b2line << endl;
	linestoskip++;

	while ((b2line[0] == ' ' || b2line.empty()) && !cin.eof()) {
		if (!b2line.empty()) {
			//cout << "next line=" << b2line << endl;

			branch2.push_back(b2line);
		}
		//else
		//	cout << "skipping empty line in b2" << endl;
		linestoskip++;
		getline(cin, b2line);
	}

	linestoskip--;

	cout << "BRANCH1" << endl;
	for (list<string>::iterator it = branch1.begin(); it != branch1.end(); it++) {
		cout << (*it) << endl;
	}
	cout << "BRANCH2" << endl;
	for (list<string>::iterator it = branch2.begin(); it != branch2.end(); it++) {
		cout << (*it) << endl;
	}

	if (iftruth == 0)
		return branch2;
	return branch1;
}



/*

string term1;
string term2;
string compoper;

int i = 0;
while (arg[i] == ' ')
i++;

while (isalnum(arg[i]) || arg[i] == '(' || arg[i] == ')') {
cout << arg[i] << endl;
term1 += arg[i++];
}

cout << "term1=" << term1 << ';' << endl;
cout << "arg[i]=" << arg[i] << ';' << endl;

while (arg[i] == ' ')
i++;

while (arg[i] == '=' || arg[i] == '>' || arg[i] == '<' || arg[i] == '!')
compoper += arg[i++];

while (arg[i] == ' ')
i++;

while (isalnum(arg[i]))
term2 += arg[i++];

variable * term1Var = getvariable(term1, Variables);
variable * term2Var = getvariable(term2, Variables);
float term1f = term1Var->value;
float term2f = term2Var->value;
term1Var = NULL;
term2Var = NULL;

if (compoper.compare("==") == 0) {
cout << "is equal to" << endl;
if (term1f == term2f)
return true;
else
return false;
}
else if (compoper.compare(">=") == 0) {
cout << "greater than or equal to" << endl;
if (term1f >= term2f)
return true;
else
return false;
}
else if (compoper.compare(">") == 0) {
cout << "greater than" << endl;
if (term1f > term2f)
return true;
else
return false;
}
else if (compoper.compare("<=") == 0) {
cout << "less than or equal to" << endl;
if (term1f <= term2f)
return true;
else
return false;
}
else if (compoper.compare("<") == 0) {
cout << "less than" << endl;
if (term1f < term2f)
return true;
else
return false;
}
else if (compoper.compare("!=") == 0) {
cout << "not equal to" << endl;
if (term1f != term2f)
return true;
else
return false;
}
return false;
*/
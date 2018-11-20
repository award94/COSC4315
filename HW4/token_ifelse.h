using namespace std;

string getarg(string ifline);
bool evaluatearg(string arg, int scope, int nestlevel);
list<string> findbranchdata(list<string> & branch, bool iftruth, int & linestoskip);
int findlastlineifelse(int startLineNum, int & elseline, int stacklevel, int nestlevel);

string parseexpr(string line, int scope, int nestlevel);

void ifelse(string ifline, int & iflineNum, int funclastline,
	int prevstack, string stackname, int nestlevel) {
	//cout << endl<<"============IF ELSE BEGIN==========" << endl;
	

	int currentstack = prevstack;
	//cout << "stacklevel=" << prevstack << endl;
	//cout << "nestlevel=" << nestlevel << endl;

	int elseline = -1;
	int lastline = findlastlineifelse(iflineNum, elseline, prevstack, nestlevel);
	
	//cout << "if start line Num=" << iflineNum << endl;
	//cout << "else start line=" << elseline << endl;
	//cout << "if/else last line=" << lastline << endl;
	//cout << "function last line=" << funclastline << endl;

	string line;
	string firstWord;

	string arg = getarg(ifline);
	//cout << "arg=" << arg << endl;
	bool iftruth = evaluatearg(arg, currentstack, nestlevel);
	//cout << "iftruth=" << iftruth << endl;

	if (iftruth == 1) {
		if (elseline == -1) {
			//cout << "start1" << endl;
			int i = iflineNum + 1;
			for (; i <= lastline; i++) {
				//cout << "i=" << i <<endl;
				string currentLine = fileLines[i];
				processstatement(i, currentLine, funclastline, currentstack, stackname, nestlevel+1);
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
				processstatement(i, currentLine, funclastline, currentstack, stackname, nestlevel+1);
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
				processstatement(i, currentLine, funclastline, currentstack, stackname, nestlevel+1);
			}
			iflineNum = i;
			
			//cout << "done4" << endl;
		}
	}

	iflineNum = lastline;
	//cout << "lineNum=" << iflineNum << endl;
	//cout << "============IF ELSE END==========" << endl;
	
}

int findlastlineifelse(int startLineNum, int & elseline, int stacklevel, int nestlevel) {
	//cout << "findlastline" << endl;
	//cout << "nestlevel=" << nestlevel << endl;
	//cout << "filesize=" << fileLines.size() << endl;


	string ifline = fileLines[startLineNum];
	//cout << "ifline=" << ifline << endl;
	int s = 0;
	while (ifline[s] == ' ')
		s++;
	int indention = s / 3 + 1;
	//cout << "indention=" << indention << endl;

	int listindention = indention;
	if (stacklevel > 0)
		listindention--;

	if (ifelseList.empty())
		ifelseList.push_back(listindention-1);

	else {
		if (ifelseList[ifelseList.size() - 1] < listindention-1)
			ifelseList[ifelseList.size() - 1] = listindention-1;
		else if (ifelseList[ifelseList.size() - 1] > listindention-1)
			ifelseList.push_back(listindention-1);
	}


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
			for (int j = 0; j < 3 * indention; j++) {
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

				if (nextvar.compare("else:") == 0 && elseline == -1) {
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

string parseexpr(string line, int scope, int nestlevel) {
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

	//cout << "tempterm=" << tempterm << endl;
	newexpr += evaluatenewterm(tempterm, scope, nestlevel);

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

		newexpr += evaluatenewterm(tempterm, scope, nestlevel);
	}

	return newexpr;
}

//parses out the values from the argument and determines the truth of it
bool evaluatearg(string arg, int scope, int nestlevel) {
	//cout << "inside evaluatearg()" << endl;
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

	string expr1 = parseexpr(rawexpr1, scope, nestlevel);
	string expr2 = parseexpr(rawexpr2, scope, nestlevel);

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
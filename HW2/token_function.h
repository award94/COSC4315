using namespace std;

string findfuncname(string line);
int findlastlinefunc(int startLineNum, int funcscope);
bool checkreturn(int startLine, int lastLine, int scopelevel);
float setreturnvalue(string line, string funcName, int funcscope);

void createNewFunc(string line, int & lineNum, int scopelevel){
	cout << "inside Function" << endl;
	int funcscope = scopelevel + 1;

	string funcName = findfuncname(line);
	float funcResult;

	createNewVar(funcName, Variables, scopelevel);

	//list<string> funcstatements;
	vector<string> funcstatements;

	cout << endl << "current line#=" << lineNum << endl;
	int lastLine = findlastlinefunc(lineNum, funcscope);

	cout << "-----------------------------" << endl;
	cout << "ENTIRE FUNCION DEFINITION" << endl;
	for (int i = lineNum; i <= lastLine; i++) {
		cout << fileLines[i] << endl;
		string currentLine = fileLines[i];

		bool lineinscope = 1;
		for (int j = 0; j < funcscope* 3; j++) {
			if (currentLine[j] != ' ')
				lineinscope = 0;
		}
		if (currentLine[(funcscope * 3) + 1] == ' ')
			lineinscope = 0;
		cout << "isthisline in scope=" << lineinscope << endl;

		if (lineinscope) {
			int j = 0;
			while (currentLine[j] == ' ')
				j++;

			string nextvar;

			while (currentLine[j] != ' ' && j < currentLine.length())
				nextvar += currentLine[j++];

			cout << "nextvar=" << nextvar << ';'<< endl;

			if (nextvar.compare("return") != 0) {
				cout << "I will process this statement" << endl;
				processstatement(i, currentLine, funcscope);
			}
			else {
				cout << "assigning return value" << endl;
				float returnvalue = setreturnvalue(currentLine, funcName, funcscope);
				variable * temp = getvariable(funcName, Variables);
				temp->value = returnvalue;
				temp = NULL;
				break;
			}
		}

	}
	cout << "-----------------------------" << endl;

	lineNum = lastLine;
	deleteScope(Variables, funcscope);


	//bool doesreturn;
	//doesreturn = checkreturn(lineNum, lastLine, funcscope);
	//cout << "doesreturn = "<<doesreturn << endl;

	/*
	string funcline;
	getline(cin, funcline);
	while (((funcline[0] == ' ' && funcline[1] == ' ') || funcline.empty()) && !cin.eof()) {
		//cout << "found a line:" << funcline<< endl;
		funcstatements.push_back(funcline);
		lineNum++;
		getline(cin, funcline);
	}

	string dummy;
	cin.clear();
	cin.seekg(0, cin.beg);
	for (int j = 0; j < lineNum; j++)
		getline(cin, dummy);

	cout << "lines in function" << endl;
	for (list<string>::iterator it = funcstatements.begin(); it != funcstatements.end(); it++) {
		cout <<"processing this inside func():"<< (*it) << endl;

		int i = 0;							//char index of the statement
		string nextVar;

		while ((*it)[i] == ' ' && i < (*it).length()) {
			i++;
		}
		while (isalnum((*it)[i]) && i < (*it).length()) {
			nextVar.append((*it), i, 1);
			i++;
		}

		cout <<"nextVar="<< nextVar << endl;

		

		if (nextVar.compare("return") == 0) {
			cout << "found the return" << endl;
			funcResult = setreturnvalue((*it), funcName, funcscope);
		}
		else
			processstatement(lineNum, (*it), funcscope);
	}

	cout << "funcResult=" << funcResult << endl;

	setValue(funcName, Variables, funcResult);
	deleteScope(Variables, funcscope);
	*/
}

int findlastlinefunc(int startLineNum, int funcscope) {
	cout << "findlastline" << endl;
	cout << startLineNum << endl;

	int i = startLineNum + 1;
	while (i < fileLines.size()) {
		string currentLine = fileLines[i];
		cout << currentLine << endl;
		i++;

		bool checkscope = 1;
		for (int j = 0; j < 3 * funcscope; j++) {
			if (currentLine[j] != ' ')
				checkscope = 0;
		}
		cout << "checkscope=" << checkscope << endl;
		if (checkscope == 0)
			break;

	}
	cout << i-1 << endl;
	return i-1;
}

bool checkreturn(int startLine, int lastLine, int scopelevel) {
	cout << "inside checkreturn()" << endl;
	cout << "scope=" << scopelevel << endl;

	for (int i = startLine + 1; i < lastLine; i++) {
		cout << fileLines[i] << endl;
		string currentLine = fileLines[i];

		bool lineinscope = 1;
		for (int j = 0; j < scopelevel * 3; j++) {
			if (currentLine[j] != ' ')
				lineinscope = 0;
		}
		if (currentLine[(scopelevel * 3) + 1] == ' ')
			lineinscope = 0;
		cout << "isthisline in scope=" << lineinscope << endl;

		int j = 0;
		while (currentLine[j] == ' ')
			j++;

		string nextvar;

		while (currentLine[j] != ' ' && j < currentLine.length())
			nextvar += currentLine[j++];

		cout << "nextvar="<<nextvar << endl;
	}

	return 0;
}

string findfuncname(string line) {
	string name;

	int i = 0;

	while (line[i] == ' ')
		i++;

	while (isalnum(line[i]))
		i++;

	while (line[i] == ' ')
		i++;

	while (isalnum(line[i]) && i < line.length()) {
		name += line[i];
		i++;
	}

	name += "()";

	return name;
}

float setreturnvalue(string line, string funcName, int funcscope) {
	//cout << "inside setreturnvalue" << endl;
	//cout << "line:" << line << endl;
	//cout << "funcName:" << funcName << endl;

	string alreadypassed;
	string RHS;
	int i = 0;

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

	//cout << "alreadypassed:" << alreadypassed <<';'<<endl;

	string tempTerm;
	while (isalnum(line[i])) {
		tempTerm += line[i];
		i++;
	}

	if (checkifconst(tempTerm)) {
		//cout << "constant value" << endl;
		RHS += tempTerm;
		RHS += ' ';
	}
	else {
		//cout << "not a constant value" << endl;
		for (int j = funcscope; j >= 0; j--) {
			if (checkforvariableinscope(tempTerm, Variables, j)) {
				//cout << "found variable in this scope:" << j << endl;
				variable * temp = getvariablescope(tempTerm, Variables, j);
				RHS += to_string(temp->value);
				RHS += ' ';
				temp = NULL;
				break;
			}
			//else {
			//	cout << "did not find variable in this scope, try lower ones" << endl;
			//}
		}
	}

	while (line[i] == ' ') {
		i++;
	}

	while (i < line.length()) {
		tempTerm = "";

		while (!isalnum(line[i]) && line[i] != ' ') {
			tempTerm += line[i];
			i++;
		}
		if ((tempTerm.compare("+") == 0) || (tempTerm.compare("-") == 0 ||
			tempTerm.compare("*") == 0) || (tempTerm.compare("/") == 0)) {
			RHS += tempTerm;
			RHS += ' ';
		}

		while (line[i] == ' ')
			i++;

		tempTerm = "";

		while (isalnum(line[i])) {
			//cout << line[i] << endl;
			tempTerm.append(line, i, 1);
			i++;
		}
		while (line[i] == ' ' && line.length())
			i++;

		if (checkifconst(tempTerm)) {
			RHS += tempTerm;
			RHS += ' ';
		}
		else {
			for (int j = funcscope; j >= 0; j--) {
				if (checkforvariableinscope(tempTerm, Variables, j)) {
					variable * temp = getvariablescope(tempTerm, Variables, j);
					RHS += to_string(temp->value);
					RHS += ' ';
					temp = NULL;
					break;
				}
			}
		}
	}
	cout << "RHS:" << RHS << endl;
	postfixconverter converter;
	RHS = converter.convertToPostfix(RHS);
	cout << "RHS:" << RHS << endl;
	return computeresult(RHS);
}
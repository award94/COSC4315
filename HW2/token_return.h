using namespace std;

float setreturnvalue(string line, string funcName, int funcscope);

void setreturn(string line, int & lineNum, int lastline, int scopelevel, string funcname) {
	cout << "inside setreturn" << endl;
	cout << line << endl;
	cout << "lineNum=" << lineNum << endl;
	cout << "lastline=" << lastline << endl;
	cout << "scopelevel=" << scopelevel << endl;
	cout << "funcname=" << funcname << endl;

	printVariables(Variables);

	createNewVar(funcname, Variables, scopelevel-1);

	float returnvalue = setreturnvalue(line, funcname, scopelevel);
	variable * temp = getvariable(funcname, Variables);
	temp->value = returnvalue;
	temp = NULL;

	lineNum = lastline;
}

float setreturnvalue(string line, string funcName, int funcscope) {
	cout << "inside setreturnvalue" << endl;
	cout << "line:" << line << endl;
	cout << "funcName:" << funcName << endl;
	cout << "scope=" << funcscope << endl;

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

	//cout << "alreadypassed:" << alreadypassed << ';' << endl;

	string tempTerm;

	if (line[i] == '-') {
		tempTerm += line[i];
		i++;
	}

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
		cout << "not a constant value" << endl;
		for (int j = funcscope; j >= 0; j--){
			cout << "scope=" << j << endl;
			if (checkforvariableinscope(tempTerm, Variables, j)) {
				cout << "found variable in this scope:" << j<< endl;
				variable * temp = getvariablescope(tempTerm, Variables, j);
				cout << "value=" << temp->value << endl;
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
			for (int j = funcscope; j >= 0; j--) {
				cout << "scope=" << j << endl;
				if (checkforvariableinscope(tempTerm, Variables, j)) {
					cout << "found variable in this scope:" << j << endl;
					variable * temp = getvariablescope(tempTerm, Variables, j);
					cout << "value=" << temp->value << endl;
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
	//cout << "RHS:" << RHS << endl;
	postfixconverter converter;
	RHS = converter.convertToPostfix(RHS);
	//cout << "RHS:" << RHS << endl;
	return computeresult(RHS);
}
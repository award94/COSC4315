using namespace std;

string findfuncname(string line);
float setreturnvalue(string line, string funcName, list<variable*> & Variables, int funcscope);

void createNewFunc(string line, int & lineNum, list<variable*> & Variables, int scopelevel){
	//cout << "nextVar is a function" << endl;
	int funcscope = scopelevel + 1;

	string funcName = findfuncname(line);
	float funcResult;

	createNewVar(funcName, scopelevel, Variables);

	list<string> funcstatements;
	string funcline;
	getline(cin, funcline);
	while ((funcline[0] == ' ' && funcline[1] == ' ') || funcline.empty()) {
		//cout << "found a line" << endl;
		funcstatements.push_back(funcline);
		lineNum++;
		getline(cin, funcline);
	}

	string dummy;
	cin.clear();
	cin.seekg(0, cin.beg);
	for (int j = 0; j < lineNum; j++)
		getline(cin, dummy);

	//cout << "lines in function" << endl;
	for (list<string>::iterator it = funcstatements.begin(); it != funcstatements.end(); it++) {
		//cout << (*it) << endl;

		int i = 0;							//char index of the statement
		string nextVar;

		while ((*it)[i] == ' ' && i < (*it).length()) {
			i++;
		}
		while (isalnum((*it)[i]) && i < (*it).length()) {
			nextVar.append((*it), i, 1);
			i++;
		}

		//cout << nextVar << endl;

		

		if (nextVar.compare("return") == 0) {
			//cout << "found the return" << endl;
			funcResult = setreturnvalue((*it), funcName, Variables, funcscope);
		}
		else
			processstatement(Variables, lineNum, (*it), funcscope);
	}

	//cout << "funcResult=" << funcResult << endl;

	setValue(funcName, funcResult, Variables);
	deleteScope(Variables, funcscope);
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

float setreturnvalue(string line, string funcName, list<variable*> & Variables, int funcscope) {
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
	//cout << "RHS:" << RHS << endl;
	postfixconverter converter;
	RHS = converter.convertToPostfix(RHS);
	//cout << "RHS:" << RHS << endl;
	return computeresult(RHS);
}
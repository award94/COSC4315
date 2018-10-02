using namespace std;

string findfuncname(string line);

void createNewFunc(string line, int & lineNum, list<variable*> & Variables, int scopelevel){
	//cout << "nextVar is a function" << endl;
	int funcscope = scopelevel + 1;

	string funcName = findfuncname(line);

	createNewVar(funcName, funcscope, Variables);

	list<string> funcstatements;
	string funcline;
	getline(cin, funcline);
	while ((funcline[0] == ' ' && funcline[1] == ' ') || funcline.empty()) {
		cout << "found a line" << endl;
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
		cout << (*it) << endl;

	}

	//deleteScope(Variables, funcscope);
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

	return name;
}
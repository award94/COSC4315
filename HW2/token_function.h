using namespace std;

void createNewFunc(string line, int & i, list<variable*> & Variables) {
	cout << "nextVar is a function" << endl;

	string funcName;

	while (isalnum(line[i]) && i < line.length()) {
		cout << "i=" << i << ", line[i]=" << line[i] << endl;
		funcName.append(line, i, 1);
		i++;
	}

	createNewVar(funcName, Variables);
}
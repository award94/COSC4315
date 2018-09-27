using namespace std;

void createNewFunc(string line, int & i, list<variable*> & Variables) {
	cout << "nextVar is a function" << endl;

	string funcName;

	while (isalnum(line[i]) && i < line.length()) {
		cout << "i=" << i << ", line[i]=" << line[i] << endl;
		funcName.append(line, i, 1);
		i++;
	}

	variable * newVar = new variable();
	newVar->name = funcName;
	newVar->value = 1;

	Variables.push_back(newVar);
	newVar = NULL;
	delete newVar;
}
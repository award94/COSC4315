using namespace std;

void createNewFunc(string line, int & i, list<token*> & Tokens) {
	cout << "nextToken is a function" << endl;

	string funcName;

	while (isalnum(line[i]) && i < line.length()) {
		cout << "i=" << i << ", line[i]=" << line[i] << endl;
		funcName.append(line, i, 1);
		i++;
	}

	token * newToken = new token();
	newToken->name = funcName;
	newToken->value = 1;

	Tokens.push_back(newToken);
	newToken = NULL;
	delete newToken;
}
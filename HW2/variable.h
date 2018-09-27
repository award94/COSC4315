using namespace std;

struct token {
	string name;
	int value;
};

void printTokens(list<token*> myTokens) {
	cout << "inside printTokens" << endl;

	for (list<token*>::iterator it = myTokens.begin(); it != myTokens.end(); it++)
		cout << "token data" << endl;
}

void deleteTokens(list<token*> myTokens) {
	cout << "inside deleteTokens" << endl;

	token * temp = NULL;
	while (myTokens.size() != 0) {
		temp = myTokens.front();
		myTokens.pop_front();
		delete temp;
	}
}

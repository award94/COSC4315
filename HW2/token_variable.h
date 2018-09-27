using namespace std;

void createNewVar(string nextToken, list<token*> & Tokens) {

	cout << "nextToken is a variable" << endl;

	//Create a new token
	token * newToken = new token();
	newToken->name = nextToken;
	newToken->value = 1;
	
	Tokens.push_back(newToken);
	newToken = NULL;
	delete newToken;
}
using namespace std;

void createNewVar(string nextVar, list<variable*> & Variables) {

	cout << "nextToken is a variable" << endl;

	//Create a new token
	variable * newVar = new variable();
	newVar->name = nextVar;
	newVar->value = 1;
	
	Variables.push_back(newVar);
	newVar = NULL;
	delete newVar;
}
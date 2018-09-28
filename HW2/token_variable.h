using namespace std;

void createNewVar(string nextVar, list<variable*> & Variables) {
	//Create a new token
	variable * newVar = new variable();
	newVar->name = nextVar;
	newVar->value = 0;
	
	Variables.push_back(newVar);
	newVar = NULL;
	delete newVar;
}
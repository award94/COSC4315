using namespace std;

struct variable {
	string name;
	float value;
};

bool checkforvariable(string VarName, list<variable*> Variables) {
	for (list<variable*>::iterator it = Variables.begin();
		it != Variables.end(); it++) {
		if ((*it)->name.compare(VarName) == 0)
			return true;
	}
	return false;
}

variable* getvariable(string VarName, list<variable*> Variables) {
	//cout << "inside getvariable()" << endl;
	for (list<variable*>::iterator it = Variables.begin();
		it != Variables.end(); it++) {
		if ((*it)->name.compare(VarName) == 0)
			return (*it);
	}
	//cout << "Variable does not exist" << endl;
	return NULL;
}

void createNewVar(string nextVar, list<variable*> & Variables) {
	//Create a new token
	variable * newVar = new variable();
	newVar->name = nextVar;
	newVar->value = 0;

	Variables.push_back(newVar);
	newVar = NULL;
	delete newVar;
}

void printVariables(list<variable*> myVariables) {
	cout << "All Variables in system" << endl;

	for (list<variable*>::iterator it = myVariables.begin(); it != myVariables.end(); it++)
		cout << "ID=" << (*it)->name << " value=" << (*it)->value << endl;
}

void deleteVariables(list<variable*> myVariables) {
	cout << "inside deleteVariables" << endl;

	variable * temp = NULL;
	while (myVariables.size() != 0) {
		temp = myVariables.front();
		myVariables.pop_front();
		delete temp;
	}
}

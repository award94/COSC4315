using namespace std;

struct variable {
	string name;
	float value;
};

void printVariables(list<variable*> myVariables) {
	cout << "All Variables in system" << endl;

	for (list<variable*>::iterator it = myVariables.begin(); it != myVariables.end(); it++)
		cout << "ID="<<(*it)->name<<" value="<<(*it)->value << endl;
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

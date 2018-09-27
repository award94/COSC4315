using namespace std;

struct variable {
	string name;
	int value;
};

void printVariables(list<variable*> myVariables) {
	cout << "inside printVariables" << endl;

	for (list<variable*>::iterator it = myVariables.begin(); it != myVariables.end(); it++)
		cout << "variable data" << endl;
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

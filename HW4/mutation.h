using namespace std;

//void variableassign(string variablename, vector<string> & mutationlist);
//bool checkforvariable(string variablename);
bool checkformutatedvariable(string variablename);

/*
void variableassign(string variablename, vector<string> & mutationlist) {
	cout << "inside variableassign()" << endl;
	cout << "variablename=" << variablename << ';' << endl;

	if (checkforvariable(variablename)) {
		if (!checkformutatedvariable(variablename))
			mutationlist.push_back(variablename);
	}
	else {
		variables.push_back(variablename);
	}
}

bool checkforvariable(string variablename) {
	cout << "inside checkforvariable()" << endl;

	for (int i = 0; i < variables.size(); i++) {
		if (variables[i].compare(variablename) == 0)
			return true;
	}
	return false;
}
*/

bool checkformutatedvariable(string variablename) {
	//cout << "inside checkformutatedvariable()" << endl;

	for (int i = 0; i < mutationList.size(); i++) {
		if (mutationList[i].compare(variablename) == 0)
			return true;
	}
	return false;
}
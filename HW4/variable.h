using namespace std;

struct variable {
	string name;
	float value;
	int scope;
};

bool checkforvariable(string VarName, list<variable*> & Variables) {
	for (list<variable*>::iterator it = Variables.begin();
		it != Variables.end(); it++) {
		if ((*it)->name.compare(VarName) == 0)
			return true;
	}
	return false;
}

bool checkforvariableinscope(string VarName, list<variable*> & Variables, int scopelevel) {
	for (list<variable*>::iterator it = Variables.begin();
		it != Variables.end(); it++) {
		if ((*it)->name.compare(VarName) == 0 && (*it)->scope == scopelevel)
			return true;
	}
	return false;
}

bool checkifconst(string Var) {
	for (int i = 0; i < Var.length(); i++) {
		if ((isdigit(Var[i]) || (i == 0 && Var[i] == '-')) == false)
			return false;
	}
	return true;
}

variable* getvariable(string VarName, list<variable*> & Variables) {
	//cout << "inside getvariable():" << VarName<< ';'<< endl;
	for (list<variable*>::iterator it = Variables.begin();
		it != Variables.end(); it++) {
		if ((*it)->name.compare(VarName) == 0)
			return (*it);
	}
	cout << "Variable does not exist" << endl;
	return NULL;
}

void setValue(string VarName, list<variable*> & Variables, float VarValue) {
	for (list<variable*>::iterator it = Variables.begin();
		it != Variables.end(); it++) {
		if ((*it)->name.compare(VarName) == 0)
			(*it)->value = VarValue;
	}
}

variable* getvariablescope(string VarName, list<variable*> & Variables, int scopelevel) {
	//cout << "getvariableinscope()" << endl;
	//cout << "name=" << VarName << ";" << endl;
	//cout << "scope=" << scopelevel << endl;

	for (list<variable*>::iterator it = Variables.begin();
		it != Variables.end(); it++) {
		if ((*it)->name.compare(VarName) == 0 && (*it)->scope == scopelevel)
			return (*it);
	}
	//cout << "Variable does not exist" << endl;
	return NULL;
}

void createNewVar(string nextVar, list<variable*> & Variables, int scopelevel) {
	if (nextVar.compare("if") == 0 || nextVar.compare("else") == 0 || nextVar.compare("def") == 0 ||
		nextVar.compare("int") == 0|| nextVar.compare("string") == 0 || nextVar.compare("print") == 0 ||
		nextVar.compare("list") == 0 || nextVar.compare("False") == 0 || nextVar.compare("class") == 0 ||
		nextVar.compare("is") == 0 || nextVar.compare("None") == 0 ||
		nextVar.compare("True") == 0 || nextVar.compare("from") == 0 || nextVar.compare("in") == 0 ||
		nextVar.compare("lambda") == 0 || nextVar.compare("try") == 0 || nextVar.compare("nonlocal") == 0 ||
		nextVar.compare("while") == 0 || nextVar.compare("and") == 0 || nextVar.compare("or") == 0 ||
		nextVar.compare("del") == 0 || nextVar.compare("global") == 0 || nextVar.compare("not") == 0 ||
		nextVar.compare("with") == 0 || nextVar.compare("as") == 0 || nextVar.compare("elif") == 0 ||
		nextVar.compare("yield") == 0 || nextVar.compare("assert") == 0 || nextVar.compare("import") == 0 ||
		nextVar.compare("pass") == 0 || nextVar.compare("break") == 0 ||
		nextVar.compare("except") == 0 || nextVar.compare("raise") == 0) {
		cout << "ERROR: Trying to name variable a reserved word" << endl;
		cout << "Bad Name = " << nextVar << endl;
		return;
	}

	//Create a new token
	variable * newVar = new variable();
	newVar->name = nextVar;
	newVar->value = 0;
	newVar->scope = scopelevel;

	Variables.push_back(newVar);
	newVar = NULL;
	delete newVar;
}

void printVariables(list<variable*> & Variables) {
	//cout << "All Variables in system" << endl;

	for (list<variable*>::iterator it = Variables.begin(); it != Variables.end(); it++)
		cout << "name=" << (*it)->name << " value=" << (*it)->value
			<< " scope=" << (*it)->scope << endl;
}

void deleteVariables(list<variable*> & Variables) {
	//cout << "inside deleteVariables" << endl;

	variable * temp = NULL;
	while (Variables.size() != 0) {
		temp = Variables.front();
		Variables.pop_front();
		delete temp;
	}
}

void deleteScope(list<variable*> & Variables, int scopelevel) {
	//cout << "inside deleteScope" << endl;

	for (list<variable*>::iterator it = Variables.begin(); it != Variables.end();) {
		if ((*it)->scope == scopelevel) {
			it = Variables.erase(it);
		}
		else
			it++;
	}
}
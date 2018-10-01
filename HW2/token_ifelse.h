using namespace std;

struct ifelsebrancher {
	int offset;
	int branchlength;
};

string getarg(string ifline);
bool evaluatearg(string arg, list<variable*> Variables);
list<string> findbranchdata(list<string> & branch, bool iftruth, int & linestoskip);


void ifelse(string ifline, int iflineNum, list<variable*> Variables, list<string> & branch, int & linestoskip) {
	cout << "inside ifelse()" << endl;
	cout << ifline << " " << iflineNum << endl;

	string line;
	string firstWord;

	string arg = getarg(ifline);
	cout << "arg=" << arg << endl;
	bool iftruth = evaluatearg(arg, Variables);
	cout << "iftruth=" << iftruth << endl;

	branch = findbranchdata(branch, iftruth, linestoskip);
	cout << "linestoskip=" << linestoskip << endl;
}

//returns string of argument
string getarg(string ifline) {
	string arg;
	int i = 0;
	while (ifline[i] != '(')
		i++;
	i++;
	while (ifline[i] != ')') {
		arg += ifline[i];
		i++;
	}

	return arg;
}

//parses out the values from the argument and determines the truth of it
bool evaluatearg(string arg, list<variable*> Variables) {
	string term1;
	string term2;
	string compoper;

	int i = 0;
	while (arg[i] == ' ')
		i++;

	while (isalnum(arg[i]))
		term1 += arg[i++];

	while (arg[i] == ' ')
		i++;

	while (arg[i] == '=' || arg[i] == '>' || arg[i] == '<' || arg[i] == '!')
		compoper += arg[i++];

	while (arg[i] == ' ')
		i++;

	while (isalnum(arg[i]))
		term2 += arg[i++];
	
	variable * term1Var = getvariable(term1, Variables);
	variable * term2Var = getvariable(term2, Variables);
	float term1f = term1Var->value;
	float term2f = term2Var->value;
	term1Var = NULL;
	term2Var = NULL;

	if (compoper.compare("==") == 0) {
		cout << "is equal to" << endl;
		if (term1f == term2f)
			return true;
		else
			return false;
	}
	else if (compoper.compare(">=") == 0) {
		cout << "greater than or equal to" << endl;
		if (term1f >= term2f)
			return true;
		else
			return false;
	}
	else if (compoper.compare(">") == 0) {
		cout << "greater than" << endl;
		if (term1f > term2f)
			return true;
		else
			return false;
	}
	else if (compoper.compare("<=") == 0) {
		cout << "less than or equal to" << endl;
		if (term1f <= term2f)
			return true;
		else
			return false;
	}
	else if (compoper.compare("<") == 0) {
		cout << "less than" << endl;
		if (term1f < term2f) 
			return true;
		else
			return false;
	}
	else if (compoper.compare("!=") == 0) {
		cout << "not equal to" << endl;
		if (term1f != term2f)
			return true;
		else
			return false;
	}
	return false;
}

list<string> findbranchdata(list<string> & branch, bool iftruth, int & linestoskip) {
	cout << "inside findbranchdata" << endl;
	
	list<string> branch1;
	list<string> branch2;
	string b1line;
	string b2line;
	
	getline(cin, b1line);
	//cout << b1line << endl;
	linestoskip++;
	
	while ((b1line[0] == ' ' || b1line.empty()) && !cin.eof()) {

		//cout << "next line=" << b1line << endl;

		if (!b1line.empty()) {
			branch1.push_back(b1line);
		}
		//else {
		//	cout << "skipping empty line in b1" << endl;
		//}
		linestoskip++;
		getline(cin, b1line);
	} 

	getline(cin, b2line);
	//cout << b2line << endl;
	linestoskip++;

	while ((b2line[0] == ' ' || b2line.empty()) && !cin.eof()) {
		if (!b2line.empty()) {
			//cout << "next line=" << b2line << endl;

			branch2.push_back(b2line);
		}
		//else
		//	cout << "skipping empty line in b2" << endl;
		linestoskip++;
		getline(cin, b2line);
	}

	linestoskip--;

	cout << "BRANCH1" << endl;
	for (list<string>::iterator it = branch1.begin(); it != branch1.end(); it++) {
		cout << (*it) << endl;
	}
	cout << "BRANCH2" << endl;
	for (list<string>::iterator it = branch2.begin(); it != branch2.end(); it++) {
		cout << (*it) << endl;
	}

	if (iftruth == 0)
		return branch2;
	return branch1;
}


/*


*/

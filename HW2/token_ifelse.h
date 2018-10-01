using namespace std;

string getarg(string ifline);
bool evaluatearg(string arg, list<variable*> Variables);

void ifelse(string ifline, int iflineNum, list<variable*> Variables) {
	cout << "inside ifelse()" << endl;
	cout << ifline << " " << iflineNum << endl;

	list<string> branch1;
	list<string> branch2;

	string line;
	string firstWord;

	string arg = getarg(ifline);
	cout << "arg=" << arg << endl;
	bool iftruth = evaluatearg(arg, Variables);
	cout << "iftruth=" << iftruth << endl;

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

	return 0;
}




/*
do {
getline(cin, line);
cout << "next line="<<line << endl;
int j;

while (line[j] == ' ')
j++;

while (isalpha(line[j])) {
firstWord += line[j];
j++;
}

branch1.push_back(line);

} while (line[0] == ' ' != 0 && cin.eof() != true);

do {
getline(cin, line);
cout << "next line=" << line << endl;
int j;

while (line[j] == ' ')
j++;

while (isalpha(line[j])) {
firstWord += line[j];
j++;
}

branch2.push_back(line);

} while (line[0] == ' ' != 0 && cin.eof() != true);
branch1.pop_back();
branch2.pop_back();

cout << "BRANCH1" << endl;
for (list<string>::iterator it = branch1.begin(); it != branch1.end(); it++) {
cout << (*it) << endl;
}
cout << "BRANCH2" << endl;
for (list<string>::iterator it = branch2.begin(); it != branch2.end(); it++) {
cout << (*it) << endl;
}
*/

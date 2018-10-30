using namespace std;

void findargument(string line, int & parenthesis1, int & parenthesis2);
void createtermlist(vector<string> & termlist, string arg);
void parsetermlist(vector<string> & termlist, int scope);
string evaluatenewterm(string newterm, int scope);

void print(string line, int scope) {
// Argument is used as a temporary variable to hold the contents before the delimiter
	// When the delimiter is reached, the strings are checked and appended to finalOutputt
	string finalOutput;
		
	cout << "inside print" << endl;

	int i = 0;
	int parenthesis1;
	int parenthesis2;
	string arg;
	
	
	findargument(line, parenthesis1, parenthesis2);
	
	arg.append(line, parenthesis1+1, parenthesis2 - parenthesis1-1);
	
	vector<string> termlist;
	createtermlist(termlist, arg);
	parsetermlist(termlist, scope);
	cout << "PARSED TERMS" << endl;
	for (int i = 0; i < termlist.size(); i++) {
		cout << termlist[i] << endl;
		if (isalpha(termlist[i][0])) {
			//cout << "string" << endl;
			finalOutput += termlist[i];
			finalOutput += ' ';
		}
		else {
			//cout << "number" << endl;
			postfixconverter pfxconv;
			string pfx = pfxconv.convertToPostfix(termlist[i]);
			int finalresult = computeresult(pfx);

			finalOutput += to_string(finalresult);
			finalOutput += ' ';
		}
	}


	////cout << "finalOutput=" << finalOutput << endl;
	cout << finalOutput << endl;

	
}

void createtermlist(vector<string> & termlist, string arg) {
	cout << "inside createtermlist()" << endl;
	cout << "arg=" << arg << endl;

	for (int i = 0; i < arg.length(); i++) {

		string newterm;
		

		//cout << i << endl;

		while (arg[i] == ' ' && i < arg.length())
			i++;

		/*if (arg[i] == '"') {
			//cout << "string found" << endl;
			newterm += arg[i];
			i++;
			while (arg[i] != '"') {
				newterm += arg[i];
				i++;
			}
			newterm += arg[i];
			i++;
		}
		else {*/
		stack<char> parenstack;
		while (i < arg.length()) {
			if (arg[i] == '(')
				parenstack.push('(');
			if (arg[i] == ')')
				parenstack.pop();
			if (arg[i] == ',' && parenstack.empty()) {
				i++;
				break;
			}
			newterm += arg[i];
			i++;
		}
		//}

		cout << "newterm=" << newterm << endl;

		termlist.push_back(newterm);
	}
}

void parsetermlist(vector<string> & termlist, int scope) {
	cout << "inside parsetermlist()" << endl;

	for (int i = 0; i < termlist.size(); i++) {
		cout << "termlist[" << i << "]=" << termlist[i] << ";" << endl;
		string currentexpr = termlist[i];
		string parsedexpr;

		cout << currentexpr[0] << ' ' << currentexpr[currentexpr.length() - 1] << endl;

		if (currentexpr[0] == '"' && currentexpr[currentexpr.length() - 1] == '"')
			parsedexpr.append(currentexpr, 1, currentexpr.length() - 2);

		else {
			int j = 0;
			while (j < currentexpr.length()) {
				string newterm;


				while (currentexpr[j] == ' ' && j < currentexpr.length())
					j++;

				/*while (isalnum(currentexpr[j]) && j < currentexpr.length()) {
					newterm += currentexpr[j];
					j++;
				}*/
				while (currentexpr[j] != '+' && currentexpr[j] != '-' && currentexpr[j] != '*' && currentexpr[j] != '/' && j < currentexpr.length()) {
					newterm += currentexpr[j];
					j++;
				}

				cout << "newterm=" << newterm << ";" << endl;

				parsedexpr += evaluatenewterm(newterm, scope);
				if (currentexpr[j] == '(' && currentexpr[j + 1] == ')')
					j += 2;

				cout << "parsedexpr=" << parsedexpr << ';' << endl;

				newterm = "";

				while (currentexpr[j] == ' ' && j < currentexpr.length())
					j++;

				while ((currentexpr[j] == '*' || currentexpr[j] == '/' ||
					currentexpr[j] == '+' || currentexpr[j] == '-') && j < currentexpr.length()) {
					newterm += currentexpr[j];
					j++;
				}

				cout << "newterm=" << newterm << ";" << endl;

				parsedexpr += newterm;
				parsedexpr += ' ';

				cout << "parsedexpr=" << parsedexpr << ';' << endl;
				cout << "j=" << currentexpr[j] << endl;
				//sleep(2);
			}
		}
		cout << "parsedexpr=" << parsedexpr << ';' << endl;
		termlist[i] = parsedexpr;
		cout << "termlist[i]=" << termlist[i] << endl;
	}


}

string evaluatenewterm(string newterm, int scope) {
	cout << "inside evaluateterm()" << endl;
	cout << "newterm=" << newterm << endl;
	

	string returnstring;

	if (checkifconst(newterm)) {
		returnstring += newterm;
		returnstring += ' ';
	}
	else {
		//cout << "variable" << endl;
		string getfuncname;
		int i = 0;
		while (newterm[i] != '(' && i < newterm.length()) {
			getfuncname += newterm[i];
			i++;
		}
		cout << "getfuncname=" << getfuncname << endl;
		if (checkforfunction(getfuncname, Functions)) {
			cout << "func does exist" << endl;

			func_type * temp = getFunction(getfuncname, Functions);
			
			cout << "checkreturn=" << temp->doesreturn << endl;
			if (temp->doesreturn) {
				////cout << "returnvalue=" << temp->returnvalue << ';' << endl;
				temp->setreturn(newterm);
				string tempvalue = to_string(temp->returnvalue);
				returnstring += tempvalue;
				returnstring += ' ';
			}
			else {
				cout << "ERROR: Function does not return a value" << endl;
			}
			temp = NULL;
		}
		else {
			for (int j = scope; j >= 0; j--) {
				////cout << "scope=" << j << endl;

				if (checkforvariableinscope(newterm, Variables, j)) {
					////cout << "variable found in this scope:" << j << endl;
					variable * temp2 = getvariablescope(newterm, Variables, j);
					returnstring += to_string(temp2->value);
					returnstring += ' ';
					temp2 = NULL;
					break;
				}
				else
					cout << "error: variable does not exist:" << newterm << endl;
			}
		}
	}

	//cout << "returnstring=" << returnstring << endl;
	//sleep(5);
	return returnstring;
}

void findargument(string line, int & parenthesis1, int & parenthesis2) {
	int i = 0;

	while (line[i] != '(')
		i++;

	stack<char> parenstack;
	parenstack.push('(');

	parenthesis1 = i;
	i++;
	while (i < line.length()) {
		if (line[i] == '(')
			parenstack.push('(');
		if (line[i] == ')')
			parenstack.pop();
		if (parenstack.empty())
			break;
		i++;
	}
	parenthesis2 = i;
}
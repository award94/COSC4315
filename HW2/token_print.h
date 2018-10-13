using namespace std;

void findargument(string line, int & parenthesis1, int & parenthesis2);
void createtermlist(vector<string> & termlist, string arg);
void parsetermlist(vector<string> & termlist, int scope);
string evaluatenewterm(string newterm, int scope);

void print(string line, int scope) {
// Argument is used as a temporary variable to hold the contents before the delimiter
	// When the delimiter is reached, the strings are checked and appended to finalOutputt
	string finalOutput;
		
	//cout << "inside print" << endl;

	int i = 0;
	int parenthesis1;
	int parenthesis2;
	string arg;
	
	
	findargument(line, parenthesis1, parenthesis2);
	
	arg.append(line, parenthesis1+1, parenthesis2 - parenthesis1-1);
	
	vector<string> termlist;
	createtermlist(termlist, arg);
	parsetermlist(termlist, scope);
	//cout << "PARSED TERMS" << endl;
	for (int i = 0; i < termlist.size(); i++) {
		//cout << termlist[i] << endl;
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


	//cout << "finalOutput=" << finalOutput << endl;
	cout << finalOutput << endl;

	
}

void createtermlist(vector<string> & termlist, string arg) {
	//cout << "inside createtermlist()" << endl;
	//cout << "arg=" << arg << endl;

	for (int i = 0; i < arg.length(); i++) {

		string newterm;

		//cout << i << endl;

		while (arg[i] == ' ' && i < arg.length())
			i++;

		while (arg[i] != ',' && i < arg.length()) {
			newterm += arg[i];
			i++;
		}

		termlist.push_back(newterm);
	}
}

void parsetermlist(vector<string> & termlist, int scope) {
	//cout << "inside parsetermlist()" << endl;

	for (int i = 0; i < termlist.size(); i++) {
		//cout << "termlist[" << i << "]=" << termlist[i] << ";" << endl;
		string currentexpr = termlist[i];
		string parsedexpr;

		if (currentexpr[0] == '"' && currentexpr[currentexpr.length() - 1] == '"')
			parsedexpr.append(currentexpr, 1, currentexpr.length() - 2);

		else {
			int j = 0;
			while (j < currentexpr.length()) {
				string newterm;

				while (currentexpr[j] == ' ' && j < currentexpr.length())
					j++;

				while (isalnum(currentexpr[j]) && j < currentexpr.length()) {
					newterm += currentexpr[j];
					j++;
				}

				//cout << "newterm=" << newterm << ";" << endl;

				parsedexpr += evaluatenewterm(newterm, scope);
				if (currentexpr[j] == '(' && currentexpr[j + 1] == ')')
					j += 2;

				//cout << "parsedexpr=" << parsedexpr << ';' << endl;

				newterm = "";

				while (currentexpr[j] == ' ' && j < currentexpr.length())
					j++;

				while ((currentexpr[j] == '*' || currentexpr[j] == '/' ||
					currentexpr[j] == '+' || currentexpr[j] == '-') && j < currentexpr.length()) {
					newterm += currentexpr[j];
					j++;
				}

				//cout << "newterm=" << newterm << ";" << endl;

				parsedexpr += newterm;
				parsedexpr += ' ';

				//cout << "parsedexpr=" << parsedexpr << ';' << endl;
				//cout << "j=" << currentexpr[j] << endl;
				//sleep(2);
			}
		}
		//cout << "parsedexpr=" << parsedexpr << ';' << endl;
		termlist[i] = parsedexpr;
		//cout << "termlist[i]=" << termlist[i] << endl;
	}


}

string evaluatenewterm(string newterm, int scope) {
	//cout << "inside evaluateterm()" << endl;
	//cout << "newterm=" << newterm << endl;

	string returnstring;

	if (checkifconst(newterm)) {
		returnstring += newterm;
		returnstring += ' ';
	}
	else {
		//cout << "variable" << endl;
		if (checkforfunction(newterm, Functions)) {
			func_type * temp = getFunction(newterm, Functions);
			temp->execute();
			//cout << "checkreturn=" << temp->doesreturn << endl;
			if (temp->doesreturn) {
				//cout << "returnvalue=" << temp->returnvalue << ';' << endl;
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
				//cout << "scope=" << j << endl;

				if (checkforvariableinscope(newterm, Variables, j)) {
					//cout << "variable found in this scope:" << j << endl;
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
	return returnstring;
}

void findargument(string line, int & parenthesis1, int & parenthesis2) {
	int i = 0;
	while (i < line.length()) {
		while (line[i] != '(' && i < line.length())
			i++;
		if (line[i] == '(' && line[i + 1] != ')') {
			parenthesis1 = i;
			break;
		}
		else
			i++;
	}
	i = 0;
	while (i < line.length()) {
		while (line[i] != ')' && i < line.length()) {
			i++;
		}
		if (line[i] == ')' && line[i - 1] != '(') {
			parenthesis2 = i;
			break;
		}
		else
			i++;
	}
	//cout << "p1=" << parenthesis1 << " p2=" << parenthesis2 << endl;
}

	/*
	int i = 0;
	while (i < line.length()) {
		while (line[i] != ',') {
			argument += line[i];
			if (i < line.length()){
				i++;
			}
			// I get string subscript out of range without this break in the else statement
			else {
				break;
			}
		}
		while (line[i] == ',') {
			//Testing for const or variable
			if (checkifconst(argument) == 1){
			// If value is a constant, append to finaloutput
			cout << "Inside tokenprint, found a constant" << endl;	
			finalOutput += argument;
			}
			// I'm not entirely sure how to get the value that variables<argument> is 
			// Pointing to in inrder to append the value associated with argument
			if (checkforvariable(argument, Variables) == 1){
			cout << "Inside tokenprint, found a variable" << endl;
			// Create iterator to iterate through list and find the desired variable 
				for (list<variable*>::iterator it = Variables.begin(); it != Variables.end(); it++)
					if (argument == (*it)->name) {
						// Append theh value of the desired variable  to the finaloutput string
						finalOutput += (*it)->value;
					}
			}
			// I need to add in a check to see if it's an arithmetic operation
			// wasn't sure whichh function to call, so i just left a comment for now
			finalOutput += argument;
			argument.clear();
			if (i < line.length()){
				i++;
			}
			// I get string subscript out of range without this break in the else statement
			else {
				break;
			}
		} 
	}
<<<<<<< .mine
	cout << "Final output is: " << finalOutput << endl;
*/
/*
||||||| .r69
	// Printing the final part of the print statement that get's read after the final ,
	// appending the final value of argument to finalOutput
	if (checkifconst(argument) == 1){
	finalOutput += argument;
	}
	if (checkforvariable(argument, Variables) == 1){
	for (list<variable*>::iterator it = Variables.begin(); it != Variables.end(); it++){
		if (argument == (*it)->name){
			finalOutput += (*it)->value;
		}
	}
	finalOutput += argument;
	argument.clear();
cout << "Final output is: " << finalOutput << endl;
}
=======
	// Printing the final part of the print statement that get's read after the final ,
	// appending the final value of argument to finalOutput
	if (checkifconst(argument) == 1){
	finalOutput += argument;
	}
	if (checkforvariable(argument, Variables) == 1) {
		for (list<variable*>::iterator it = Variables.begin(); it != Variables.end(); it++) {
			if (argument == (*it)->name) {
				finalOutput += (*it)->value;
			}
		}
	}
	finalOutput += argument;
	argument.clear();
cout << "Final output is: " << finalOutput << endl;
}
>>>>>>> .r70
*/
/*
SUGGESTION FOR PARSING OUT WHAT YOU'RE PRINTING
line = "print(this, is, what, you, want, to, grab)";
string nextvar;								//each word in "this, is, what, you, want, to, grab"

string argument;							//put "this, is, what, you, want, to, grab" here
											// after finding the value of each word
											//(Whether or not it is a constant or variable)

int i = 0 ;

while(line[i] == ' ')
	i++;
while(line[i] != '(')
	i++;
while(line[i] = ' ')
	i++;

	This now has i at t's index after the parenthesis in print(this, is, what, you, want, to, grab);
															i->^
												grab all this->^---------------------------------^
	Now you can grab all those variables inside until you find a ')'

while(line[i] != ',')
	nextvar += line[i]

argument += nextvar;
argument += ' ';
*/


/*
do {
// Remove whitespace
if (arg[i] == ' ') {
//cout << "Whitespace removed" << endl;
i++;
}
// Takes care of constants
if (arg[i] == '"') {
//cout << "First quote encountered " << endl;
i++;
while (arg[i] != '"') {
//cout << "Searching for second quote " << endl;
argument += arg[i];
i++;
}
finalOutput += argument;
finalOutput += ' ';
argument.clear();
// Need a second increment to skip over the comma
i++;
}
// Starting the check to see if arg is a variable
if (arg[i] != ',') {
//cout << "Searching for a comma " << endl;
argument += arg[i];
i++;
}
if (arg[i] == ',' || i == arg.length()) {
// Seems like this block of code is repeated later

// Testing for duplicate
while (i < arg.length()) {
//cout << line[i] << endl;

//cout << "inside loop" << endl;

while (arg[i] == ' ') {
i++;
}
cout << "inside arithmetic check" << endl;
cout << arg[i] << endl;

if (arg[i] == '+' || arg[i] == '-' || arg[i] == '*' || arg[i] == '/') {
argument.append(arg, i, 1);
i++;
}
//cout << i<<" tempterm=" << tempterm << 'a'<<endl;
//cout << tempterm.compare("-") << endl;

if ((argument.compare("+") == 0) || (argument.compare("-") == 0 ||
argument.compare("*") == 0) || (argument.compare("/") == 0)) {
cout << "operator=" << argument << endl;
finalOutput.append(argument);
finalOutput += ' ';
// Testing
argument.clear();
i++;
}

while (arg[i] == ' ')
i++;

//argument = "";

if (arg[i] == '-') {
argument += arg[i];
i++;
}

while (isalnum(arg[i])) {
//cout << line[i] << endl;
argument.append(arg, i, 1);
i++;
}

if ((i + 2) <= arg.length()) {
//cout << "next 2:"<<line[i] << line[i + 1] << endl;
if (arg[i] == '(' && arg[i + 1] == ')') {
i += 2;
}
}

while (arg[i] == ' ')
i++;
// End of insertion

//If constant append it to RHS
// Changed the argument//If variable lookup value and append it to RHS
if (checkifconst(argument)) {
cout << "is a constant: " << argument <<";"<< endl;
finalOutput.append(argument);
finalOutput += ' ';
//Testing
argument.clear();
i++;
}
else {
cout << "variable:" << argument <<endl;
if (checkforfunction(argument, Functions)) {
cout << "found function" << endl;
func_type * temp = getFunction(argument, Functions);
cout << temp->returnvalue << endl;

finalOutput += to_string(temp->returnvalue);
finalOutput += ' ';

temp = NULL;
// Testing
i++;
}
else {
for (int j = 2; j >= 0; j--){
//for (int j = scopelevel; j >= 0; j--) {
cout << "scope=" << j << endl;

if (checkforvariableinscope(argument, Variables, j)) {
cout << "found variable in this scope:" << j << endl;
variable * temp = getvariablescope(argument, Variables, j);
finalOutput += to_string(temp->value);
finalOutput += ' ';
temp = NULL;
// Testing
i++;
argument.clear();
break;
}
else
cout << "error: variable does not exist:" << argument << endl;
}
}
}


//RHS After first time is appended
//cout << "RHS=" << RHS << endl;
//cout << i << ' ' << line.length() << endl;

//Loops through rest of RHS
//Finds Opertator and appends to RHS
//Then finds Constant and appends to RHS

finalOutput += argument;
// Delete
finalOutput += ' ';
// Delete
argument.clear();
i++;

}
} // Added in

} while (i < arg.length());


cout << "Line is: " << line << endl;
cout << "arg=" << arg << endl;
cout << "Final output is: " << finalOutput << endl;
*/
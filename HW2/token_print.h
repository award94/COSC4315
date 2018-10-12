using namespace std;

void findargument(string line, int & parenthesis1, int & parenthesis2);

void print(string line) {
// Argument is used as a temporary variable to hold the contents before the delimiter
	// When the delimiter is reached, the strings are checked and appended to finalOutputt
	string argument;
	string finalOutput;
	cout << "this is the line:"<<line << endl;

	// try string streaming until you hit the comma
	
	int i = 0;
	int parenthesis1;
	int parenthesis2;
	string arg;
	
	
	findargument(line, parenthesis1, parenthesis2);
	
	arg.append(line, parenthesis1+1, parenthesis2 - parenthesis1-1);
	
	do {
		//cout << "Inside the do statement, doing the dew" << endl;
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
				cout << "Searching for second quote " << endl;
				argument += arg[i];
				i++;
			}
			finalOutput += argument;
			// If this works keep  otherwise delete
			finalOutput += ' ';
			// Delete to here

			argument.clear();
			// Need a second increment to skip over the comma
			i++;
		} 
		// Starting the chheck to see if arg is a variable
		if (arg[i] != ',') {
			//cout << "Searching for a comma " << endl;
			argument += arg[i];
			i++;
		}	
		// argument being read is a comma
		if (arg[i] == ',' || i == arg.length()) {
			//cout << "Found a comma" << endl;
			//cout << "Argument is: " << argument << endl;
			// Check if arg is a variable

			// Couldn't figure out how to check if it's a variable
			// Could you take a look at this when you're bored?
			if (checkforvariable(argument, Variables) == true)
				{
				cout << "Found is a variable " << endl;
				variable* temp;
				//Printing all variables
				printVariables(Variables);
				temp = getvariable(argument, Variables);
				cout << "Temp value is: " << temp->value << endl;
				finalOutput += temp->value;
				finalOutput += ' '; 
				temp = NULL;
			}
			// Checking if argument is a function
			else{
				if (checkifconst(argument)){
					finalOutput.append(argument);
					finalOutput += ' ';
					argument.clear();
				}
				else{
					cout << "Variable: " << argument << endl;
					if (checkforfunction(argument, Functions)){
					cout << "found function" << endl;
					func_type * temp = getFunction(argument, Functions);
					cout << temp->returnvalue << endl;

					finalOutput += to_string(temp->returnvalue);
					finalOutput += ' ';
					}
					}
			}
			// End of testing for variabe segment
			// Add in arithmetic check and print will be functioning	
		finalOutput += argument;
			// Delete 
		finalOutput += ' ';
			// Delete
		argument.clear();
		i++;
		}

	} while (i < arg.length());


	cout << "Line is: " << line << endl;
	cout << "arg=" << arg << endl;
	cout << "Final output is: " << finalOutput << endl;
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
	cout << "p1=" << parenthesis1 << " p2=" << parenthesis2 << endl;
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

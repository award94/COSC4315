using namespace std;

void print(string line) {
	// Argument is used as a temporary variable to hold the contents before the delimiter
	// When the delimiter is reached, the strings are checked and appended to finalOutputt
	string argument;
	string finalOutput;

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
			finalOutput += argument;
			}
			// I'm not entirely sure how to get the value that variables<argument> is 
			// Pointing to in inrder to append the value associated with argument
			if (checkforvariable(argument, Variables) == 1){
			finalOutput += argument;
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
cout << "Final output is: " << finalOutput << endl;
}

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

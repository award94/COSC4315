using namespace std;
#include "stdlib.h"

void print(string line, list<variable*> & Variables) {
	//string line = "something something, darkside, hello, its me";
	// print statement is separated by commas so make comma the delimiter
	string delimiter = ",";
	// final string to  be outputed
	string finalOutput;
	string token;
	size_t pos = 0;
	
	// While loop to loop through line 
	while ((pos = line.find(delimiter)) != std::string::npos) {
		cout << "Line is: " << line << endl;
		// Adding to theh finaloutputt string
		token = line.substr(0, pos);
		finalOutput += token;
		finalOutput += " ";
		// TBH i probably shouldn't erase the linei as I go but it seems to kind of work
		// I'll find a replacement 
		line.erase(0, pos + delimiter.length());
	}
	
	cout << finalOutput << endl;
/*
	// Create a string object that will be cout'd at the end
	string finalOutput;
	// Parsing the argument line that will serve as the input to the print statement
	cout << "Final value of line is: " << line << endl;	


	// append them to the string you're printing. if they're variales 
	cout << "inside print()" << endl;
	// Check for type of input, if type is string or anything besides int, just cout it
	// If type is int call the arithmetic func Adam wrote
	// Parse with a comma delimiter
*/
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
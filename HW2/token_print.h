using namespace std;

void print(string line, list<variable*> & Variables) {
	//string line = "something something, darkside, hello, its me";
	string delimiter = ",";
	string finalOutput;
	auto start = 0U;
	auto end = line.find(delimiter);
	
	

	// Alternative method
	while (end != std::string::npos) {
		cout << line.substr(start, end - start) << endl;
		start = end + delimiter.length();
		end = line.find(delimiter, start);
	}

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


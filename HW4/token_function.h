using namespace std;

string findfuncname(string line);
int findlastlinefunc(int startLineNum, int funcscope);


void createNewFunc(string line, int & lineNum, int scopelevel,string stackname, int nestlevel){
	//cout << endl << "==========FUNCTION SCOPE BEGIN============" << endl;

	func_type * newFunc = new func_type();
	newFunc->defline = line;
	//cout << "defline=" << newFunc->defline << endl;
	newFunc->scope = scopelevel + 1;
	newFunc->findfuncname();
	newFunc->startline = lineNum;
	//cout << "startline=" << newFunc->startline	<< endl;
	newFunc->findlastline();
	//cout << "endline=" << newFunc->endline << endl;

	newFunc->checkreturn();
	//cout << "doesreturn=" << newFunc->doesreturn << endl;
	//if (newFunc->doesreturn) {
	//	newFunc->setreturn();
		//cout << "returnvalue=" << newFunc->returnvalue << endl;
	//}
	
	lineNum = newFunc->endline;
	newFunc->createarglist();

	Functions.push_back(newFunc);
	newFunc = NULL;

	//cout << "==========FUNCTION SCOPE END============" << endl;
}

int findlastlinefunc(int startLineNum, int funcscope) {
	//cout << "findlastline" << endl;
	//cout << startLineNum << endl;
	//cout << "filesize=" << fileLines.size() << endl;

	int i = startLineNum;
	while (i < fileLines.size()-1) {
		i++;
		string currentLine = fileLines[i];

		int k = 0;
		string commentCheck;
		while (currentLine[k] == ' ' && k < currentLine.length()) {
			k++;
		}
		while ((isalnum(currentLine[k]) || currentLine[k] == '#') && k < currentLine.length()) {
			commentCheck += currentLine[k];
			k++;
		}

		if (!currentLine.empty() && (commentCheck[0] != '#')) {
			//cout << currentLine << " ("<<i<<")"<<endl;

			bool checkscope = 1;
			for (int j = 0; j < 3 * funcscope; j++) {
				//cout << currentLine[j];
				if (currentLine[j] != ' ') {
					checkscope = 0;
				}
			}
			//cout << "checkscope=" << checkscope << endl;
			if (checkscope == 0) {
				i -= 1;
				break;
			}
		}
	}
	//cout <<"last line num = "<< i << endl;
	return i;
}

string findfuncname(string line) {
	string name;

	int i = 0;

	while (line[i] == ' ')
		i++;

	while (isalnum(line[i]))
		i++;

	while (line[i] == ' ')
		i++;

	while (isalnum(line[i]) && i < line.length()) {
		name += line[i];
		i++;
	}

	name += "()";

	return name;
}
using namespace std;

string findfuncname(string line);
int findlastlinefunc(int startLineNum, int funcscope);


void createNewFunc(string line, int & lineNum, int scopelevel){
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
	if (newFunc->doesreturn) {
		newFunc->setreturn();
		//cout << "returnvalue=" << newFunc->returnvalue << endl;
	}
	
	lineNum = newFunc->endline;

	Functions.push_back(newFunc);
	newFunc = NULL;

	//cout << "==========FUNCTION SCOPE END============" << endl;

	/*
	

	int funcscope = scopelevel + 1;

	string funcName = findfuncname(line);
	//cout<<"found funcname"<<endl;
	float funcResult;

	vector<string> funcstatements;

	//cout << endl << "current line#=" << lineNum << endl;
	int lastLine = findlastlinefunc(lineNum, funcscope);
	//cout << "found lastline" << endl;
	
	cout << "ENTIRE FUNCION DEFINITION" << endl;
	for (int i = lineNum; i <= lastLine; i++) {
		cout << fileLines[i] << endl;
	}
	cout << "start line = " << lineNum << endl;
	cout << "last line = " << lastLine << endl;

	cout << "STARTING TO PROCESS LINES IN FUNCTION" << endl;
	for (int i = lineNum; i <= lastLine; i++) {
		//cout << fileLines[i] << endl;
		string currentLine = fileLines[i];
		if (!currentLine.empty()) {
			bool lineinscope = 1;
			for (int j = 0; j < funcscope * 3; j++) {
				if (currentLine[j] != ' ')
					lineinscope = 0;
			}
			//cout << "lineinscope=" << lineinscope << endl;
			if (currentLine[(funcscope * 3)] == ' ') {
				//cout << "funcscope=" << funcscope << endl;
				//cout << currentLine[(funcscope * 3)] << endl;
				lineinscope = 0;
			}
			//cout << "lineinscope=" << lineinscope << endl;
			//cout << "isthisline in scope=" << lineinscope << endl;

			if (lineinscope) {
				int j = 0;
				while (currentLine[j] == ' ')
					j++;

				string nextvar;

				while (currentLine[j] != ' ' && j < currentLine.length())
					nextvar += currentLine[j++];

				processstatement(i, currentLine, lastLine, funcscope, funcName);
			}
		}

	}
	deleteScope(Variables, funcscope);
	

	lineNum = lastLine;
	*/
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

/*

//cout << "nextvar=" << nextvar << ';'<< endl;


if (nextvar.compare("return") != 0) {
//cout << "I will process this statement" << endl;

}
else {
cout << "assigning return value" << endl;
float returnvalue = setreturnvalue(currentLine, funcName, funcscope);
variable * temp = getvariable(funcName, Variables);
temp->value = returnvalue;
temp = NULL;
cout << "ending function because return found" << endl;
lineNum = lastLine;
}

bool checkreturn(int startLine, int lastLine, int scopelevel);


bool checkreturn(int startLine, int lastLine, int scopelevel) {
//cout << "inside checkreturn()" << endl;
//cout << "scope=" << scopelevel << endl;

for (int i = startLine + 1; i <= lastLine; i++) {
cout << fileLines[i] << endl;
string currentLine = fileLines[i];

bool lineinscope = 1;
for (int j = 0; j < scopelevel * 3; j++) {
if (currentLine[j] != ' ')
lineinscope = 0;
}
if (currentLine[(scopelevel * 3) + 1] == ' ')
lineinscope = 0;
//cout << "isthisline in scope=" << lineinscope << endl;

int j = 0;
while (currentLine[j] == ' ')
j++;

string nextvar;

while (currentLine[j] != ' ' && j < currentLine.length())
nextvar += currentLine[j++];

//cout << "nextvar="<<nextvar << endl;

if (lineinscope && nextvar.compare("return") == 0)
return 1;
}

return 0;
}

*/
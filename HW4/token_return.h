using namespace std;

float setreturnvalue(string line, string funcName, int funcscope, int nestlevel);

void setreturn(string line, int & lineNum, int lastline, int scopelevel, string funcname, int nestlevel) {
	//cout << "inside setreturn" << endl;
	//cout << "\t\t\t"<<line << endl;
	//cout << "funcname=" << funcname << endl;
	//cout << "lineNum=" << lineNum << endl;
	//cout << "lastline=" << lastline << endl;
	//cout << "scopelevel=" << scopelevel << endl;
	//cout << "nestlevel=" << nestlevel << endl;

	//printVariables(Variables);

	createNewVar(funcname, Variables, scopelevel-1);

	float returnvalue = setreturnvalue(line, funcname, scopelevel, nestlevel);
	//cout << "======================================================" << endl;
	//cout << "returnvalue of scope:" << scopelevel << "=" << returnvalue << endl;
	//cout << "======================================================" << endl;
	variable * temp = getvariablescope(funcname, Variables, scopelevel-1);
	temp->value = returnvalue;
	temp = NULL;
	func_type * temp2 = getFunction(funcname, Functions);
	temp2->returnvalue = returnvalue;
	temp2 = NULL;
	//printVariables(Variables);
	//printFunctions(Functions);

	lineNum = lastline;
}

float setreturnvalue(string line, string funcName, int funcscope, int nestlevel) {
	//cout << "inside setreturnvalue" << endl;
	//cout << "line:" << line << endl;
	//cout << "funcName:" << funcName << endl;
	//cout << "scope=" << funcscope << endl;

	string alreadypassed;
	string RHS;
	int i = 0;

	while (line[i] == ' ' && i < line.length()) {
		alreadypassed += line[i];
		i++;
	}
	while (isalnum(line[i]) && i < line.length()) {
		alreadypassed += line[i];
		i++;
	}
	while (line[i] == ' ' && i < line.length()) {
		alreadypassed += line[i];
		i++;
	}	

	string tempterm;

	stack<char> parenstack;
	while (i < line.length()) {
		if ((line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/' ||
			line[i] == ' ') && parenstack.empty()) {
			break;
		}
		if (line[i] == '(') {
			parenstack.push('(');
		}
		if (line[i] == ')') {
			parenstack.pop();
		}
		tempterm += line[i];
		i++;
	}

	//cout << "tempterm=" << tempterm << ";" << endl;
	RHS += evaluatenewterm(tempterm, funcscope, nestlevel);
	//cout << "RHS=" << RHS << ";" << endl;

	string tempTerm;

	while (line[i] == ' ') {
		i++;
	}

	while (i < line.length()) {
		tempterm = "";
		//cout << line[i] << endl;

		//cout << "inside loop" << endl;
		while (line[i] == ' ') {
			i++;
		}
		//cout << line[i] << endl;

		if (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/') {
			tempterm.append(line, i, 1);
			i++;
		}
		//cout << i<<" tempterm=" << tempterm << 'a'<<endl;
		//cout << tempterm.compare("-") << endl;

		if ((tempterm.compare("+") == 0) || (tempterm.compare("-") == 0 ||
			tempterm.compare("*") == 0) || (tempterm.compare("/") == 0)) {
			//cout << "operator=" << tempterm << endl;
			RHS.append(tempterm);
			RHS += ' ';
		}

		while (line[i] == ' ')
			i++;

		tempterm = "";

		if (line[i] == '-') {
			tempterm += line[i];
			i++;
		}

		stack<char> parenstack2;
		while (i < line.length()) {
			if ((line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/' ||
				line[i] == ' ') && parenstack2.empty()) {
				break;
			}
			if (line[i] == '(') {
				parenstack2.push('(');
			}
			if (line[i] == ')') {
				parenstack2.pop();
			}
			tempterm += line[i];
			i++;
		}

		while (line[i] == ' ')
			i++;

		//cout << tempterm << endl;

		RHS += evaluatenewterm(tempterm, funcscope, nestlevel);

		//cout << "RHS=" << RHS << endl;
	}
	/*
	while (i < line.length()) {
		tempTerm = "";

		while ((!isalnum(line[i]) && line[i] != ' ') && i < line.length()) {
			tempTerm += line[i];
			i++;
		}
		if ((tempTerm.compare("+") == 0) || (tempTerm.compare("-") == 0 ||
			tempTerm.compare("*") == 0) || (tempTerm.compare("/") == 0)) {
			RHS += tempTerm;
			RHS += ' ';
		}

		while (line[i] == ' ' && i < line.length())
			i++;

		tempTerm = "";

		if (line[i] == '-') {
			tempTerm += line[i];
			i++;
		}

		while (isalnum(line[i]) && i < line.length()) {
			//cout << line[i] << endl;
			tempTerm.append(line, i, 1);
			i++;
		}
		if ((i + 2) <= line.length()) {
			//cout << "next 2:"<<line[i] << line[i + 1] << endl;
			if (line[i] == '(' && line[i + 1] == ')') {
				tempTerm += "()";
				i += 2;
			}
		}

		while (line[i] == ' ' && i < line.length())
			i++;

		if (checkifconst(tempTerm)) {
			RHS += tempTerm;
			RHS += ' ';
		}
		else {
			for (int j = funcscope; j >= 0; j--) {
				//cout << "scope=" << j << endl;
				if (checkforvariableinscope(tempTerm, Variables, j)) {
					//cout << "found variable in this scope:" << j << endl;
					variable * temp = getvariablescope(tempTerm, Variables, j);
					//cout << "value=" << temp->value << endl;
					RHS += to_string(temp->value);
					RHS += ' ';
					temp = NULL;
					break;
				}
				else {
					//cout << "error: variable does not exist:" << tempTerm << endl;
				}
			}
		}
	}
	*/
	//cout << "RHS:" << RHS << endl;
	postfixconverter converter;
	RHS = converter.convertToPostfix(RHS);
	//cout << "RHS:" << RHS << endl;
	return computeresult(RHS);
}
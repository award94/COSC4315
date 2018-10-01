using namespace std;

bool checkifconst(string Var);
void convertToConstants(string & line, list<variable*> & Variables, string & RHS,
	string & LHS);
float computeresult(string exp);

void assignment(string line, list<variable*> & Variables) {
	string RHS;
	string LHS;
	string pfxRHS;

	//converts RHS to a series of constants
	convertToConstants(line, Variables, RHS, LHS);
	//converts RHS to postfix notation
	postfixconverter converter;
	pfxRHS = converter.convertToPostfix(RHS);

	//computes result
	float result = computeresult(pfxRHS);

	//assigns result to LHS Variable
	variable * lhsvar = getvariable(LHS, Variables);
	lhsvar->value = result;
	cout << lhsvar->name << '=' << lhsvar->value << endl;
	lhsvar = NULL;
}

bool checkifconst(string Var) {
	for (int i = 0; i < Var.length(); i++) {
		if (isdigit(Var[i]) == false)
			return false;
	}
	return true;
}

void convertToConstants(string & line, list<variable*> & Variables, string & RHS,
	string & LHS) {
	int i = 0;

	//parse LHS variable

	while (line[i] == ' ')
		i++;

	while (isalnum(line[i])) {
		LHS.append(line, i, 1);
		i++;
	}

	

	//Check if LHS Var has been declared yet
	//If not, declare it
	if (!checkforvariable(LHS, Variables)) {
		createNewVar(LHS, Variables);
	}

	//Skipping whitespaces
	while (line[i] == ' ')
		i++;


	//Error checking for '='
	if (line[i] != '=')
		cout << "Error invalid assignment format" << endl;
	else
		i++;

	while (line[i] == ' ')
		i++;


	//Finding First term in RHS
	string tempterm;
	while (isalnum(line[i])) {
		//cout << line[i] << endl;
		tempterm.append(line, i, 1);
		i++;
	}

	//cout << tempterm << endl;

	//If constant append it to RHS
	//If variable lookup value and append it to RHS
	if (checkifconst(tempterm)) {
		//cout << "is a constant" << endl;
		RHS.append(tempterm);
	}
	else {
		//cout << "variable" << endl;
		variable * grabValue = getvariable(tempterm, Variables);
		if (grabValue == NULL)
			cout << "error: " << tempterm << " is undefined at this point" << endl;
		else {
			RHS.append(to_string(grabValue->value));
			grabValue = NULL;
		}
	}

	//cout << "RHS=" << RHS << endl;
	//cout << i << ' ' << line.length() << endl;

	//Loops through rest of RHS
	//Finds Opertator and appends to RHS
	//Then finds Constant and appends to RHS
	while (i < line.length()) {
		tempterm = "";

		//cout << "inside loop" << endl;
		while (line[i] == ' ')
			i++;

		while (!isalnum(line[i])) {
			tempterm.append(line, i, 1);
			i++;
		}

		if ((tempterm.compare("+") == 0) || (tempterm.compare("-") == 0 ||
			tempterm.compare("*") == 0) || (tempterm.compare("/") == 0)) {
			RHS.append(tempterm);
		}

		while (line[i] == ' ')
			i++;

		tempterm = "";

		while (isalnum(line[i])) {
			//cout << line[i] << endl;
			tempterm.append(line, i, 1);
			i++;
		}

		while (line[i] == ' ')
			i++;

		//cout << tempterm << endl;

		if (checkifconst(tempterm)) {
			//cout << "is a constant" << endl;
			RHS.append(tempterm);
		}
		else {
			//cout << "variable" << endl;
			variable * grabValue = getvariable(tempterm, Variables);
			if (grabValue == NULL)
				cout << "error: " << tempterm << " is undefined at this point" << endl;
			else {
				RHS.append(to_string(grabValue->value));
				grabValue = NULL;
			}
		}

		//cout << "RHS=" << RHS << endl;
	}
}

float computeresult(string exp) {
	//cout << exp << endl;

	list<string> explist;
	int i = 0;

	while (i < exp.length()) {
		string toadd = "";
		while (i < exp.length() && exp[i] != ' ') {
			toadd += exp[i];
			i++;
		}
		//cout << toadd << endl;
		while (exp[i] == ' ')
			i++;
		explist.push_back(toadd);
	}

	stack<float> numbers;

	while (explist.size() != 0) {
		if (explist.front().compare("+") != 0 && explist.front().compare("-") != 0 &&
			explist.front().compare("*") != 0 && explist.front().compare("/") != 0) {
			//cout << "number found" << endl;
			float tempfloat = stof(explist.front());
			numbers.push(tempfloat);
			explist.pop_front();
		}
		else {
			//cout << "operator found" << endl;
			char op = explist.front()[0];
			explist.pop_front();

			float term2 = numbers.top();
			numbers.pop();
			float term1 = numbers.top();
			numbers.pop();
			float term3;

			//cout << "term1=" << term1 << " term2=" << term2 << endl;

			switch (op) {
			case('+'):
				//cout << "addition" << endl;
				term3 = term1 + term2;
				break;
			case('-'):
				//cout << "subtraction" << endl;
				term3 = term1 - term2;
				break;
			case('*'):
				//cout << "multiplication" << endl;
				term3 = term1 * term2;
				break;
			case('/'):
				//cout << "division" << endl;
				term3 = term1 / term2;
				break;
			default:
				//cout << "error" << endl;
				break;
			}

			//cout << "term3 = " << term3 << endl;
			numbers.push(term3);
		}
	}

	return numbers.top();
}

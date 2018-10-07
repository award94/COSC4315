using namespace std;

class postfixconverter{
	public:
		bool precedence(char opr1, char opr2);
		string convertToPostfix(string expression);
		void setInfix(string a);
		string getInfix();
		string getPostfix();
		int getResult();
		postfixconverter(string a); //Default constructor

		stack<float> intstack;
		stack<char> operstack;

	private:
		string ifx;
		string pfx;

		int result;
};

bool postfixconverter::precedence(char opr1, char opr2){
	//cout << "inside postfixconverter()" << endl;
	if (opr2 == 0)
		return 1;
	if ((opr2 == '+' || opr2 == '-') && (opr1 == '*' || opr1 == '/'))
		return 1;

	return 0;
}

string postfixconverter::convertToPostfix(string expression) {
	cout << "inside convertToPostfix()" << endl;
	cout << "expression=" << expression << ';' << endl;

	string pfxexpression = "";

	int i = 0;
	while (i < expression.length()) {

		string newsymbol;

		while (expression[i] != ' ') {
			newsymbol += expression[i];
			i++;
		}
		//cout << "newsymbol=" << newsymbol << endl;

		while (expression[i] == ' ')
			i++;
		
		if ((newsymbol[0] == '+' || newsymbol[0] == '-' || newsymbol[0] == '*' || newsymbol[0] == '/') && newsymbol.length() == 1) {
			char newoperator = newsymbol[0];
			//cout << newoperator << endl;

			if (operstack.size() == 0) {
				//cout << "empty stack" << endl;
				operstack.push(newoperator);

				//cout << "adding " << newoperator << ": to the stack" << endl;

			}
			else if (precedence(newoperator, operstack.top())) {
				//cout << "new symbol has precedence" << endl;

				operstack.push(newoperator);

				//cout << "adding " << newoperator << " to the stack" << endl;

			}
			else {

				//cout << "adding " << operstack.top() << " to the pfx" << endl;
				//cout << "adding " << newoperator << " to the stack" << endl;

				if (operstack.size() != 0) {
					pfxexpression += operstack.top();
					pfxexpression += ' ';
					operstack.pop();
				}

				operstack.push(newoperator);

			}
		}
		else {
			pfxexpression += newsymbol;
			pfxexpression += ' ';
		}
	}


	while (operstack.size() != 0) {
		//cout << "top of operstack=" << operstack.top() << endl;
		pfxexpression += operstack.top();
		pfxexpression += ' ';
		operstack.pop();
	}
	cout << endl;

	//cout << "pfxexpression=" << pfxexpression << endl;
	return pfxexpression;
}

void postfixconverter::setInfix(string a) {
	ifx = a;
}

string postfixconverter::getInfix() {
	return ifx;
}

string postfixconverter::getPostfix() {
	return pfx;
}

int postfixconverter::getResult() {
	return result;
}

postfixconverter::postfixconverter(string a = "") {
	ifx = a;
	pfx = "";

	result = -1;
}


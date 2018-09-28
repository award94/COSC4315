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
	//cout << "inside convertToPostfix()" << endl;

	string pfxexpression = "";

	int i = 0;
	while (i < expression.length()) {

		if (isdigit(expression[i])) {

			//cout << "digit found" << endl;

			string strnewnumber = "";

			while ((isdigit(expression[i]) || expression[i] == '.') && i < expression.length()) {
				strnewnumber.append(expression, i, 1);
				i++;
			}	

			pfxexpression.append(strnewnumber);
			pfxexpression.append(" ");

			//cout << "Adding " << strnewnumber << " to the pfx" << endl;
		}

		else if (expression[i] == '+' || expression[i] == '-' ||
			expression[i] == '*' || expression[i] == '/') {
			//cout << "operator found" << endl;

			char newoperator = expression[i];

			//cout << newoperator << endl;

			if (operstack.size() == 0) {
				//cout << "empty stack" << endl;
				operstack.push(newoperator);

				//cout << "adding " << newoperator << " to the stack" << endl;

			}
			else if (precedence(newoperator, operstack.top())) {
				//cout << "new symbol has precedence" << endl;
				
				operstack.push(newoperator);

				//cout << "adding " << newoperator << " to the stack" << endl;

			}
			else {

				//cout << "adding " << operstack.top() << " to the pfx" << endl;
				//cout << "adding " << newoperator << " to the stack" << endl;

				pfxexpression += operstack.top();
				pfxexpression += ' ';
				operstack.pop();

				if (operstack.size() != 0) {
					pfxexpression += operstack.top();
					pfxexpression += ' ';
					operstack.pop();
				}

				operstack.push(newoperator);

			}


			i++;
		}
	}

	while (operstack.size() != 0) {
		pfxexpression += operstack.top();
		pfxexpression += ' ';
		operstack.pop();
	}
	cout << endl;

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


using namespace std;

class postfixconverter{
	public:
		bool precedence(char opr1, char opr2);
		void convertToPostfix();
		void setInfix(string a);
		string getInfix();
		string getPostfix();
		int getResult();
		postfixconverter(string a); //Default constructor

	private:
		string ifx;
		string pfx;

		int result;
};

bool postfixconverter::precedence(char opr1, char opr2){
	cout << "inside postfixconverter()" << endl;
}

void postfixconverter::convertToPostfix() {
	cout << "inside convertToPostfix()" << endl;
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


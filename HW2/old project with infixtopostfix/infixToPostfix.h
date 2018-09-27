using namespace std;

class infixToPostfix{
	public:
		bool precedence(char opr1, char opr2);
		void convertToPostfix();
		void getInfix(string a);
		void showInfix();
		void showPostfix();
		infixToPostfix(string a); //Default constructor
			
	private:
		string ifx;
		string pfx;
};

void infixToPostfix::convertToPostfix(){
	stack opstack;
	
	node * termNodes[ifx.length()];
	for(int i = 0; i < ifx.length(); i++){
		termNodes[i] = new node;
		termNodes[i]->setValue(ifx[i]);
		
		if(isalpha(ifx[i]))
			pfx += ifx[i];
			
		if(ifx[i] == '(')
			opstack.push(termNodes[i]);
			
		if(ifx[i] == ')'){
			opstack.push(termNodes[i]);
			while(opstack.peekTop() != '('){
				if(opstack.peekTop() == ')')
					opstack.pop();
				else
					pfx += opstack.pop();
			}
			opstack.pop();
		}
			
		if(ifx[i] == '+' || ifx[i] == '-' || ifx[i] == '*' || ifx[i] =='/'){
			if(opstack.peekTop() == '-' || opstack.peekTop () == '+' ||
				opstack.peekTop() == '*' || opstack.peekTop() == '/'){
					if(precedence(ifx[i], opstack.peekTop())){
						while(precedence(ifx[i], opstack.peekTop()))
							opstack.push(termNodes[i]);
					}
					else{
						pfx += opstack.pop();
						opstack.push(termNodes[i]);	
					}
				}
			else
				opstack.push(termNodes[i]);
		}
	}
	
	while(opstack.peekTop()){
		pfx += opstack.pop();	
	}
}

bool infixToPostfix::precedence(char opr1, char opr2){
	if(opr2 == 0)
		return 1;
	if((opr2 == '+' || opr2 == '-') && (opr1 == '*' || opr1 == '/'))
		return 1;
		
	return 0;
	
}

void infixToPostfix::getInfix(string a){
	ifx = a;
}

void infixToPostfix::showInfix(){
	cout<<ifx;	
}

void infixToPostfix::showPostfix(){
	cout<<pfx;	
}

infixToPostfix::infixToPostfix(string a = ""){
	ifx = a;
	pfx = "";	
}



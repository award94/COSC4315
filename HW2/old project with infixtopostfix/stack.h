using namespace std;

class stack{
	friend class node;
	
	public:
		void push(node * a);
		char pop();
		char peekTop();
		
		void print();
		
		stack();
		~stack();
	
	private:
		node * top;
		
};

void stack::push(node * a){
	node * temp;
	temp = top;
	top = a;
	top->previous = temp;
	
	temp = NULL;
}

char stack::pop(){
	node * temp = top;
	top = top->previous;
	char tempValue = temp->value;
	delete temp;
	return tempValue;	
}

char stack::peekTop(){
	char tempValue = top->value;
	return tempValue;
}

void stack::print(){
	node * temp = top;
	while(temp){
		cout<<temp->value;
		temp = temp->previous;
	}
	cout<<endl;
}

stack::stack(){
	top = new node;	
}

stack::~stack(){
	node * temp = top;
	while(temp){
		top = top->previous;
		delete temp;
		temp = top;
	}
}

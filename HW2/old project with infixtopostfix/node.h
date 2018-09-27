using namespace std;
class node{
	friend class stack;
	
	public:
		node(char a, node *b);
		void print() const;
		
		void setValue(char a);
		void setPrevious(node * a);
	private:
		char value;
		node * previous;
};

void node::print() const{
	cout<<value<<' '<<previous<<endl;
}

void node::setValue(char a){
	value = a;	
}

void node::setPrevious(node * a){
	previous = a;	
}

node::node(char a = 0, node *b = NULL){
	value = a;
	previous = b;
}



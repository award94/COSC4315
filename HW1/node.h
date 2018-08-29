using namespace std;

class node{
	
	friend class doubleLinkedList;
	friend class DLLManager;
	
	public:
		node(int a, node *b, node *c);
		void print() const;
		
		void setValue(int a);
		void setNext(node * a);
		void setPrevious(node * a);
	private:
		int value;
		node * next;
		node * previous;
};

void node::print() const{
	cout<<previous<<' '<<value<<' '<<next<<endl;
}

void node::setValue(int a){
	value = a;	
}

void node::setNext(node * a){
	next = a;	
}

void node::setPrevious(node * a){
	previous = a;	
}

node::node(int a = 0, node *b = NULL, node *c = NULL){
	value = a;
	next = b;	
	previous = c;
}



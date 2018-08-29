#include <windows.h>

using namespace std;

void leadZeroPrint(int a, int e);

class doubleLinkedList{
	friend class DLLManager;
	
	public:
		void setHead(node * a);
		void setTail(node * a);
		bool isEmpty();
		bool isFull();
		void insertStart(node * a);
		void insertEnd(node * a);
		void insertHere(node * a, int b);
		void removeStart();
		void trimEmptyHead();
		void print() const;
		int getLength() const;	
		void destroyList();
		
		doubleLinkedList& operator = (const doubleLinkedList& list);
		doubleLinkedList operator + (const doubleLinkedList& list);
		doubleLinkedList operator * (const doubleLinkedList& list);
		
		doubleLinkedList();
		doubleLinkedList(int digitsPerNode);
		doubleLinkedList(string term, int digitsPerNode);
		~doubleLinkedList();
	private:	
		int DPN;
		node * head;
		node * tail;
		int length;
};

//Assigns the head of the list
void doubleLinkedList::setHead(node * a){
	head = a;
}

void doubleLinkedList::setTail(node * a){
	tail = a;	
}

//Checks to see if the head has any value
bool doubleLinkedList::isEmpty(){
	if(head == NULL)
		return true;
	return false;
}

bool doubleLinkedList::isFull(){
	if(head != NULL)
		return true;
	return false;
}

//Inserts a node before the head
void doubleLinkedList::insertStart(node * a){
	length++;
	head->previous = a;
	a->next = head;
	head = a;
}

//Inserts a node at the end of the list
void doubleLinkedList::insertEnd(node * a){
	length++;
	node * temp;
	temp = head;
	while(temp->next != NULL)
		temp = temp->next;
	
	a->previous = temp;
	temp->next = a;
	tail = a;
	
	temp = NULL;
	delete temp;
}

//Inserts a node before the given index
void doubleLinkedList::insertHere(node * a, int b){
	length++;
	node * temp;
	temp = head;
	while(temp->next->value != b)
		temp = temp->next;
	a->next = temp->next;
	a->previous = temp;
	temp->next->next->previous = a;
	temp->next = a;
	
	temp = NULL;
	delete temp;
}

void doubleLinkedList::removeStart(){
	node * temp = head;
	head = temp->next;
	
	temp = NULL;
	delete temp;	
}

void doubleLinkedList::trimEmptyHead(){
	node * temp;
	temp = head;
	if(temp->value == 0){
		head = head->next;
		delete temp;
		length--;	
	}
	
	temp = NULL;
	delete temp;
}

//Prints the whole list
void doubleLinkedList::print() const{
	node * temp;
	temp = head;
	
	while(temp != NULL){
		if(temp != head)
			leadZeroPrint(temp->value, DPN-1);
		cout<<temp->value;
		temp = temp->next;	
	}
	temp = NULL;
	delete temp;
}

void leadZeroPrint(int a, int e){
	int pows = pow(10, e);
	if(a/pows == 0 && e != 0){
		cout<<0;
		leadZeroPrint(a, e-1);
	}
}

int doubleLinkedList::getLength() const{
	return length;	
}

void doubleLinkedList::destroyList(){
	node * temp;
	
	while(head != NULL){
		temp = head;
		head = head->next;
		delete temp;
	}
	
	tail = NULL;
}

doubleLinkedList::doubleLinkedList(){
	DPN = 1;
	length = 1;
	head = NULL;
	tail = NULL;
}

doubleLinkedList::doubleLinkedList(int digitsPerNode){
	DPN = digitsPerNode;
	length = 1;
	head = NULL;
	tail = NULL;
}

doubleLinkedList::doubleLinkedList(string term, int digitsPerNode){
	DPN = digitsPerNode;
	int listLength = (term.length()+(digitsPerNode-1))/digitsPerNode;
	length = 0;
	
	node * temp[listLength];
	for(int i = 0; i < listLength; i++){
		temp[i] = new node;
		length++;
	}
		
	head = temp[0];
	node * temp2 = head;
	
	for(int i = 1; i < listLength; i++){
		temp2->next = temp[i];
		temp2 = temp2->next;
	}
	
	tail = temp2;
	
	for(int i = listLength-1; i >= 0; i--){
		temp2->previous = temp[i];
		if(temp2->previous != NULL)
			temp2 = temp2->previous;
	}
	
	temp2 = head;

	for(int i = 0; i < term.length(); i += digitsPerNode){
		int f = 0;
		for(int e = digitsPerNode-1; e >= 0; e--){
			if(i+f < term.length())
				temp2->value += (term[i+f]-48) * pow(10,e);
			f++;		
		}
		temp2 = temp2->next;
	}
	
	if(term.length() % digitsPerNode != 0){
		int numOfShift = 0;
		numOfShift = listLength * digitsPerNode - term.length();
		int shift = pow(10, numOfShift);
		int shift2 = pow(10, digitsPerNode - numOfShift);
		
		temp2 = tail;
		temp2->value = temp2->value / shift;
		temp2 = temp2->previous;
		
		for(int i = 0; i < listLength-1; i++){
			temp2->next->value += (temp2->value%shift) * shift2;
			temp2->value = temp2->value / shift;
			if(temp2->previous != NULL)
				temp2 = temp2->previous;	
		}
	}
	
	temp2 = NULL;
	delete temp2;
}

doubleLinkedList& doubleLinkedList::operator = (const doubleLinkedList& list){
	node * temp = head;
	
	if(&list != this){
		
		while(head != NULL){
			temp = head;
			head = head->next;
			delete temp;
		}
	
		temp = list.head;
		int listSize = 1;
		
		while(temp->next != NULL){
			listSize++;
			temp = temp->next;
		}
		
		node * returnNodes[listSize];
		
		for(int i = 0; i < listSize; i++)
			returnNodes[i] = new node;	
		
		setHead(returnNodes[0]);
		for(int i = 1; i < listSize; i++)
			insertEnd(returnNodes[i]);
		
		
		temp = list.head;
		node * temp2 = head;
		
		for(int i = 0; i < listSize; i++){
			temp2->value = temp->value;
			
			temp = temp->next;
			temp2 = temp2->next;	
		}
	}	
}

doubleLinkedList doubleLinkedList::operator + (const doubleLinkedList& list){
	doubleLinkedList term3;
	int duration;
	int modShift = pow(10, DPN);
	int bounce = 0;
	
	int term3Length;
	if(length > list.length){
		duration = list.length;
		term3Length = length +1;
	}
	else{
		duration = length;
		term3Length = list.length+1;
	}
	node * t3Nodes[term3Length];
	for(int i = 0; i < term3Length; i++)
		t3Nodes[i] = new node;		
	term3.head = t3Nodes[0];
	for(int i = 1; i < term3Length; i++)
		term3.insertEnd(t3Nodes[i]);
		
	node * temp = tail;
	node * temp2 = list.tail;
	node * temp3 = term3.tail;
	
	for(int i = 0; i < duration; i++){
		temp3->value = temp->value + temp2->value + bounce;
		bounce = bounce / modShift;
		
		if(temp3->value >= pow(10, DPN)){
			bounce = temp3->value / modShift;
			temp3->value = temp3->value % modShift;
		}
		
		temp = temp->previous;
		temp2 = temp2->previous;
		temp3 = temp3->previous;	
	}
	
	if(length > list.length){
		for(int i = duration; i < length; i++){
			temp3->value = temp->value + bounce;
			bounce = bounce / modShift;
			
			if(temp3->value >= pow(10, DPN)){
				bounce = temp3->value / modShift;
				temp3->value = temp3->value % modShift;
			}
		temp = temp->previous;
		temp3 = temp3->previous;
		
		}
	}
	
	else{
		for(int i = duration; i < list.length; i++){
			temp3->value = temp2->value + bounce;
			bounce = bounce / modShift;
			
			if(temp3->value >= pow(10, DPN)){
				bounce = temp3->value / modShift;
				temp3->value = temp3->value % modShift;
			}
		temp2 = temp2->previous;
		temp3 = temp3->previous;
		
		}
	}
	
	temp3->value +=bounce;
	
	return term3;
}

doubleLinkedList doubleLinkedList::operator * (const doubleLinkedList& list){
	int duration, product, sum;
	int modShift = pow(10, DPN);
	int bounce = 0;
	int term3Length = length + list.length;
	
	doubleLinkedList term3;
	node * t3Nodes[term3Length];
	t3Nodes[0] = new node;
	term3.setHead(t3Nodes[0]);
	
	for(int i = 1; i < term3Length; i++){
		t3Nodes[i] = new node;
		term3.insertEnd(t3Nodes[i]);	
	}
	
	node * temp3 = new node;
	node * temp2 = new node;
	node * temp1 = new node;
	
	for(int i = 0; i < length; i++){
		temp1 = tail;
		temp2 = list.tail;
		temp3 = term3.tail;
		
		for(int k = 0; k < i; k++){
			temp1 = temp1->previous;
			temp3 = temp3->previous;
		}
		
		for(int j = 0; j < list.length; j++){
			product = temp1->value * temp2->value + bounce;
			temp3->value = temp3->value + (product%modShift);
			bounce = product/modShift + temp3->value/modShift;
			temp3->value = temp3->value % modShift;
			
			if(temp1->previous != NULL || temp2->previous != NULL || 
				temp3->previous != NULL){
				temp2 = temp2->previous;
				temp3 = temp3->previous;
			}
		}
		temp3->value = bounce;
		bounce = 0;
	}
	
	return term3;
}

doubleLinkedList::~doubleLinkedList(){
	head = NULL;
	tail = NULL;
	delete head;
	delete tail;	
}

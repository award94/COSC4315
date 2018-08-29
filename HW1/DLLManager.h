using namespace std;

class DLLManager{
	friend class doubleLinkedList;
	
	public:
		bool checkForOper(doubleLinkedList a);
		int searchForOper(doubleLinkedList a);
		char getOpChar(doubleLinkedList a, int opIndex);
		
		void createNodes(node *myNodes[], string dummy);
		void createTNodes(node *myNodes[], int opIndex);
		void createDLL(doubleLinkedList & dll, node *myNodes[], int nodeListSize);
		
		void copyIntoTerm1(doubleLinkedList &termDLL,  doubleLinkedList wholeLine, int opIndex);
		void copyIntoTerm2(doubleLinkedList &termDLL,
			 doubleLinkedList wholeLine, int opIndex, int wholeLength);
			 
		int getT3Length(int t1, int t2, char opChar);
		void computeTerm3(doubleLinkedList term1, doubleLinkedList term2,
			 doubleLinkedList & term3, char opChar, int term3Length);
		
		void addition(doubleLinkedList term1, doubleLinkedList term2, 
			doubleLinkedList & term3, int term3Length);
		void multiply(doubleLinkedList term1, doubleLinkedList term2, 
			doubleLinkedList & term3, int term3Length);
			
		void trimZeros(doubleLinkedList & term3);
		
		DLLManager();
	private:
};

bool DLLManager::checkForOper(doubleLinkedList a){
	node * temp;
	temp = a.head;
	
	
	while(temp->next != NULL){
		if(temp->value == 42 || temp->value == 43)
			return true;
		temp = temp->next;	
	}
	
	return false;
}

int DLLManager::searchForOper(doubleLinkedList a){
	node * temp;
	temp = a.head;
	int count = 0;
	
	while(temp->next != NULL){
		if(temp->value == 42 || temp->value ==43)
			return count;
		count++;
		temp = temp->next;	
	}
	
	return 0;	
}

char DLLManager::getOpChar(doubleLinkedList a, int opIndex){
	node * temp;
	temp = a.head;
	
	for(int i = 0; i < opIndex; i++)
		temp = temp->next;
;
	return temp->value;
			
}

void DLLManager::createNodes(node *myNodes[], string dummy){	
	for(int i = 0; i < dummy.length(); i++){
		myNodes[i] = new node;
		myNodes[i]->setValue(dummy[i]);
	}
}

void DLLManager::createTNodes(node *myNodes[], int opIndex){
	for(int i = 0; i < opIndex; i++)
		myNodes[i] = new node;
}

void DLLManager::createDLL(doubleLinkedList & dll, node *myNodes[], int nodeListSize){
	dll.setHead(myNodes[0]);
	dll.setTail(myNodes[nodeListSize-1]);
		for(int i = 1; i <nodeListSize; i++)
			dll.insertEnd(myNodes[i]);
}

void DLLManager::copyIntoTerm1(doubleLinkedList & termDLL, doubleLinkedList wholeLine, int opIndex){
	node * tempWhole = wholeLine.head;
	node * tempTerm = termDLL.head;
	
	for(int i = 0; i < opIndex; i++){
		if(tempWhole->value > 57 || tempWhole->value < 48)
			return;
		tempTerm->value = tempWhole->value - 48;
		tempWhole = tempWhole->next;
		tempTerm = tempTerm->next;
	}
}

void DLLManager::copyIntoTerm2(doubleLinkedList &termDLL, 
	doubleLinkedList wholeLine, int opIndex, int wholeLength){
	node * tempWhole = wholeLine.head;
	node * tempTerm = termDLL.head;
	
	for(int i = 0; i < opIndex + 1; i++)
		tempWhole = tempWhole->next;
	
	for(int i = 0; i < (wholeLength - opIndex - 1); i++){
		if(tempWhole->value > 57 || tempWhole->value < 48)
			return;
		tempTerm->value = tempWhole->value - 48;
		tempWhole = tempWhole->next;
		tempTerm = tempTerm->next;
	}
}

int DLLManager::getT3Length(int t1, int t2, char opChar){
	if(opChar == 42){
		return t1 + t2;
	}
	
	if(opChar == 43)
		if(t1 > t2){
			return t1 + 1;
		}
		else
			return t2 + 1;
	cout<<"Invalid opChar"<<endl;
	return 100;
}

void DLLManager::computeTerm3(doubleLinkedList term1, doubleLinkedList term2, 
		doubleLinkedList & term3, char opChar, int term3Length){
			
	if(opChar == '+'){	
		addition(term1, term2, term3, term3Length);
	}
	
	if(opChar == '*'){
		multiply(term1, term2, term3, term3Length);
	}
}

void DLLManager::addition(doubleLinkedList term1, doubleLinkedList term2, doubleLinkedList & term3, int term3Length){
	int duration, sum, bounce = 0;
	
	node * temp1 = term1.tail;
	node * temp2 = term2.tail;
	node * temp3 = term3.tail;
	
	if(term1.getLength() < term2.getLength())
		duration = term1.getLength();
	else
		duration = term2.getLength();
	
	for(int i = 0; i < duration; i++){
			sum = temp2->value + temp1->value+bounce;
			bounce = sum/10;
			temp3->value += sum % 10;
			
			if(temp1->previous != NULL || temp2->previous != NULL || 
				temp3->previous != NULL){
				temp1 = temp1->previous;
				temp2 = temp2->previous;
				temp3 = temp3->previous;
			}
	}
		
	if(term1.getLength() > term2.getLength()){
		for(int i = duration; i < term1.getLength(); i++){
			sum = temp1->value + bounce;
			temp3->value = sum % 10;
			bounce = sum/10;
			
			temp3 = temp3->previous;
			temp1 = temp1->previous;
		}
	}
	else{
		for(int i = duration; i < term2.getLength(); i++){
			sum = temp2->value + bounce;
			temp3->value = sum % 10;
			bounce = sum/10;
			
			temp3 = temp3->previous;
			temp2 = temp2->previous;
		}
	}
	temp3->value = bounce;
}

void DLLManager::multiply(doubleLinkedList term1, doubleLinkedList term2, 
	doubleLinkedList & term3, int term3Length){	
	int duration, product, sum;
	int bounce = 0;
	int term1Length = term1.getLength();
	int term2Length = term2.getLength();
	node * temp3 = new node;
	
	for(int i = 0; i < term1Length; i++){
		node * temp1 = term1.tail;
		node * temp2 = term2.tail;
		temp3 = term3.tail;
		
		for(int k = 0; k < i; k++){
			temp1 = temp1->previous;
			temp3 = temp3->previous;
		}
		
		for(int j = 0; j < term2Length; j++){
			product = temp1->value * temp2->value + bounce;
			temp3->value = (temp3->value + (product%10));
			bounce = product/10 + temp3->value / 10;
			temp3->value = temp3->value % 10;
			
			
			
			if(temp1->previous != NULL || temp2->previous != NULL || 
				temp3->previous != NULL){
				temp2 = temp2->previous;
				temp3 = temp3->previous;
			}
		}
		temp3->value = bounce;
		bounce = 0;
	}
}
	
void DLLManager::trimZeros(doubleLinkedList & term3){
	if(term3.head->next != NULL){
		if(term3.head->value == 0)
			term3.removeStart();	
	}
}
	
DLLManager::DLLManager(){	
}

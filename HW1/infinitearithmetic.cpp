#include <iostream>
#include <fstream>
#include "argumentManager.h"
#include <string>
#include <cctype>
#include "node.h"
#include "doubleLinkedList.h"
#include "DLLManager.h"

using namespace std;

void checkIfEmpty(string & dummy);
void trimString(string & dummy);
void printResults(doubleLinkedList term1, doubleLinkedList term2,
	 doubleLinkedList term3, char opChar);

int main(int argc, char *argv[]){
	
		if (argc < 2) {
		    cerr << "Usage: infinitearithmetic \"filename=xyz.txt;digitsPerNode=<number>\"\n";
		}
				
		ArgumentManager am(argc, argv);
  		string filename = am.get("input");
  		string digitsPerNode = (am.get("digitsPerNode"));
		ifstream inFile(filename.c_str());		
		
		string dummy;

		while(inFile && inFile.peek() != -1){
			getline(inFile, dummy);
			checkIfEmpty(dummy);
			trimString(dummy);
			
			doubleLinkedList wholeLine;
			doubleLinkedList term1;
			doubleLinkedList term2;
			doubleLinkedList term3;
			char opChar;
			int opIndex;
			DLLManager DLLMan;
			
			node * myNodes[dummy.length()];
			
			DLLMan.createNodes(myNodes, dummy);
			DLLMan.createDLL(wholeLine, myNodes, dummy.length());
			
			if(DLLMan.checkForOper(wholeLine)){
				opIndex = DLLMan.searchForOper(wholeLine);
				opChar = DLLMan.getOpChar(wholeLine, opIndex);
						
				node*T1Nodes[opIndex];
				node*T2Nodes[dummy.length() - opIndex];
				
				DLLMan.createTNodes(T1Nodes, opIndex);
				DLLMan.createTNodes(T2Nodes, (dummy.length() - opIndex - 1));
				DLLMan.createDLL(term1, T1Nodes, opIndex);
				DLLMan.createDLL(term2, T2Nodes, (dummy.length() - opIndex - 1));
				DLLMan.copyIntoTerm1(term1, wholeLine, opIndex);
				DLLMan.copyIntoTerm2(term2, wholeLine, opIndex, dummy.length());
						
				int T3Length = DLLMan.getT3Length(opIndex, 
					dummy.length() - opIndex - 1, opChar);
				node*T3Nodes[T3Length];
				
				DLLMan.createTNodes(T3Nodes, T3Length);
				DLLMan.createDLL(term3, T3Nodes, T3Length);		
				DLLMan.computeTerm3(term1, term2, term3, opChar, T3Length);
				DLLMan.trimZeros(term3);
				printResults(term1, term2, term3, opChar);
			}
		}
		
		return 0;
}

void checkIfEmpty(string & dummy){
	for(int i = 0; i < dummy.length(); i++){
		if(isdigit(dummy[i]))
			return;
	}
	dummy.append("123");
}

void trimString(string & dummy){
	while((isdigit(dummy[0]) == false)){
		dummy.erase(0,1);	
	}
	while((isdigit(dummy[dummy.length()-1]) == false)){
		dummy.erase((dummy.length()-1),1);	
	}
}

void printResults(doubleLinkedList term1, doubleLinkedList term2,
	 doubleLinkedList term3, char opChar){
	 term1.print();
	cout<<opChar;
	term2.print();
	cout<<'=';
	term3.print();	
	cout<<endl;
}

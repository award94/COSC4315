#include <iostream>
#include <fstream>
#include <math.h>
#include "argumentManager.h"
#include <string>
#include <cctype>
#include "node.h"
#include "doubleLinkedList.h"

using namespace std;

bool checkIfEmpty(string & dummy);
void trimString(string & dummy);
void chopLine(string line, string & num1, string & num2, string & op);

int main(int argc, char *argv[]){
		if (argc < 2) {
		    cerr << "Usage: infinitearithmetic \"input=xyz.txt;digitsPerNode=<number>\"\n";
		}
				
		ArgumentManager am(argc, argv);
  		string filename = am.get("input");
		int digitsPerNode = stoi(am.get("digitsPerNode"));
		ifstream inFile(filename.c_str());		
		
		string line;
		
		while(getline(inFile, line)){			
			if(checkIfEmpty(line)){
				trimString(line);
				
				string num1, num2, op;
				
				chopLine(line, num1, num2, op);
				doubleLinkedList term1(num1, digitsPerNode);
				doubleLinkedList term2(num2, digitsPerNode);
				
				doubleLinkedList term3(digitsPerNode);
				if(op == "+")
					term3 = term1 + term2;
				
				if(op == "*")
					term3 = term1 * term2;
				
				term3.trimEmptyHead();
				
				term1.print();
				cout<<op;
				term2.print();
				cout<<"=";
				term3.print();
				cout<<endl;	
			}
		}
		return 0;
}

bool checkIfEmpty(string & dummy){
	for(int i = 0; i < dummy.length(); i++){
		if(isdigit(dummy[i]))
			return true;
	}
	return false;
}

void trimString(string & dummy){
	while((isdigit(dummy[0]) == false)){
		dummy.erase(0,1);	
	}
	while((isdigit(dummy[dummy.length()-1]) == false)){
		dummy.erase((dummy.length()-1),1);	
	}
}

void chopLine(string line, string & num1, string & num2, string & op){
	int opIndex;
	
	for(int i = 0; i < line.length(); i++){
		if(line[i] == 42 || line[i] == 43){
			op = line[i];
			opIndex = i;
		}
	}
	num1.append(line, 0, opIndex);
	num2.append(line, opIndex+1, line.length());
}

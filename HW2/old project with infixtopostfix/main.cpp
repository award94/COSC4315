#include <iostream>
#include <string>
#include <fstream>
#include "node.h"
#include "stack.h"
#include "infixToPostfix.h"

using namespace std;

int main(int argc, char * argv[]){
	ifstream inFile;
	inFile.open("infixData.txt");
	
	string myString;
	
	while(getline(inFile, myString)){
		infixToPostfix myInToPost(myString);
		myInToPost.showInfix();
		cout<<endl;
		myInToPost.convertToPostfix();
		myInToPost.showPostfix();
		cout<<endl;
	}
		
	inFile.close();
	return 0;	
}

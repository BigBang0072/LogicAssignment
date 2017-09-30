#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int mapRankToOperator(char operation);
void initializeBuffer(int lengthBuffer,char Buffer[]);
void infixToPostfix(int lengthInfix,char infix[],int* lengthPostStack,char postStack[]);

int main(){
	int lengthInfix=10,lengthPostStack;
	char infix[10]={'(','p','*','q',')'};
	char postStack[lengthInfix];
	infixToPostfix(lengthInfix,infix,&lengthPostStack,postStack);
	return 0;
}

void infixToPostfix(int lengthInfix,char infix[],int* lengthPostStack,char postStack[]){
	/*

	*/
	//Initializing the local Buffer for our operation.
	char workStack[lengthInfix];
	initializeBuffer(lengthInfix,workStack);


	//Traversing the infix and converting it to the postfix.
	int wtos=-1,postTos=-1;
	int previousRank=0,currentRank=0;
	for(int i=0;i<lengthInfix;i++){
		char data=infix[i];//making a local copy of the current character in Infix.

		//If out character is a operation.
		if(data=='~' || data=='*' || data=='+' || data=='>'){
			currentRank=mapRankToOperator(data);
			if(currentRank>previousRank){
				wtos++;
				workStack[wtos]=data;
				previousRank=currentRank;
			}
			else{
				do{
					postTos++;
					postStack[postTos]=data;
					wtos--;
					char stackData=workStack[wtos];
					previousRank=mapRankToOperator(stackData);
				}while(currentRank<=previousRank);
				wtos++;
				workStack[wtos]=data;
				previousRank=currentRank;
			}

		}
		//If we encounter a parnthesis which referes to a specialized subtree in Binary tree representation.
		else if(data=='('){
			wtos++;
			workStack[wtos]=data;
		}
		else if(data==')'){
			char stackData=workStack[wtos];
			while(stackData!='('){
				postTos++;
				postStack[postTos]=stackData;
				wtos--;
				stackData=workStack[wtos];
			}
			wtos--;
		}

		else{
			postTos++;
			postStack[postTos]=data;
		}
	}
	while(wtos!=-1){
		char data=workStack[wtos];
		wtos--;
		postTos++;
		postStack[postTos]=data;
	}

	*lengthPostStack=postTos+1;
}

void initializeBuffer(int lengthBuffer,char Buffer[]){
	for(int i=0;i<lengthBuffer;i++){
		Buffer[i]=0;//Initializing all the initial state ot Ascii value 0.
	}
}

int mapRankToOperator(char operation){

	// We are giving rank in the magnitude of number.
	// 4:Best and 1:Last
	if(operation =='~'){
		return 4;
	}
	else if(operation =='*'){
		return 3;
	}
	else if(operation =='+'){
		return 2;
	}
	else if(operation =='>'){
		return 1;
	}
	return -1;//to take care of the ( which is pushed inside the work buffer.
	// The popping of work Stack of operator will only go until "(" cuz it will be in less rank
	//than any of the current operator.
}
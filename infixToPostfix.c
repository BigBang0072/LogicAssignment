#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int mapRankToOperator(char operation);
void initializeBuffer(int lengthBuffer,char Buffer[]);
void infixToPostfix(int lengthInfix,char infix[],int* lengthPostStack,char postStack[]);

int main(){
	int lengthInfix=7,lengthPostStack;
	char infix[7]={'a','+','(','b','*','c',')'};
	char postStack[lengthInfix];
	initializeBuffer(lengthInfix,postStack);
	infixToPostfix(lengthInfix,infix,&lengthPostStack,postStack);
	for(int i=0;i<lengthInfix;i++){
		printf("%c ",postStack[i]);
	}
	printf("\n%d\n",lengthPostStack);
	return 0;
}

void infixToPostfix(int lengthInfix,char infix[],int* lengthPostStack,char postStack[]){
	/*  INPUT:1.Number of Character in Infix array.
			  2.Infix character Array.
			  3.Pointer to length of Postfix Form (for iterating over in next task.)
			  4.To get the Postfix form in form of Character Array.

	    OUTPUT: None.


	*/

	//WORKSPACE CREATION
	//Initializing the local Buffer for our operation.
	//This will act as storing the operators and parenthesis coming in form Infix fromat.
	int wtos=-1; // This is a top of Stack counter variable.
	char workStack[lengthInfix];
	initializeBuffer(lengthInfix,workStack);


	//Traversing the infix and converting it to the postfix.
	int postTos=-1; //This is top of Stack variable for working on Postfix array.
	int previousRank=0,currentRank=0;
	for(int i=0;i<lengthInfix;i++){
		char data=infix[i];//making a local copy of the current character in Infix.

		//If out character is a operation.
		if(data=='~' || data=='*' || data=='+' || data=='>'){
			currentRank=mapRankToOperator(data);
			//If the rank of scanned operator in greater than the last operator scanned.
			if(currentRank>previousRank){
				wtos++;
				workStack[wtos]=data;
				previousRank=currentRank;
			}
			//If the current scannd operator is of less rank than last one
			else{
				//put the operator to the Postfix Stack until rank of the 
				//operator in workStack becomes less than scanned rank.
				do{
					postTos++;
					postStack[postTos]=data;
					wtos--;
					char stackData=workStack[wtos];
					previousRank=mapRankToOperator(stackData);
				}while(currentRank<=previousRank);
				//Now finally putting the scanned operator in workStack.
				wtos++;
				workStack[wtos]=data;
				previousRank=currentRank;
			}

		}



		//If we encounter a parnthesis which referes to a specialized subtree in Binary tree representation.
		else if(data=='('){
			//The opening parenthesis represent private grouping of operation.
			wtos++;
			workStack[wtos]=data;
		}
		else if(data==')'){
			//So until we again encounter the close we have to do the conversion
			//as if doing it for independent problem.
			char stackData=workStack[wtos];
			//Finally as subproblem ends we put them in Postfix Stack.
			while(stackData!='('){
				postTos++;
				postStack[postTos]=stackData;
				wtos--;
				stackData=workStack[wtos];
			}
			wtos--;
		}




		else{
			//If operands are encountered, then directly push them to the Postfix Stack.
			postTos++;
			postStack[postTos]=data;
		}
	}



	//Now putting the rest of left operations present in the workStack to
	// the Postfix Stack.
	while(wtos!=-1){
		char data=workStack[wtos];
		wtos--;
		postTos++;
		postStack[postTos]=data;
	}

	//Updating the length of the PostOrder stack for the furthur 
	// iterating in the array in next task.
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
	return -1;//to take care of the "("" which is pushed inside the work buffer.
	// The popping of work Stack of operator will only go until "(" cuz it will be in less rank
	//than any of the current operator.
}
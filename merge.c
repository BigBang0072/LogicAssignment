#include <stdio.h>
#include <stdlib.h>

//NODE Declaration for building the Parse Tree.
struct node{
	struct node* leftPointer;
	struct node* rightPointer;
	char data;
};

//MAIN FUNCTION Declaration.
void infixToPostfix(int lengthInfix,char infix[],int* lengthPostStack,char postStack[]);
struct node* giveParseTree(int lengthStack,char postOrderStack[]);
void printInfix(struct node* node);

//HELPER FUNCTION Declaration
void initializeBuffer(int lengthBuffer,char Buffer[]);
int mapRankToOperator(char operation);
void printPostfix(int lengthPostStack,char postStack[]);
void initializeStack(int lengthStack,struct node* stack[]);
struct node* giveNewNode(char data,struct node* leftPointer,struct node* rightPointer);



//HANDLER
int main(){
	//HAVE to take command line taking implementation here. (CHANGE)
	int MAX_SIZE=50;
	char infix[MAX_SIZE];
	scanf("%s",infix);
	int lengthInfix=0;

	int i = 0;
	while(infix[i] != '\0'){
		lengthInfix++;
		i++;
	}

	// printf("%d %s\n",lengthInfix,infix);

	//Initializing the Postfix Array.
	int lengthPostStack;
	char postStack[lengthInfix]; // Postfix Array.
	initializeBuffer(lengthInfix,postStack);

	// 1. Calling the First Main function to convert the Infix to Postfix.

	printf("\nConverting Infix to Postfix expression...\n");
	infixToPostfix(lengthInfix,infix,&lengthPostStack,postStack);
	printf("Converted to Postfix\n");
	printPostfix(lengthPostStack,postStack);

	// 2. Building the Parse tree from the Postfix format.

	printf("Creating Parse tree from Postfix expression...\n");
	struct node* head=giveParseTree(lengthPostStack,postStack);
	printf("Parse tree created.\n\n");

	// 3. Printing the Parse tree to get back Infix Format.(fully Paranthesized)
	
	printf("Traversing the tree...\n");
	printf("Printing the infix expression...\n");
	printf("Infix :");

	printInfix(head);
	printf("\nPrint Complete\n");

	return 0;
}



//TASK Implementation.

//Task 1

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
		//printf("%d %c\n",i,data);
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
					postStack[postTos]=workStack[wtos];
					wtos--;
					//In case we reach the end of workStack.
					if(wtos==-1){
						break;
					}
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
			previousRank=mapRankToOperator(data);
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
			stackData=workStack[wtos];
			previousRank=mapRankToOperator(stackData);
		}




		else{
			//If operands are encountered, then directly push them to the Postfix Stack.
			postTos++;
			postStack[postTos]=data;
		}
		//printf("wtos :%d %d\n",wtos,previousRank);
		//printf("%s\n\n",workStack);
	}

	//printf("FIRST PASS\n");

	//Now putting the rest of left operations present in the workStack to
	// the Postfix Stack.
	while(wtos!=-1){
		char data=workStack[wtos];
		wtos--;
		postTos++;
		//printf("%d %c\n",wtos,data);
		postStack[postTos]=data;
	}

	//Updating the length of the PostOrder stack for the furthur 
	// iterating in the array in next task.
	*lengthPostStack=postTos+1;
}

//Task 2
struct node* giveParseTree(int lengthStack,char postOrderStack[]){
	/*
		INPUT : 1.The Current Length of stack (actual length counting from 1).
				2.The postOrder of the infix form (received from Task1).

		OUTPUT :1."head" pointer of the Binary Tree.
	*/

	//Creating our temporary Stack for making parse tree.
	struct node* nodeStack[lengthStack];
	initializeStack(lengthStack,nodeStack);

	//Now Traverse through the postfix order got from the First Part.

	int tos=-1;	//TopOfStack counter
	for(int i=0;i<lengthStack;i++){
		char data=postOrderStack[i];
		if(data=='~'){
			//We just need one element for Negation operation.
			//Thus making a subTree with negation as parent and tos as the right child.
			//The left element is NULL to fecilitate In-order traversal.
			struct node* newNode=giveNewNode(data,NULL,nodeStack[tos]);
			nodeStack[tos]=newNode;
		}
		else if(data=='+' || data=='*' || data=='>'){
			//We need two subgraph to add these operation.
			struct node* newNode=giveNewNode(data,nodeStack[tos-1],nodeStack[tos]);
			tos--;	//As two elements are used and get one final node we need to lower tos.
			nodeStack[tos]=newNode;
		}
		else{
			//As this a proposition we need to add them to stack.
			tos++;
			struct node* newNode=giveNewNode(data,NULL,NULL);//A proposition cant have children hence NULL.
			nodeStack[tos]=newNode;
		}
	}

	

	// After the merging of all the proposition with the approriate operator
	// we will be left with only one node that is the require "BINARY-Parse Tree"
	return nodeStack[0]; //hence returning the final left tree pointer.
}


//Task 3
void printInfix(struct node* node){

	if(node == NULL){
		return;
	}

	if (node->leftPointer != NULL)
	{
		printf("(");
	}
	printInfix(node->leftPointer);

	if (node->data == '~')
	{
		printf("(");
	}
	printf("%c", node->data);
	

	printInfix(node->rightPointer);
	if (node->rightPointer != NULL)
	{
		printf(")");
	}
}


//HELPER FUNCTION Implementation.
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
void printPostfix(int lengthPostStack,char postStack[]){
	
	printf("Printing Postfix expression...\n");	
	printf("Postfix : ");
	for(int i=0;i<lengthPostStack;i++){
		printf("%c",postStack[i]);
	}
	printf("\n\n");
}
void initializeStack(int lengthStack,struct node* stack[]){
	//Initializing any stack(which is form of array of node's pointer)
	for(int i=0;i<lengthStack;i++){
		stack[i]=NULL;//Pointing the stack element to NULL.
	}
}
struct node* giveNewNode(char data,struct node* leftPointer,struct node* rightPointer){
	/*
		INPUT : 1.Data of the current node.
				2.The pointer to the left child
				3.The pointer to the right child

		OUTPUT: 1.The pointer reference of the Parent to be added.
	*/

	//Creating a reference of the new node to be added.
	struct node* newNode=(struct node*)malloc(sizeof(struct node));

	// Filling up the new node with necessary data.
	newNode->leftPointer=leftPointer;
	newNode->rightPointer=rightPointer;
	newNode->data=data;

	//Returning the reference to the newNode to be added accordingly.
	return newNode;
}

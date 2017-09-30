#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct node{
	struct node* leftPointer;
	struct node* rightPointer;
	char data;
};


void printInfix(struct node* node);
void initializeStack(int lengthStack,struct node* stack[]);
struct node* giveParseTree(int lengthStack,char postOrderStack[]);
struct node* giveNewNode(char data,struct node* leftPointer,struct node* rightPointer);

int main(){
	char test[10]={'5','1','2','+','4','*','+','3','+'};
	struct node* head=giveParseTree(9,test);
	printInfix(head);
	printf("\n");
	return 0;
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

void initializeStack(int lengthStack,struct node* stack[]){
	//Initializing any stack(which is form of array of node's pointer)
	for(int i=0;i<lengthStack;i++){
		stack[i]=NULL;//Pointing the stack element to NULL.
	}
}

void printInfix(struct node* node){

	if(node == NULL){
		return;
	}

	if (node->leftPointer != NULL)
	{
		printf("( ");
	}
	printInfix(node->leftPointer);

	printf("%c ", node->data);
	if (node->data == '~')
	{
		printf(" (");
	}

	printInfix(node->rightPointer);
	if (node->rightPointer)
	{
		printf(") ");
	}
}
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct node{
	struct node* leftPointer;
	struct node* rightPointer;
	char data;
};

void initializeStack(int lengthStack,struct node* stack[]);
struct node* giveParseTree(int lengthStack,char postOrderStack[]);
struct node* giveNewNode(char data,struct node* leftPointer,struct node* rightPointer);

int main(){
	char test[10]={'p','q','+'};
	struct node* head=giveParseTree(3,test);

	return 0;
}

struct node* giveNewNode(char data,struct node* leftPointer,struct node* rightPointer){
	/*
		INPUT : 1.Data of the current node.
				2.The pointer to the left child
				3.THe pointer to the right child

		OUTPUT: 1.The pointer reference of the Parent to be added.
	*/

	//Creating a reference of the new node to be added.
	struct node* newNode=(struct node*)malloc(sizeof(struct node));

	// Filling up the new node with necessary data.
	newNode->leftPointer=leftPointer;
	newNode->rightPointer=rightPointer;
	newNode->data=data;

	//Returning the reference to the newNode.
	return newNode;
}

struct node* giveParseTree(int lengthStack,char postOrderStack[]){

	//Creating our temporary Stack for making parse tree.
	struct node* nodeStack[lengthStack];
	initializeStack(lengthStack,nodeStack);

	//Now Traverse through the postfix order got from the First Part.
	int tos=-1;
	for(int i=0;i<lengthStack;i++){
		char data=postOrderStack[i];
		if(data=='~'){
			struct node* newNode=giveNewNode(data,NULL,nodeStack[tos]);
			nodeStack[tos]=newNode;
		}
		else if(data=='+' || data=='*' || data=='>'){
			struct node* newNode=giveNewNode(data,nodeStack[tos-1],nodeStack[tos]);
			tos--;
			nodeStack[tos]=newNode;
		}
		else{
			tos++;
			struct node* newNode=giveNewNode(data,NULL,NULL);
			nodeStack[i]=newNode;
		}
	}
	return nodeStack[0];
}

void initializeStack(int lengthStack,struct node* stack[]){
	//Initializing any stack(which is form of array of nodes pointer)
	for(int i=0;i<lengthStack;i++){
		stack[i]=NULL;//Pointing the stack element to NULL.
	}
}
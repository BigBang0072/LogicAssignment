#include <stdio.h>

struct node
{
	node* leftPointer;
	node* rightPointer;
	char data;
};

int main(){

	return 0;
}


void printInfix(node* node){

	if(node == NULL){
		return;
	}

	if (node->leftPointer != NULL)
	{
		printf("(");
	}
	printInfix(node->leftPointer);
]
	printf("%c ", node->data);
	if (node->data == '~')
	{
		printf("(");
	}

	printInfix(node->rightPointer);
	if (node->rightPointer)
	{
		printf(")");
	}
	
}
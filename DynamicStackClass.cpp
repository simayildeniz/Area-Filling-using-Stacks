# include <iostream>
# include "DynamicStackClass.h"

;using namespace std;

/* Begin: code taken from DyamicStringClass.cpp and updated*/
DynamicStack::DynamicStack() // CONSTRUCTOR
{
	top = NULL;
}

void DynamicStack::push(int xCoord, int yCoord)
{
	StackNode *  newNode;

	newNode = new StackNode;
	newNode->xCoord = xCoord;
	newNode->yCoord = yCoord;

	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else
	{
		newNode->next = top;
		top = newNode;
	}
}

void DynamicStack::pop(int & xCoord, int & yCoord)
{
	StackNode *temp;

	if (isEmpty())
	{
		//cout << "Stack is empty!" << endl;
	}
	else
	{
		xCoord = top->xCoord;
		yCoord = top->yCoord;
		temp = top->next;
		delete top;
		top = temp;
	}
}

bool DynamicStack::isEmpty()
{
	bool status;

	if (top == NULL)
	{
		status = true;
	}
	else
	{
		status = false;
	}
	return status;
}

DynamicStack::~DynamicStack()
{
	StackNode * temp;
	while (top != NULL)
	{
		temp = top;
		top = top->next;

		delete temp;
	}
}
/* End: code taken from DyamicStringClass.cpp and updated*/ 
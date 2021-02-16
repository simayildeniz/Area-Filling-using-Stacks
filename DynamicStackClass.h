#ifndef DYNAMICSTACKCLASS_H
#define DYNAMICSTACKCLASS_H

using namespace std;

/* Begin: code taken from DyamicStringClass.cpp and updated*/
struct StackNode
{
	//char value;
	int xCoord;
	int yCoord;
	StackNode * next;
};

class DynamicStack
{
	private: 
		StackNode * top;
		StackNode * GetTopPointer(DynamicStack myStack);

	public:
		DynamicStack();
		void push(int xCoord, int yCoord);
		void pop(int & xCoord, int & yCoord);
		bool isEmpty();
		~DynamicStack();
}
/* End: code taken from DyamicStringClass.cpp and updated*/ 
#endif

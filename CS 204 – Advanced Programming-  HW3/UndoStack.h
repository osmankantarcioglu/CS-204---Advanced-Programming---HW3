#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include <string>
using namespace std;


struct StackNode
{
	char operation;
	string employee_name;
	string project_name;
	int project_priority;
	StackNode* next;
};

class UndoStack
{
private:
	StackNode* top;

public:
	UndoStack(); //Creates an empty stack.
	void push(char operation, string employee_name, string project_name, int project_priority); //Push node to the top of the stack
	void pop(char & operation, string & employee_name, string & project_name, int & project_priority); //pops the top node of the stack
	bool isEmpty(); //check whether stack is empty
	void clear(); //deallocating the dynamically - allocated memory of the stack
};

#endif
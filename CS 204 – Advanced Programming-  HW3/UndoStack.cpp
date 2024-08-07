#include<iostream>
#include"UndoStack.h"
using namespace std;

//This function is used to creates an empty stack.
UndoStack::UndoStack() 
{
	top = NULL;
}

//This function is used push node to the top of the stack
void UndoStack::push(char operation, string employee_name, string project_name, int project_priority)
{
	StackNode* newNode = new StackNode;
	newNode->employee_name = employee_name;
	newNode->operation = operation;
	newNode->project_name = project_name;
	newNode->project_priority = project_priority;
	newNode->next = top;
	top = newNode;
}
//This function is used pops the top node of the stack
void UndoStack::pop(char& operation, string& employee_name, string& project_name, int& project_priority)
{
	operation = top->operation;
	employee_name = top->employee_name;
	project_name = top->project_name;
	project_priority = top->project_priority;

	StackNode* temp = top;
	top = top->next;
	delete temp;
}
//This function is used to check whether stack is empty
bool UndoStack::isEmpty()
{
	if (top == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//This function is used to deallocating the dynamically - allocated memory of the stack
void UndoStack::clear()
{
	while (top != NULL)
	{
		StackNode* temp = top;
		top = top->next;
		delete temp;
	}
}
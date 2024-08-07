#include<iostream>
#include"EmployeeProject2DLL.h"
using namespace std;
/******************************************************************************
Sabanci  University CS204 Advanced Programming Homework3 – Employee-Project Management System using a Hybrid Data Structure
Coded by: Osman Kantarcioglu    -   30891   - Section:B2
Date:20 March 2024
******************************************************************************/

/******************************************************************************
This is give in homework file.
This function is constructer function that creat an empty object with no employee
******************************************************************************/
EmployeeProject2DLL::EmployeeProject2DLL()
{
	head = NULL;
}
/******************************************************************************
This is give in homework file.
This function checks wheterher employee is assigned to the project
******************************************************************************/
bool EmployeeProject2DLL::isEmployeeAssignedToProject(string employee_name, string project_name)
{
	EmployeeNode* EmployeeNodeHead = head;
	while (EmployeeNodeHead != NULL)					//Function iterate linked list and search matching project_name and employee_name 
	{
		if (EmployeeNodeHead->employee_name == employee_name)
		{
			ProjectNode* ProjectNodeHead = EmployeeNodeHead->head;
			while (ProjectNodeHead != NULL)
			{
				if (ProjectNodeHead->project_name == project_name)
				{
					return true;
				}
				ProjectNodeHead = ProjectNodeHead->next;
			}
		}
		EmployeeNodeHead = EmployeeNodeHead->down;
	}
	return false;
}
/******************************************************************************
This is extra function that is not given in homework file.
This function is used to check whether there is a project exists with same priority
******************************************************************************/
bool EmployeeProject2DLL::anotherProjectWithSamePriority(string employee_name, string project_name, int project_priority)
{
	EmployeeNode* EmployeeNodeHead = head;
	while (EmployeeNodeHead != NULL)
	{
		if (EmployeeNodeHead->employee_name == employee_name)
		{
			ProjectNode* ProjectNodeHead = EmployeeNodeHead->head;
			while (ProjectNodeHead != NULL)	//Function iterates over linked list
			{
				if (ProjectNodeHead->project_priority == project_priority && project_name != ProjectNodeHead->project_name)
				{
					return true;		//return true when there is an project with same priority but different project name
				}
				ProjectNodeHead = ProjectNodeHead->next;
			}
		}
		EmployeeNodeHead = EmployeeNodeHead->down;
	}
	return false;
}
/******************************************************************************
This is another extra function that is not given in homework file.
This function is used to check whether given project name has already same project priority
******************************************************************************/
bool EmployeeProject2DLL::alreadySamePriority(string employee_name, string project_name, int project_priority) {
	EmployeeNode* EmployeeNodeHead = head;
	while (EmployeeNodeHead != NULL)
	{
		if (EmployeeNodeHead->employee_name == employee_name)
		{
			ProjectNode* ProjectNodeHead = EmployeeNodeHead->head;
			while (ProjectNodeHead != NULL)//Function iterates over linked list
			{
				if (project_name == ProjectNodeHead->project_name && ProjectNodeHead->project_priority == project_priority)
				{
					return true;		//return true when there is an project with same priority and same project name
				}
				ProjectNodeHead = ProjectNodeHead->next;
			}
		}
		EmployeeNodeHead = EmployeeNodeHead->down;
	}
	return false;
}
/******************************************************************************
This is another extra function that is not given in homework file.
This function is used to sort projects of the employees
******************************************************************************/
void EmployeeProject2DLL::reorderList(ProjectNode*& ProjectNodeHead) //ascending order
{
	//first order numerically ascending
	for (ProjectNode* currentPtr = ProjectNodeHead; currentPtr->next != NULL; currentPtr = currentPtr->next)
	{
		for (ProjectNode* tempPtr = currentPtr->next; tempPtr != NULL; tempPtr = tempPtr->next)
		{
			if (currentPtr->project_priority > tempPtr->project_priority)//When there are projects that they are not sorted
			{
				//Changes contents of the linked list instead of changing nodes. 
				string temp_project_name = tempPtr->project_name;
				int temp_project_priority = tempPtr->project_priority;
				tempPtr->project_name = currentPtr->project_name;
				tempPtr->project_priority = currentPtr->project_priority;
				currentPtr->project_name = temp_project_name;
				currentPtr->project_priority = temp_project_priority;
			}
		}
	}
}
/******************************************************************************
This is give in homework file.
This function is used to sort projects of the employees
******************************************************************************/
bool EmployeeProject2DLL::updateProjectPriority(string employee_name, string project_name, int& project_priority)
{
	if (anotherProjectWithSamePriority(employee_name, project_name, project_priority))
	{
		cout << "The project priority has not been updated because there is another project with the same priority." << endl;
		return false; // return false when another project with same priority
	}
	else if (alreadySamePriority(employee_name, project_name, project_priority))
	{
		cout << "The project priority is already the same as the new priority." << endl;
		return false; // return false when same project with same priority
	}
	else
	{
		//update content of the linked list
		EmployeeNode* EmployeeNodeHead = head;
		while (EmployeeNodeHead != NULL)
		{
			if (EmployeeNodeHead->employee_name == employee_name)
			{
				ProjectNode* ProjectNodeHead = EmployeeNodeHead->head;
				while (ProjectNodeHead != NULL)
				{
					if (ProjectNodeHead->project_name == project_name)
					{
						//When matching project is found, it updates linked list
						int previous_project_priority = ProjectNodeHead->project_priority;
						ProjectNodeHead->project_priority = project_priority;
						project_priority = previous_project_priority; // to be returned as the reference parameter. 
						//call sort function after new update has been done
						reorderList(EmployeeNodeHead->head);
						return true;
					}
					ProjectNodeHead = ProjectNodeHead->next;
				}
			}
			EmployeeNodeHead = EmployeeNodeHead->down;
		}
	}
	return false;
}
/******************************************************************************
This is another extra function that is not given in homework file.
This function is used to sort employee names in ascending order
******************************************************************************/
void EmployeeProject2DLL::employeeListOrder(EmployeeNode*& EmployeeNodeHead)
{
	EmployeeNode* currentNode = EmployeeNodeHead;
	while (currentNode != NULL)
	{
		EmployeeNode* minNode = currentNode;
		EmployeeNode* tempNode = currentNode->down;
		while (tempNode != NULL) //iterate over all elemetns of the employee list
		{
			if (tempNode->employee_name < minNode->employee_name)
			{
				minNode = tempNode; // find minimum node
			}
			tempNode = tempNode->down;
		}
		if (minNode != currentNode)//if minimum node is not current node, order should be change.
		{
			//instead of changing nodes, contents of the nodes has been changed
			string temp_employee_name = currentNode->employee_name;
			currentNode->employee_name = minNode->employee_name;
			minNode->employee_name = temp_employee_name;

			ProjectNode* temp_head = currentNode->head;
			currentNode->head = minNode->head;
			minNode->head = temp_head;
		}
		currentNode = currentNode->down;//apply same procedure for new node
	}
}
/******************************************************************************
This is another function that is given in homework file.
This function is used to assign new employee to project
******************************************************************************/
bool EmployeeProject2DLL::assignEmployeeToProject(string employee_name, string project_name, int project_priority)
{
	EmployeeNode* EmployeeNodeHead = head;
	//If head is null (if there is not employee)
	if (EmployeeNodeHead == NULL) {
		//add new employee
		EmployeeNode* newRow = new EmployeeNode;
		newRow->employee_name = employee_name;
		newRow->head = NULL;
		newRow->down = NULL;
		//assign new porject
		ProjectNode* newProject = new ProjectNode;
		newProject->project_name = project_name;
		newProject->project_priority = project_priority;
		newProject->next = NULL;

		newRow->head = newProject;
		head = newRow;
		return true;
	}

	//when project has not been added due to another project with the same priority
	while (EmployeeNodeHead != NULL)
	{
		if (EmployeeNodeHead->employee_name == employee_name)
		{
			ProjectNode* ProjectNodeHead = EmployeeNodeHead->head;
			while (ProjectNodeHead != NULL)
			{
				if (ProjectNodeHead->project_priority == project_priority)
				{
					cout << "The project has not been added because there is another project with the same priority." << endl;
					return false;
				}
				ProjectNodeHead = ProjectNodeHead->next;
			}
		}
		EmployeeNodeHead = EmployeeNodeHead->down;
	}
	//when employee exists and project does not exists, add new project to the existing employee
	EmployeeNodeHead = head;
	while (EmployeeNodeHead != NULL)
	{
		if (EmployeeNodeHead->employee_name == employee_name)
		{
			ProjectNode* ProjectNodeHead = EmployeeNodeHead->head;
			while (ProjectNodeHead->next != NULL)
			{
				ProjectNodeHead = ProjectNodeHead->next;
			}
			//new project has been added
			ProjectNode* newNode = new ProjectNode;
			newNode->next = NULL;
			newNode->prev = ProjectNodeHead;
			newNode->project_name = project_name;
			newNode->project_priority = project_priority;
			ProjectNodeHead->next = newNode;
			//sorted again after new project has been added
			reorderList(EmployeeNodeHead->head);
			return true;
		}
		EmployeeNodeHead = EmployeeNodeHead->down;
	}
	//if there is no employee with given name, add new employee and asign new project
	EmployeeNodeHead = head;
	while (EmployeeNodeHead->down != NULL)
	{
		EmployeeNodeHead = EmployeeNodeHead->down;
	}
	EmployeeNode* newRow = new EmployeeNode;
	newRow->down = NULL;
	newRow->employee_name = employee_name;
	newRow->head = NULL;

	ProjectNode* newProject = new ProjectNode;
	newProject->project_name = project_name;
	newProject->project_priority = project_priority;
	newProject->next = NULL;

	newRow->head = newProject;
	//new project connected
	EmployeeNodeHead->down = newRow;
	//linked list ordered
	employeeListOrder(head);
	return true;
}
/******************************************************************************
This is another function that is given in homework file.
This function is used to withdraw employee from project
******************************************************************************/
void EmployeeProject2DLL::withdrawEmployeeFromProject(string employee_name, string project_name, int& project_priority)
{
	bool stop = false; //flag is used to stop function when it is needed
	EmployeeNode* previousEmployee = NULL;
	EmployeeNode* currentNode = head;

	while (currentNode != NULL && stop == false)
	{
		if (currentNode->employee_name == employee_name)
		{
			ProjectNode* currentProject = currentNode->head;
			ProjectNode* previousProject = NULL;

			while (currentProject != NULL && stop == false)
			{
				if (currentProject->project_name == project_name) //find node to be deleted
				{
					project_priority = currentProject->project_priority;

					// Update linked list 
					if (currentNode->head == currentProject)
					{
						currentNode->head = currentProject->next;
					}
					else
					{
						previousProject->next = currentProject->next;
					}

					delete currentProject; //delete project node
					stop = true;; // exit the inner loop after deleting the project
				}

				previousProject = currentProject;//update previous project
				currentProject = currentProject->next;
			}
			// If no projects left for the employee, remove the employee node
			if (currentNode->head == NULL)
			{
				if (previousEmployee == NULL)
				{
					head = currentNode->down;
				}
				else
				{
					previousEmployee->down = currentNode->down;
				}
				delete currentNode;
				stop = true; // exit the outer loop after removing the employee
			}
		}
		previousEmployee = currentNode;//update previous employee node
		currentNode = currentNode->down;
	}
}
/******************************************************************************
This is another function that is given in homework file.
This function is used to print the entire list
******************************************************************************/
void EmployeeProject2DLL::printTheEntireList()
{
	EmployeeNode* EmployeeNodeHead = head;
	employeeListOrder(EmployeeNodeHead);

	if (head == NULL) //if list is empty, give error message.
	{
		cout << "The list is empty." << endl;
	}
	while (EmployeeNodeHead != NULL) //if list is not empty, print its content
	{
		cout << EmployeeNodeHead->employee_name << ": ";
		ProjectNode* currentProject = EmployeeNodeHead->head;
		if (currentProject != NULL)
		{
			reorderList(currentProject); //order project again to aviod undesired order mistakes
		}
		while (currentProject != NULL)
		{
			cout << "(" << currentProject->project_name << ", " << currentProject->project_priority << ") ";
			currentProject = currentProject->next;
		}
		cout << endl;
		EmployeeNodeHead = EmployeeNodeHead->down;
	}
}
/******************************************************************************
This is another extra function that is not given in homework file.
This function is used to print project list in descending order.
Recursive approach is used to print in descending order.
******************************************************************************/
void EmployeeProject2DLL::printDesc(ProjectNode* project)
{
	if (project == nullptr) {
		return;
	}
	printDesc(project->next);
	cout << "(" << project->project_name << ", " << project->project_priority << ") ";

}
/******************************************************************************
This is another function that is given in homework file.
This function is used to print employee project(s) according to given option.
ascending (1)
or descending (0)
******************************************************************************/
void EmployeeProject2DLL::printEmployeeProjects(string employee_name, int option)
{
	int counter = 0;
	bool is_found = false;
	EmployeeNode* EmployeeNodeHead = head;
	while (EmployeeNodeHead != NULL && is_found == false)
	{
		if (EmployeeNodeHead->employee_name == employee_name)
		{
			is_found = true; //when the given employee name is found in employee list
		}
		counter++;
		EmployeeNodeHead = EmployeeNodeHead->down;
	}
	if (is_found)
	{
		bool stop = false;
		if (option == 0) //descending
		{
			EmployeeNode* curretnEmployee = head;
			while (curretnEmployee != nullptr && curretnEmployee->employee_name != employee_name) {
				curretnEmployee = curretnEmployee->down;
			}
			printDesc(curretnEmployee->head);
			cout << endl;
		}
		else if (option == 1) // ascending
		{
			EmployeeNode* newHead = head;
			while (newHead != NULL && stop == false)
			{
				if (newHead->employee_name == employee_name)
				{
					ProjectNode* currentProject = newHead->head;
					while (currentProject != NULL)
					{
						cout << "(" << currentProject->project_name << ", " << currentProject->project_priority << ") ";
						currentProject = currentProject->next;
					}
					cout << endl;
					stop = true;
				}
				newHead = newHead->down;
			}
		}
	}
	else if (counter != 0) // if there are employees in the list but the given name is not found
	{
		cout << "The employee is not in the list." << endl;
	}
	else if (counter == 0) // if employee list is empty
	{
		cout << "There are no employees in the list." << endl;
	}

}
/******************************************************************************
This is another function that is given in homework file.
This function is used to undo movements
******************************************************************************/
void EmployeeProject2DLL::undo(char operaiton, string employee_name, string project_name, int project_priority)
{
	if (operaiton == 'a') // if a is entered, call withdraw function
	{
		cout << "Undoing the assignment of a project." << endl;
		withdrawEmployeeFromProject(employee_name, project_name, project_priority);
	}
	else if (operaiton == 'w') // if w is entered, call assign function
	{
		cout << "Undoing the withdrawal of a project." << endl;
		assignEmployeeToProject(employee_name, project_name, project_priority);
	}
	else if (operaiton == 'u') // if u is entered, call update function
	{
		cout << "Undoing the update of a project priority." << endl;
		updateProjectPriority(employee_name, project_name, project_priority);
	}
}
/******************************************************************************
This is another function that is given in homework file.
This function is used to cleare linked list (delete all components)
******************************************************************************/
void EmployeeProject2DLL::clear()
{
	EmployeeNode* EmployeeNodeHead = head;
	while (EmployeeNodeHead != NULL)
	{
		ProjectNode* CurrentProject = EmployeeNodeHead->head;
		while (CurrentProject != NULL)
		{
			ProjectNode* temp = CurrentProject;
			CurrentProject = CurrentProject->next;
			delete temp; // delete all projects 

		}
		EmployeeNode* tempEmployee = EmployeeNodeHead;
		EmployeeNodeHead = EmployeeNodeHead->down;
		delete tempEmployee; // delete all employees
	}
}
#ifndef EMPLOYEEPROJECT2DLL_H
#define EMPLOYEEPROJECT2DLL_H

#include <string>
using namespace std;
struct ProjectNode
{
	string project_name;
	int project_priority;
	ProjectNode* next;
	ProjectNode* prev;
};

struct EmployeeNode
{
	string employee_name;
	ProjectNode* head;
	ProjectNode* tail;
	EmployeeNode* down;
};



class EmployeeProject2DLL
{
private:
	EmployeeNode* head;	
	bool anotherProjectWithSamePriority(string employee_name, string project_name, int project_priority);//This function is used to check whether there is a project exists with same priority
	bool alreadySamePriority(string employee_name, string project_name, int project_priority);//This function is used to check whether given project name has already same project priority
	void reorderList(ProjectNode*& ProjectNodeHead);//This function is used to sort projects of the employees
	void employeeListOrder(EmployeeNode*& EmployeeNodeHead);//This function is used to sort employee names in ascending order
	void printDesc(ProjectNode* project);//This function is used to print project list in descending order. 
	
public:
	EmployeeProject2DLL(); //This function is to creat an empty object with no employee
	bool isEmployeeAssignedToProject(string employee_name, string project_name); //This function checks wheterher employee is assigned to the project
	bool updateProjectPriority(string employee_name, string project_name, int& project_priority); //This function is used to update projects of the employees
	bool assignEmployeeToProject(string employee_name, string project_name, int project_priority); //This function is used to assign new employee to project
	void withdrawEmployeeFromProject(string employee_name, string project_name, int& project_priority); //This function is used to withdraw employee from project
	void printTheEntireList(); //This function is used to print the entire list
	void printEmployeeProjects(string employee_name, int option);//This function is used to print employee project(s) according to given option.
	void undo(char operaiton, string employee_name, string project_name, int project_priority);//This function is used to undo movements 
	void clear();//This function is used to cleare linked list (delete all components)
};



#endif
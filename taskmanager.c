#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996) 

//Constants:
#define MAX_TITLE_LENGTH 40 
#define MAX_DESCRIPTION_LENGTH 200
#define ID_FOUND 0
#define ID_NOT_FOUND_YET 1

//Data types:
struct Task
{
	int taskId;//The task Id
	char title[MAX_TITLE_LENGTH + 1];//Max length a title can be plus null terminator
	char description[MAX_DESCRIPTION_LENGTH + 1];//Max length a description can be plus null terminator
	struct Task* nextTask;//Pointer to the next task in linked list
};

//Prototypes
int getNum(void);
struct Task* addTask(struct Task* head, int inputTaskId, char inputTitle[], char inputDescription[]);
int deleteTask(struct Task* head, int inputTaskId);

int main(void)
{
	struct Task* head = NULL;
	int option = 0;
	//Prompting a user for an input:
	while (option != 5)
	{
		printf("\nPress 1 to Add Task \n");
		printf("Press 2 to Delete Task \n");
		printf("Press 3 to Find Task \n");
		printf("Press 4 to Pelete Tasks \n");
		printf("Press 5 to Exit \n");
		printf(">>>  ");

		// Storing user input into option variable:
		option = getNum();

		if (option == 1)
		{

			char title[MAX_TITLE_LENGTH + 1] = { 0 };
			char description[MAX_DESCRIPTION_LENGTH + 1] = { 0 };

			printf("\nEnter id for task being added\n");
			printf(">>>  ");
			int titleId = getNum();
			printf("\nEnter title for task being added\n");
			printf(">>>  ");
			fgets(title, MAX_TITLE_LENGTH, stdin);
			if (strlen(title) > 0)
			{
				if (title[strlen(title) - 1] == '\n')
				{
					title[strlen(title) - 1] = '\0';
				}
			}
			printf("\nEnter description for task being added\n");
			printf(">>>  ");
			fgets(description, MAX_TITLE_LENGTH, stdin);
			if (strlen(description) > 0)
			{
				if (description[strlen(description) - 1] == '\n')
				{
					description[strlen(description) - 1] = '\0';
				}
			}
			//Add task function
			head = addTask(head, titleId, title, description);
		}
		else if (option == 2)
		{
			printf("\nEnter Task Id number to delete\n");
			printf(">>>  ");
			int taskToDelete = getNum();
			//Delete task function
			int status = deleteTask(head, taskToDelete);
			if (status == 0)
			{
				printf("\nTask with Id %d was deleted\n", taskToDelete);
			}
			else
			{
				printf("\nUnable to find task with Id %d to perform deletion\n", taskToDelete);
			}
		}
		else if (option == 3)
		{
			//Find tasks logic
		}
		else if (option == 4)
		{
			//Print tasks logic
		}
		else if (option == 5)
		{
			return 0;
		}
		else
		{
			printf("ERROR: Invalid input. Please type in a valid option.\n");

		}
	}


	return 0;
}

/*
*Function: AddTask()
* Description : This function will take the user input for taskId, takes title
*				task description, allocate dynamic memory for a new task and assign
*				input values as data members of the new task.
* Parameters :  struct Task* head, int taskId, char title[], char description[]
* Returns : returns struct
*/

struct Task* addTask(struct Task* head, int inputTaskId, char inputTitle[], char inputDescription[])
{

	//1. Create a new student dynamic memory
	struct Task* newTask = (struct Task*)malloc(sizeof(struct Task));
	if (newTask == NULL)
	{
		printf("ERROR: No memory.\n");
		exit(EXIT_FAILURE);
	}

	newTask->taskId = inputTaskId;
	strcpy(newTask->title, inputTitle);
	strcpy(newTask->description, inputDescription);
	newTask->nextTask = NULL;
	//2. Asking for a user input, checking input and assginming to a new task
	//3. Checking for double index
	//4. Creating a sorted list

	return newTask;
}
/*end AddTask()*/


/*
*Function: AddTask()
* Description : This function will take the user input for taskId, taks title
*				task description, allocate dynamic memory for a new task and assign
*				input values as data members of the new task.
* Parameters :  struct Task* head -points to start of the linked list
				int taskId - the task we are deleting
* Returns : returns int 0=successfully deleted task with given taskId
*						1=unable to delete task with the given taskId
*/

int deleteTask(struct Task* head, int inputTaskId)
{

	int returnStatus = ID_NOT_FOUND_YET;//Set status to not found yet to indicate nothing deleted yet
	//1. Set current task to head (start of linked list)
	struct Task* current = head;

	//Before starting make sure head is not NULL(this means nothing in list)
	if (current != NULL)
	{
		//2. Check if inputTaskId is equal current task which also means
		//user entered task id that is at the head of the linked list

		if (current->taskId == inputTaskId)
		{
			//Check if there is a next Id that will become the new head Id
			if (current->nextTask != NULL)
			{
				//Set new head pointer value since we are
				//about to delete current head pointer
				head = current->nextTask;
			}
			else
			{
				//There is no task after current and current is head. So there is nothing
				//left in list after deletion.
				head = NULL;
			}
			free(current);//Delete the task
			returnStatus = ID_FOUND;//We deleted the task with the given inputTaskId

		}
		else
		{
			
			//3.Iterate over the linked list until the task coming up is the task we want to delete
			while (1)
			{
				if (current->nextTask == NULL)
				{
					break;//We were unable to find the taskId break out of while loop
				}
				int nextTaskId = current->nextTask->taskId;//Get the next taskId
				if (nextTaskId == inputTaskId)
				{
					//Get a reference to the task we are going to delete
					struct Task* taskToDelete = current->nextTask;
					if (taskToDelete->nextTask != NULL)
					{
						//Our current nextTask will become the task after the deleted node
						current->nextTask = taskToDelete->nextTask;
					}
					else
					{
						//There is no task after the task we are deleting so current
						// nextTask pointer will become NULL since it is last node
						// in the linked list.
						current->nextTask = NULL;
					}

					free(taskToDelete);//Delete the task
					returnStatus = ID_FOUND;//We deleted the task with the given inputTaskId
					break;//We found taskId break out of while loop
				}

				current = current->nextTask;//Iterate to next task
				if (current == NULL) break;//We were unable to find the taskId break out of while loop
			}
		}
	}
	return returnStatus;
}
/*end deleteTask()*/

/*
*Function: getNum()
*Description: This function will take the user input, extract the number from the string and return a number.
*Parameters: no parameters.
*Returns: result is stored in the variable int number.
*/

int getNum(void)
{
	/* we will see in a later lecture how we can improve this code */
	char record[121] = { 0 }; /* record stores the string */
	int number = 0;
	/* NOTE to student: indent and brace this function consistent with
	your others */
	/* use fgets() to get a string from the keyboard */
	fgets(record, 121, stdin);
	/* extract the number from the string; sscanf() returns a number
	* corresponding with the number of items it found in the string */
	if (sscanf(record, "%d", &number) != 1)
	{
		/* if the user did not enter a number recognizable by
		* the system, set number to -1 */
		number = -1;
	}
	return number;
}
/*end getNum()*/

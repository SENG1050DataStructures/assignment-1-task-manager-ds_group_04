#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996) 

//Constants:
#define MAX_TITLE_LENGTH 40
#define MAX_DESCRIPTION_LENGTH 200

//Data types:
struct Task
{
	int taskId;
	char title[MAX_TITLE_LENGTH + 1];
	char description[MAX_DESCRIPTION_LENGTH + 1];
	struct Task* nextTask;
};

//Prototypes
int getNum(void);
struct Task* addTask(struct Task* head, int inputTaskId, char inputTitle[], char inputDescription[]);


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
			//Add task function
			addTask(head, 1,"to do", "description");
		}
		else if (option == 2)
		{
			//Delete task logic
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
* Description : This function will take the user input for taskId, taks title
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

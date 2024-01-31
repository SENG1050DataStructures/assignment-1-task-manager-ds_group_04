#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996) 

//Constants:
#define MAX_TITLE_LENGTH 40 
#define MAX_DESCRIPTION_LENGTH 200
#define ID_FOUND 0
#define ID_NOT_FOUND_YET 1
#define NO_VALID_DIGIT -1

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
struct Task* FindTaskByIndex(struct Task* head, int index);
void overwriteNewLine(char* input);

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
		printf("Press 4 to Print Tasks \n");
		printf("Press 5 to Exit \n");
		printf(">>>  ");

		// Storing user input into option variable:
		option = getNum();

		if (option == 1)
		{

			char title[MAX_TITLE_LENGTH + 1] = { 0 };
			char description[MAX_DESCRIPTION_LENGTH + 1] = { 0 };
			int titleId = NO_VALID_DIGIT;

			while (titleId < 0)
			{
				int inputId = 0;
				printf("\nEnter digital ID for task being added\n");
				printf(">>>  ");
				inputId = getNum();

				if (inputId == NO_VALID_DIGIT)
				{
					printf("No valid ID was entered.\n");
				}
				else
				{
					titleId = inputId;
				}

			}
			//Prompting user for title input:
			printf("\nEnter title for task being added\n");
			printf(">>>  ");
			fgets(title, MAX_TITLE_LENGTH, stdin);
			if (strcmp(title, "\n") == 0)
			{
				strcpy(title, "NO TITLE");
			}
			overwriteNewLine(title);

			//Prompting user for description input
			printf("\nEnter description for task being added\n");
			printf(">>>  ");
			fgets(description, MAX_TITLE_LENGTH, stdin);
			if (strcmp(description, "\n") == 0)
			{
				strcpy(description, "NO DESCRIPTION");
			}
			overwriteNewLine(description);

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
*Function: addTask()
* Description : This function will take the user input for taskId, takes title
*				task description, allocate dynamic memory for a new task and assign
*				input values as data members of the new task.
* Parameters :  struct Task* head, int taskId, char title[], char description[]
* Returns : returns struct
*/

struct Task* addTask(struct Task* head, int inputTaskId, char inputTitle[], char inputDescription[])
{

	//1. Create a new task dynamic memory
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

	//2. Creating a sorted list
	if (head == NULL || head->taskId >= inputTaskId)
	{
		newTask->nextTask = head;
		head = newTask;
	}	
	else
	{
		struct Task* current = head;
		while (current->nextTask != NULL && current->nextTask->taskId < inputTaskId)
		{
			current = current->nextTask;

		}

		newTask->nextTask = current->nextTask;
		current->nextTask = newTask;
	}

	return head;
}
/*end addTask()*/


/*
*Function: FindTaskByIndex()
* Description : This function has been created to search for a task within a linked 
* list of tasks based on its index (position) within the list. First, it initializes 
* a pointer current to the head of the linked list (head). Second, it initializes a variable
* “count” to keep track of the current position in the linked list. Third, it enters a while 
* loop that iterates through the linked list until either the end of the list (current becomes NULL)
* or the desired index (count) is reached. Next, into the loop: If the current count matches the 
* specified index, it means the desired task has been found, so it returns a pointer to that task 
* “current”. On the other hand, if the index hasn't been reached yet, it increments the count and 
* moves “current” to the next task in the list (current->nextTask). Finally, if the loop terminates 
* without finding the task (because the list is empty or the index is out of bounds), it returns NULL 
* to indicate that the task was not found.
* Parameters : struct Task* head, int index
* Returns : struct Task*
*/



struct Task* FindTaskByIndex(struct Task* head, int index)
{
	struct Task* current = head;
	int count = 0;

	while (current != NULL)
	{
		if (count == index)
		{
			return current;
		}
		count++;
		current = current->nextTask;
	}
	return NULL; //index out of limits
}



/*
*Function: deleteTask()
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
	char record[121] = { 0 };
	int number = 0;
	fgets(record, 121, stdin);

	if (sscanf(record, "%d", &number) != 1)
	{
		number = NO_VALID_DIGIT;
	}
	return number;
}
/*end getNum()*/

/*
* Function: void overwriteNewLine()
* Description : Function takes a string and overwrites and new line character with a null character
*				for further string comparison.
* Parameters : char*
* Returns : returns void.
*/
void overwriteNewLine(char* input)
{
	size_t lengthOfInput = strlen(input);
	int i = 0;
	for (i = 0; i < lengthOfInput; i++) {
		if (input[i] == '\n')
		{
			input[i] = '\0';
		}
	}
}
/*end overwriteNewLine()*/

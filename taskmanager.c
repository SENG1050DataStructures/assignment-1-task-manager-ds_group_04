/*
* FILE : taskmanager.c
* PROJECT : SENG1050 - Group Assignment #1
* PROGRAMMER(S) : Mezin Olha, Restivo Tino, Reyes Melissa
* FIRST VERSION : 2024-01-31
* DESCRIPTION : This file contains the logic for the console-based task management system,
*				using linked lists and structs with dynamic memory allocation.
*/

#include "taskmanager.h"


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
	if (head == NULL || head->taskId > inputTaskId)
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


struct Task* findTaskByIndex(struct Task* head, int index)
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
	return NULL; 
}


int deleteTask(struct Task** head, int inputTaskId)
{

	int returnStatus = ID_NOT_FOUND_YET;
	struct Task* current = *head; //
	//struct Task* current = *head; 
	
	if (current != NULL)
	{
		

		if (current->taskId == inputTaskId)
		{
			
			if (current->nextTask != NULL)
			{
				
				*head = current->nextTask;
			}
			else
			{
				
				*head = NULL;
			}
			free(current);
			returnStatus = ID_FOUND;

		}
		else
		{			
			while (1)
			{
				if (current->nextTask == NULL)
				{
					break;
				}
				int nextTaskId = current->nextTask->taskId;
				if (nextTaskId == inputTaskId)
				{
					
					struct Task* taskToDelete = current->nextTask;
					if (taskToDelete->nextTask != NULL)
					{
						
						current->nextTask = taskToDelete->nextTask;
					}
					else
					{
						
						current->nextTask = NULL;
					}

					free(taskToDelete);
					returnStatus = ID_FOUND;
					break;
				}

				current = current->nextTask;
				
			}
		}
	}
	return returnStatus;
}


void printTasks(struct Task* head)
{
	struct Task* current = head;

	if (current != NULL)
	{
		while (current != NULL)
		{
			printf("\nTaskId: %d\nTitle: %s\nDescription: %s\n\n", current->taskId, current->title, current->description);
			current = current->nextTask;
		}
	}
	else
	{
		printf("No tasks found\n");
	}
}



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

int validateInput(char* input)
{
	int foundLineBreak = 0;
	int warningIfTextTruncated = TEXT_WAS_NOT_TRUNCATED;
	if (strcmp(input, "\n") == 0)
	{
		strcpy(input, "NO INPUT");
	}
	else
	{
		size_t lengthOfInput = strlen(input);
		int i = 0;
		//If text does not end with a carriage return it was truncated
		for (i = 0; i < lengthOfInput; i++) {
			if (input[i] == '\n')
			{
				foundLineBreak = 1;
				input[i] = '\0';
			}
		}
		if (foundLineBreak == 0)
		{
			warningIfTextTruncated = TEXT_WAS_TRUNCATED;
		}
	}
	if (foundLineBreak == 0)
	{
		//If text wasn't truncated we should have found the line break
		//empty out the stdin buffer
		//so fgets doesn't fill next line of text if user entered too much in text

		while (1)
		{
			char tempBuffer[5] = { 0 };
			fgets(tempBuffer, 5, stdin);
			size_t length = strlen(tempBuffer);
			if (length == 0 || tempBuffer[length - 1] == '\n')
			{
				break;
			}
		}
	}

	return warningIfTextTruncated;
}

int checkForDuplicate(int array[], int* position, int input)
{
	for (int i = 0; i < MAX_TASKS_NUMBER; i++)
	{
		if (array[i] == input)
		{
			return DUPLICATE;
		}
	}
	
	if (*position == 0)
	{
		array[0] = input;
		*position += 1;
		return *position;
	}
	else
	{
		array[*position] = input;
		*position += 1;
		return *position;
	}
}

void freeList(struct Task* head)
{
	struct Task* current = head;
	struct Task* tempNode;

	while (current != NULL) {
		tempNode = current->nextTask;
		free(current);
		current = tempNode;
	}

}

#include "taskmanager.h"


int main(void)
{
	struct Task* head = NULL;

	int option = 0;
	int arrayOfIDs[MAX_TASKS_NUMBER] = { 0 };
	int currentElement = 0;

	while (option != 5)
	{
		printf("\nPress 1 to Add Task \n");
		printf("Press 2 to Delete Task \n");
		printf("Press 3 to Find Task \n");
		printf("Press 4 to Print Tasks \n");
		printf("Press 5 to Exit \n");
		printf(">>>  ");

		option = getNum();

		if (option == 1)
		{
			char title[MAX_TITLE_LENGTH + 1] = { 0 };
			char description[MAX_DESCRIPTION_LENGTH + 1] = { 0 };
			int taskID = NO_VALID_DIGIT;

			while (taskID < 0)
			{
				int inputId = 0;
				printf("\nEnter digital ID for task being added\n");
				printf(">>>  ");
				inputId = getNum();

				if (inputId == NO_VALID_DIGIT || inputId == 0)
				{
					printf("No valid ID was entered.\n");
				}
				else
				{
					int duplicated = checkForDuplicate(arrayOfIDs, &currentElement, inputId);
					if (duplicated == DUPLICATE)
					{
						printf("\n ID %d already exists.\n", inputId);

					}
					else
					{
						taskID = inputId;
					}
				}
			}
			printf("\nEnter title for task being added\n");

			printf(">>>  ");
			fgets(title, MAX_TITLE_LENGTH, stdin);
			if (validateInput(title) == TEXT_WAS_TRUNCATED)
			{
				printf("\nText was truncated to...%s\n",title);
			}

			printf("\nEnter description for task being added\n");
			printf(">>>  ");

			fgets(description, MAX_DESCRIPTION_LENGTH, stdin);
			
			if (validateInput(description) == TEXT_WAS_TRUNCATED)
			{
				printf("\nText was truncated to...%s\n", description);
			}

			head = addTask(head, taskID, title, description);

		}
		else if (option == 2)
		{
			printf("\nEnter digital ID for task being deleted\n");
			printf(">>>  ");
			int taskToDelete = getNum();

			if (taskToDelete == NO_VALID_DIGIT)
			{
				printf("No valid ID was entered.\n");
			}
			else
			{
				//Delete task function
				int status = deleteTask(&head, taskToDelete);

				if (status == 0)
				{
					printf("\nTask with Id %d was deleted\n", taskToDelete);
				}
				else
				{
					printf("\nUnable to find task with Id %d to perform deletion\n", taskToDelete);
				}
			}


		}
		else if (option == 3)
		{
			//Find tasks logic
		}
		else if (option == 4)
		{
			printTask(head);
		}
		else if (option == 5)
		{
			if (head != NULL)
			{
				freeList(head);
			}
			return 0;
		}
		else
		{
			printf("ERROR: Invalid input. Please type in a valid option.\n");

		}
	}

	

	return 0;
}

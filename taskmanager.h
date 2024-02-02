
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
#define DUPLICATE -2
#define MAX_TASKS_NUMBER 500
#define TEXT_WAS_NOT_TRUNCATED 0
#define TEXT_WAS_TRUNCATED 1

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
int deleteTask(struct Task** head, int inputTaskId);
struct Task* FindTaskByIndex(struct Task* head, int index);
int validateInput(char* input);
void printTask(struct Task* head);
int checkForDuplicate(int array[], int* position, int input);
void FreeList(struct Student* head);
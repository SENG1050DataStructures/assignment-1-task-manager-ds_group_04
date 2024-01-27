#include <stdio.h>


#define MAX_TITLE_LENGTH 40
#define MAX_DESCRIPTION_LENGTH 200


struct Task
{
    int taskId;
    char title[MAX_TITLE_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
    struct Task* nextTask;
};

int main(void)
{
    printf("test");
}
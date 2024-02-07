[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/8xUcoGNc)
# Assignment1
The write-up goes here.

Write up for function addTask()
* Description: This function will add a new task to the linked list.  It takes user input for taskId, task title,
* and task description, allocates dynamic memory for a new task, and assigns the input values as data members
* of the new task. I will then add the new task into the linked list sorted based on the taskId.
* The parameters for this function are:
* - struct Task* head: which points to the start of the linked list.
* - int inputTaskId: Which is the identifier of the task to be added.
* - char inputTitle[]: Which is the title or name of the task.
* - char inputDescription[]: A brief description of the task.
* The return for this function is:
* Returns: struct Task*: Returns the updated head of the linked list after adding the new task.
* 

Write up for function findTaskByIndex()
* Description: This function will return the pointer to the task at a given index. It takes two user inputs, a pointer to the head of the linked list and a integer value for the index we are looking for.
* We start by setting a local variable count to 0. We will use this variable to keep track of how many tasks (nodes) we have looked at, in other words what index we are at.
* We start at the head of the linked list, we set a local variable called current to this pointer value.
* We want to iterate across each node in the linked list.
* To do this we use a while loop and compare it to NULL to determine if we reached the end of the linked list.
* Step 1) Before we iterate to the next node in the list we compare if our count value is equal to our parameter index. If we find count is equal to the parameter index we have found the pointer at the given index. 
* If statement in step 1 is true we can now return the value of current back to main. Else go to step 2.
* Step 2) If we find count does not equal index we set current to current->nextTask so next time we iterate we are now pointing to the next node in the linked list.
* Step 3) Also at this time we increment count by one to designate that we are looking at the next index in the list.
* Step 4) Repeat step 1 again.
* We keep doing these steps until count is equal to index or we reach the end of the list, in that case we never found our index and can return NULL to indicate there is not a node at the given index.
* The parameters for this function are:
* - struct Task* head: which points to the start of the linked list.
* - int index: This is a user entered parameter and represents what index we want to find
* The return for this function is:
* Returns: struct Task*: Returns a pointer to the node at the given index. 
* If the index we were given is 0 then we are now done and can return



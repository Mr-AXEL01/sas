      /********************************************************************************\
     /                                                                               /  \
    /                                  SAS PROJECT.                                 /    \
   /                                                                               /      \
  /creating a to do list app as a final project of sas, enjoy surffing in C......./        \
 /                                                                               /          \
/*******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

// declare global function
void seetodo();
void addtodo();
// void edittodo();
// void deletetodo();
// creating a struct

enum STATUS
{
    to_do,
    doing,
    done
};
struct TODO
{
    int id;
    char title[30];
    char description[1000];
    int deadline;
    enum STATUS status;
};
struct TODO tasks[150];
int length = 0;      // number of tasks
int id = 0;          // unique identifier incremented every time user create new task
int numberTasks = 0; // number of tasks user wants to create

int main()
{
    // creating a menu so we can provide a user-friendly interface and navigate in the app.
    int choice;
    do
    {
        system("cls");
        printf("1.see your to do list\n");
        printf("2.add a new task\n");
        printf("3.edit a task\n");
        printf("4.delete a task\n");
        printf("0.Exit\n");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            seetodo();
            break;
        case 2:
            addtodo();
            break;
        case 3:
            // edittodo();
            break;
        case 4:
            // deletetodo();
            break;
        }
        printf("\n\n");
        system("pause");
    } while (choice != 0);
}

void seetodo()
{
    if (length == 0)
    {
        printf("Your to do list is empty\n");
    }
    for (int i = 0; i < length; i++)
    {
        printf("ID: %d\n", tasks[i].id);
        printf("Title: %s\n", tasks[i].title);
        printf("Description: %s\n", tasks[i].description);
        printf("Deadline: %d\n", tasks[i].deadline);
        // printf("Status: %d\n", tasks[i].status);
    }
}

void addtodo()
{
    printf("How Many Task U want create\n");
    scanf("%d", &numberTasks);

    for (int i = length; i < numberTasks + length; i++)
    {
        tasks[i].id = id;
        id++;
        printf("Enter Title\n");
        scanf("%s", tasks[i].title);
        printf("Enter Description\n");
        scanf("%s", tasks[i].description);
        printf("Enter Deadline\n");
        scanf("%d", &tasks[i].deadline);
        // printf("Enter Status\n");
        // scanf("%d", &tasks[i].status);
    }
    length = numberTasks + length;
}
void edittodo(){
    int ID;
    printf("enter the ID of the task that you wanna edit : ");
    scanf("%d", &ID);
    int found = 0;
    for (int i = 0 ; i < numberTasks ; i++){
        if (tasks[i].id == ID){
            found = 1;
            printf("EDITING TASK %d\n", ID);
            int editCoice;
            do
            {
                printf("1.edit Description\n");
                printf("2.edit deadline");
                printf("3.edit status");
                printf("0.done of editing");
                printf("\n\nEnter your choice: ");
                scanf("%d", &editCoice);
                swich(editCoice){
                    case 1 :
                    {
                        printf("enter your new description");
                        scanf
                    }
                }
            }
        }
    }
}
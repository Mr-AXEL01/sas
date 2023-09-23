      /*******************************************************************************\
     /                                                                               / \
    /                                SAS PROJECT.                                   /   \
   /               creating a to_do_list app with c programming.                   /     \
  / please enjoy surffing on my code of sas project as the final exam for youcode./       \
 /                                                                               /         \
/******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

enum STATUS
{
    TO_DO,
    DOING,
    DONE
};

struct TODO
{
    int id;
    char title[50];
    char description[1000];
    char deadline[11];
    enum STATUS status;
};

struct TODO tasks[150];
int length = 0;
int id = 1;
int numberTasks = 0;

void seeTodo();
void addTodo();
void editTodo();
void deleteTodo();
void searchTaskById();
void searchTaskByTitle(char *searchTitle);
void displayStatistics();

int main()
{
    int choice;
    do
    {
        printf("\n\t\t\t#########################-----MENU-----#########################\t\t\t\n");
        printf("1. See your to-do list\n");
        printf("2. Add a new task\n");
        printf("3. Edit a task\n");
        printf("4. Delete a task\n");
        printf("5. Search for tasks\n");
        printf("6. Statistics\n");
        printf("0. Exit\n");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            seeTodo();
            break;
        case 2:
            addTodo();
            break;
        case 3:
            editTodo();
            break;
        case 4:
            deleteTodo();
            break;
        case 5:
        {
            int searchChoice;
            printf("\n*****************************************************\n");
            printf("1. Search by Identifier\n");
            printf("2. Search by Title\n");
            printf("Enter your search choice: ");
            scanf("%d", &searchChoice);
            if (searchChoice == 1)
            {
                searchTaskById();
            }
            else if (searchChoice == 2)
            {
                char searchTitle[50];
                printf("\n*****************************************************\n");
                printf("Enter the title to search for: ");
                scanf("%s", searchTitle);
                searchTaskByTitle(searchTitle);
            }
            else
            {
                printf("\n\t###################...(*_*)...###################\t\n");
                printf("Invalid search choice\n");
            }
        }
        break;
        case 6:
            displayStatistics();
            break;
        }
        printf("\n\n");
        // Use a simple getchar to wait for user input
        printf("Press Enter to continue...");
        getchar();
        getchar(); // Consume the newline character from the previous input
    } while (choice != 0);
}

void seeTodo()
{
    if (length == 0)
    {
        printf("\n###################...(*_*)...###################\n");
        printf("Your to-do list is empty\n");
    }
    else
    {
        printf("\n\n");
        printf("Your to-do list is: \n");
        for (int i = 0; i < length; i++)
        {
            printf("\n\n");
            printf("------------------------------------------------------------------------\n");
            printf("ID: %d\n\n", tasks[i].id);
            printf("------------------------------------------------------------------------\n");
            printf("Title: %s\n\n", tasks[i].title);
            printf("------------------------------------------------------------------------\n");
            printf("Description: %s\n", tasks[i].description);
            printf("------------------------------------------------------------------------\n");
            printf("Deadline: %s\n\n", tasks[i].deadline);
            printf("------------------------------------------------------------------------\n");
            printf("Status: ");
            switch (tasks[i].status)
            {
            case TO_DO:
                printf("To-Do\n");
                break;
            case DOING:
                printf("Doing\n");
                break;
            case DONE:
                printf("Done\n");
                break;
            }
            printf("------------------------------------------------------------------------\n");
            printf("\n\n");
        }
    }
}

void addTodo()
{
    printf("How many tasks do you want to create?\n");
    scanf("%d", &numberTasks);

    while (getchar() != '\n')
        ; // Consume the newline character

    for (int i = length; i < numberTasks + length; i++)
    {
        tasks[i].id = id;
        id++; // increment id , so the next task will have a different ID
        printf("Enter Title: ");
        scanf("%49s", tasks[i].title); // the %49s is to max the characters

        printf("Enter Deadline (yyyy-mm-dd): ");
        scanf("%10s", tasks[i].deadline); // Read the deadline as a string

        // Consume the newline character again before reading the description
        while (getchar() != '\n')
            ;

        printf("Enter Description: ");
        fgets(tasks[i].description, sizeof(tasks[i].description), stdin);

        printf("Enter Status (0 - To-Do, 1 - Doing, 2 - Done): ");
        scanf("%d", &tasks[i].status);
    }
    length = numberTasks + length;
}

void editTodo()
{
    int ID;
    printf("Enter the ID of the task you want to edit: ");
    scanf("%d", &ID);
    int found = 0;
    for (int i = 0; i < length; i++)
    {
        if (tasks[i].id == ID)
        {
            found = 1;
            printf("EDITING TASK %d\n", ID);
            int editChoice;
            do
            {
                printf("1. Edit Description\n");
                printf("2. Edit Deadline\n");
                printf("3. Edit Status\n");
                printf("0. Done Editing\n");
                printf("\n\nEnter your choice: ");
                scanf("%d", &editChoice);

                switch (editChoice)
                {
                case 1:
                    printf("Enter the new description: ");
                    while (getchar() != '\n')
                        ; // Consume the newline character
                    fgets(tasks[i].description, sizeof(tasks[i].description), stdin);
                    break;
                case 2:
                    printf("Enter a new deadline: ");
                    scanf("%10s", tasks[i].deadline); // Read the deadline as a string
                    break;
                case 3:
                    printf("Enter the new status (0 - To-Do, 1 - Doing, 2 - Done): ");
                    scanf("%d", &tasks[i].status);
                    break;
                }
            } while (editChoice != 0);
        }
    }
    if (!found)
    {
        printf("Task with ID %d not found.\n", ID);
    }
}

void deleteTodo()
{
    int ID;
    printf("Enter the ID of the task you want to delete: ");
    scanf("%d", &ID);
    int found = 0;
    for (int i = 0; i < length; i++)
    {
        if (tasks[i].id == ID)
        {
            found = 1;
            printf("DELETING TASK %d\n", ID);
            for (int j = i; j < length - 1; j++)
            {
                tasks[j] = tasks[j + 1];
            }
            length--; // decrease the length to avoid having duplicate tasks at the end
            break;
        }
    }
    if (!found)
    {
        printf("Task with ID %d not found.\n", ID);
    }
}

void searchTaskById()
{
    int ID;
    printf("Enter the ID of the task you want to search for: ");
    scanf("%d", &ID);
    int found = 0;
    for (int i = 0; i < length; i++)
    {
        if (tasks[i].id == ID)
        {
            found = 1;
            printf("Task found:\n");
            printf("ID: %d\n", tasks[i].id);
            printf("Title: %s\n", tasks[i].title);
            printf("Description: %s\n", tasks[i].description);
            printf("Deadline: %s\n", tasks[i].deadline);
            printf("Status: ");
            switch (tasks[i].status)
            {
            case TO_DO:
                printf("To-Do\n");
                break;
            case DOING:
                printf("Doing\n");
                break;
            case DONE:
                printf("Done\n");
                break;
            }
            break;
        }
    }
    if (!found)
    {
        printf("Task with ID %d not found.\n", ID);
    }
}

void searchTaskByTitle(char *searchTitle)
{
    // Convert the user's input to lowercase to ensure that the search will match titles regardless of capitalization.
    for (int i = 0; searchTitle[i]; i++)
    {
        searchTitle[i] = tolower(searchTitle[i]);
    }

    // Search for tasks by title
    int found = 0;
    for (int i = 0; i < length; i++)
    {
        char taskTitleLower[50]; // Make a lowercase copy of the task title
        strcpy(taskTitleLower, tasks[i].title); // Copy the title of the current task to taskTitleLower

        for (int j = 0; taskTitleLower[j]; j++)
        {
            taskTitleLower[j] = tolower(taskTitleLower[j]);
        }

        // Compare the lowercase task title with the lowercase search title
        if (strcmp(taskTitleLower, searchTitle) == 0)
        {
            found = 1;
            printf("Task found:\n");
            printf("ID: %d\n", tasks[i].id);
            printf("Title: %s\n", tasks[i].title);
            printf("Description: %s\n", tasks[i].description);
            printf("Deadline: %s\n", tasks[i].deadline);
            printf("Status: ");
            switch (tasks[i].status)
            {
            case TO_DO:
                printf("To-Do\n");
                break;
            case DOING:
                printf("Doing\n");
                break;
            case DONE:
                printf("Done\n");
                break;
            }
        }
    }
    if (!found)
    {
        printf("No tasks with the title \"%s\" found.\n", searchTitle);
    }
}

void displayStatistics()
{
    printf("Total number of tasks: %d\n", length);

    int completeTasks = 0;
    int incompleteTasks = 0;
    time_t currentTime;
    time(&currentTime);

    for (int i = 0; i < length; i++)
    {
        if (tasks[i].status == DONE)
        {
            completeTasks++;
        }
        else
        {
            incompleteTasks++;
        }

        // Initialize the struct tm with zeros
        struct tm deadline_tm = {0};

        // Parse the deadline date string in the format "yyyy-mm-dd"
        if (sscanf(tasks[i].deadline, "%d-%d-%d", &deadline_tm.tm_year, &deadline_tm.tm_mon, &deadline_tm.tm_mday) != 3)
        {
            printf("Failed to parse deadline for Task %d\n", tasks[i].id);
            continue; // Skip this task if parsing fails
        }

        // Adjust month and year (they are 0-based and years since 1900 in struct tm)
        deadline_tm.tm_mon -= 1;
        deadline_tm.tm_year -= 1900;

        // Convert the struct tm to a timestamp
        time_t deadline_timestamp = mktime(&deadline_tm);

        // Calculate the time difference in seconds
        int secondsRemaining = deadline_timestamp - currentTime;

        // Calculate days remaining
        int daysRemaining = secondsRemaining / (60 * 60 * 24);

        printf("Task %d - Days Remaining: %d\n", tasks[i].id, daysRemaining);
    }

    printf("Number of complete tasks: %d\n", completeTasks);
    printf("Number of incomplete tasks: %d\n", incompleteTasks);
}

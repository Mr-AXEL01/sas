      /********************************************************************************
     /                                                                               /
    /                          Online C++ Compiler.                                 /
   /            Code, Compile, Run and Debug C++ program online.                   /
  /Write your code in this editor and press "Run" button to compile and execute it/
 /                                                                               /
/*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
          int deadline;
          enum STATUS status;
      };

      struct TODO tasks[150];
      int length = 0;
      int id = 0;
      int numberTasks = 0;

      void seeTodo();
      void addTodo();
      void editTodo();
      void deleteTodo();

      int main()
      {
          int choice;
          do
          {
              printf("1. See your to-do list\n");
              printf("2. Add a new task\n");
              printf("3. Edit a task\n");
              printf("4. Delete a task\n");
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
              printf("Your to-do list is empty\n");
          }
          else
          {
              printf("Your to-do list is:\n");
              for (int i = 0; i < length; i++)
              {
                  printf("ID: %d\n", tasks[i].id);
                  printf("Title: %s\n", tasks[i].title);
                  printf("Description: %s\n", tasks[i].description);
                  printf("Deadline: %d\n", tasks[i].deadline);
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
                  printf("\n");
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
              id++;
              printf("Enter Title: ");
              scanf("%49s", tasks[i].title);

              printf("Enter Deadline: ");
              scanf("%d", &tasks[i].deadline);

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
                          scanf("%d", &tasks[i].deadline);
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
                  length--;
                  break;
              }
          }
          if (!found)
          {
              printf("Task with ID %d not found.\n", ID);
          }
      }

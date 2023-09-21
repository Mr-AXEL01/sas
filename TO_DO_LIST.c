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
      void searchById();
      void searchByTitle();
      void displayStatistics();
      void sortAlphabetically();
      void sortByDeadline();
      void displayNearDeadlineTasks();

      int main()
      {
          int choice;
          do
          {
              printf("1. Manage Tasks\n");
              printf("2. View Tasks\n");
              printf("3. Edit Tasks\n");
              printf("4. Search for Tasks\n");
              printf("5. Statistics\n");
              printf("0. Exit\n");
              printf("\n\nEnter your choice: ");
              scanf("%d", &choice);

              switch (choice)
              {
              case 1:
                  addTodo();
                  break;
              case 2:
                  seeTodo();
                  break;
              case 3:
                  editTodo();
                  break;
              case 4:
                  printf("1. Search by ID\n");
                  printf("2. Search by Title\n");
                  printf("Enter your choice: ");
                  int searchChoice;
                  scanf("%d", &searchChoice);
                  if (searchChoice == 1)
                  {
                      searchById();
                  }
                  else if (searchChoice == 2)
                  {
                      searchByTitle();
                  }
                  else
                  {
                      printf("Invalid choice\n");
                  }
                  break;
              case 5:
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

      void searchById()
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
                  printf("Task found with ID %d:\n", ID);
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
                  break; // Exit the loop once the task is found
              }
          }
          if (!found)
          {
              printf("Task with ID %d not found.\n", ID);
          }
      }

      void searchByTitle()
      {
          char title[50];
          printf("Enter the title of the task you want to search for: ");
          scanf("%49s", title);
          int found = 0;
          for (int i = 0; i < length; i++)
          {
              if (strcmp(tasks[i].title, title) == 0)
              {
                  found = 1;
                  printf("Task found with title '%s':\n", title);
                  printf("ID: %d\n", tasks[i].id);
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
          if (!found)
          {
              printf("No tasks found with title '%s'.\n", title);
          }
      }

      void displayStatistics()
      {
          printf("Total number of tasks: %d\n", length);

          int completeTasks = 0;
          int incompleteTasks = 0;
          int nearDeadlineTasks = 0;

          time_t currentTime;
          time(&currentTime);
          struct tm *currentDate = localtime(&currentTime);

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

              int daysRemaining = (tasks[i].deadline - (currentDate->tm_year + 1900) * 365 - (currentDate->tm_mon) * 30 - currentDate->tm_mday);
              if (daysRemaining <= 3)
              {
                  nearDeadlineTasks++;
              }
          }

          printf("Number of complete tasks: %d\n", completeTasks);
          printf("Number of incomplete tasks: %d\n", incompleteTasks);
          printf("Number of tasks with deadline in 3 days or less: %d\n", nearDeadlineTasks);
      }

      void sortAlphabetically()
      {
          for (int i = 0; i < length - 1; i++)
          {
              for (int j = i + 1; j < length; j++)
              {
                  if (strcmp(tasks[i].title, tasks[j].title) > 0)
                  {
                      // Swap tasks[i] and tasks[j]
                      struct TODO temp = tasks[i];
                      tasks[i] = tasks[j];
                      tasks[j] = temp;
                  }
              }
          }
      }

      void sortByDeadline()
      {
          for (int i = 0; i < length - 1; i++)
          {
              for (int j = i + 1; j < length; j++)
              {
                  if (tasks[i].deadline > tasks[j].deadline)
                  {
                      // Swap tasks[i] and tasks[j]
                      struct TODO temp = tasks[i];
                      tasks[i] = tasks[j];
                      tasks[j] = temp;
                  }
              }
          }
      }

      void displayNearDeadlineTasks()
      {
          time_t currentTime;
          time(&currentTime);
          struct tm *currentDate = localtime(&currentTime);

          printf("Tasks with deadline in 3 days or less:\n");

          for (int i = 0; i < length; i++)
          {
              int daysRemaining = (tasks[i].deadline - (currentDate->tm_year + 1900) * 365 - (currentDate->tm_mon) * 30 - currentDate->tm_mday);
              if (daysRemaining <= 3)
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

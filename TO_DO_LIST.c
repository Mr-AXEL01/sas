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

      // coustome type for deadline
      struct Deadline
      {
          int day;
          int month;
          int year;
      };

      struct TODO
      {
          int id;
          char title[50];
          char description[1000];
          struct Deadline deadline;
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
      void sortingByAlpha();
      void tasksDeadlineEndSoon();
      int daysRemaining(struct Deadline deadline);
      void sortingByDeadline();

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
              printf("7. Sorting\n");

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
              case 7:
                  sortingMenu();
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
                  printf("Deadline: %d-%d-%d\n",
                         tasks[i].deadline.day,
                         tasks[i].deadline.month,
                         tasks[i].deadline.year

                  );
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

              printf("Enter deadline for Task %d (dd-mm-yyyy): ", tasks[i].id);
              scanf("%d-%d-%d",
                    &tasks[i].deadline.day,
                    &tasks[i].deadline.month,
                    &tasks[i].deadline.year);

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
                          scanf("%d-%d-%d",
                                &tasks[i].deadline.day,
                                &tasks[i].deadline.month,
                                &tasks[i].deadline.year);
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
                  printf("\n\n");
                  printf("------------------------------------------------------------------------\n");
                  printf("ID: %d\n\n", tasks[i].id);
                  printf("------------------------------------------------------------------------\n");
                  printf("Title: %s\n\n", tasks[i].title);
                  printf("------------------------------------------------------------------------\n");
                  printf("Description: %s\n", tasks[i].description);
                  printf("------------------------------------------------------------------------\n");
                  printf("Deadline: %d-%d-%d\n",
                         tasks[i].deadline.day,
                         tasks[i].deadline.month,
                         tasks[i].deadline.year

                  );
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
                  //   printf("Task found:\n");
                  //   printf("ID: %d\n", tasks[i].id);
                  //   printf("Title: %s\n", tasks[i].title);
                  //   printf("Description: %s\n", tasks[i].description);
                  //   printf("Deadline: %s\n", tasks[i].deadline);
                  //   printf("Status: ");
                  //   switch (tasks[i].status)
                  //   {
                  //   case TO_DO:
                  //       printf("To-Do\n");
                  //       break;
                  //   case DOING:
                  //       printf("Doing\n");
                  //       break;
                  //   case DONE:
                  //       printf("Done\n");
                  //       break;
                  //   }
                  //   break;
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
              char taskTitleLower[50];                // Make a lowercase copy of the task title
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
                  printf("\n\n");
                  printf("------------------------------------------------------------------------\n");
                  printf("ID: %d\n\n", tasks[i].id);
                  printf("------------------------------------------------------------------------\n");
                  printf("Title: %s\n\n", tasks[i].title);
                  printf("------------------------------------------------------------------------\n");
                  printf("Description: %s\n", tasks[i].description);
                  printf("------------------------------------------------------------------------\n");
                  printf("Deadline: %d-%d-%d\n",
                         tasks[i].deadline.day,
                         tasks[i].deadline.month,
                         tasks[i].deadline.year

                  );
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
                  //   printf("ID: %d\n", tasks[i].id);
                  //   printf("Title: %s\n", tasks[i].title);
                  //   printf("Description: %s\n", tasks[i].description);
                  //   printf("Deadline: %s\n", tasks[i].deadline);
                  //   printf("Status: ");
                  //   switch (tasks[i].status)
                  //   {
                  //   case TO_DO:
                  //       printf("To-Do\n");
                  //       break;
                  //   case DOING:
                  //       printf("Doing\n");
                  //       break;
                  //   case DONE:
                  //       printf("Done\n");
                  //       break;
              }
          }
          if (!found)
          {
              printf("No tasks with the title \"%s\" found.\n", searchTitle);
          }
      }

      void sortingMenu()
      {

          int keySorting;

          do
          {

              printf("________________________________________\n");
              printf("1.Sorting by Alpha\n");
              printf("2.Sorting By Deadline\n");
              printf("3.Sorting By Task Deadline End Soon\n");
              printf("0.BACK\n");
              printf("________________________________________\n");
              printf("Enter Your Choice: ");
              scanf("%d", &keySorting);

              switch (keySorting)
              {
              case 1:
                  sortingByAlpha();

                  break;
              case 2:
                  sortingByDeadline();

                  break;
              case 3:
                  tasksDeadlineEndSoon();
              }
              printf("\n");

          } while (keySorting != 0);
      }

      void sortingByAlpha()
      {

          struct TODO taskStorted[length]; // create new array to stock main array

          if (length == 0)
              printf("\nThere is no Tasks ");

          else

              // stock all array to new one
              for (int i = 0; i < length; i++)
              {
                  taskStorted[i] = tasks[i];
              }

          // https://youtu.be/LZNxRSoEG2M
          //  sorting array useing selection sort - deadline days
          for (int i = 0; i < length - 1; i++)
          {
              int taskMin = i;
              for (int j = 0; j < length - i; j++)
              {
                  if (strcmp(taskStorted[j].title, taskStorted[taskMin].title) < 0)
                  { // strcmp return < 0 if first title lewer then secend tile
                      taskMin = j;

                      if (taskMin != i)
                      {
                          struct TODO temp = taskStorted[i];
                          taskStorted[i] = taskStorted[taskMin];
                          taskStorted[taskMin] = temp;
                      }
                  }
              }
          }

          // Print the sorted array
          printf("Sorted tasks by title:\n");
          for (int i = 0; i < length; i++)
          {
              printf("------------------------------------------------------------------------\n");
              printf("Task %d:\n", taskStorted[i].id);
              printf("------------------------------------------------------------------------\n");
              printf("Title: %s\n", taskStorted[i].title);
              printf("------------------------------------------------------------------------\n");
              printf("Description: %s\n", taskStorted[i].description);
              printf("------------------------------------------------------------------------\n");
              printf("Deadline: %d\n", taskStorted[i].deadline);
              printf("------------------------------------------------------------------------\n");
              printf("Status: %d\n", taskStorted[i].status);
              printf("------------------------------------------------------------------------\n");
              printf("\n");
          }
      }

      // Function to calculate the number of days remaining until a given date
      int daysRemaining(struct Deadline deadline)
      {
          // is type come from library time (long int)
          time_t now; // declare variabl
          struct tm futureTime;

          // Get the current time
          time(&now);

          // Set the future time to the task's deadline
          futureTime.tm_year = deadline.year - 1900; // Years since 1900
          futureTime.tm_mon = deadline.month - 1;    // Months are 0-based
          futureTime.tm_mday = deadline.day;
          futureTime.tm_hour = 0;
          futureTime.tm_min = 0;
          futureTime.tm_sec = 0;

          // Convert both times to time_t
          time_t future = mktime(&futureTime);

          // Calculate the difference between two times in seconds
          double diff = difftime(future, now);

          // Convert seconds to days
          int days = (int)(diff / (60 * 60 * 24));

          return days;
      }

      void sortingByDeadline()
      {

          struct TODO taskStorted[length]; // create new array to stock main array

          if (length == 0)
              printf("No Tasks to Display ");

          else
          {

              // stock all array to new one
              for (int i = 0; i < length; i++)
              {
                  taskStorted[i] = tasks[i];
              }

              // sorting array useing bubble sort - deadline days
              for (int i = 0; i < length - 1; i++)
              {
                  for (int j = 0; j < length - i - 1; j++)
                  {
                      if (daysRemaining(taskStorted[j].deadline) > daysRemaining(taskStorted[j + 1].deadline))
                      {
                          struct TODO temp = taskStorted[j];
                          taskStorted[j] = taskStorted[j + 1];
                          taskStorted[j + 1] = temp;
                      }
                  }
              }

              // Display sorted tasks

              printf("Sorted tasks by deadline:\n");
              for (int i = 0; i < length; i++)
              {
                  ;
                  printf("------------------------------------------------------------------------\n");
                  printf("ID: %d\n", taskStorted[i].id);
                  printf("------------------------------------------------------------------------\n");
                  printf("Title: %s\n", taskStorted[i].title);
                  printf("------------------------------------------------------------------------\n");

                  printf("Deadline: %d-%d-%d\n",
                         taskStorted[i].deadline.day,
                         taskStorted[i].deadline.month,
                         taskStorted[i].deadline.year);
                  printf("------------------------------------------------------------------------\n");
              }
          }
      }

      void displayStatistics()
      {
          int completedTasks = 0;
          int incompleteTasks = 0;

          for (int i = 0; i < length; i++)
          {
              if (tasks[i].status == DONE)
              {
                  completedTasks++;
              }
              else
              {
                  incompleteTasks++;
              }
          }

          // Print the counts
          printf("------------------------------------------------------------------------\n");
          printf("Number of all tasks: %d\n", length);
          printf("------------------------------------------------------------------------\n");
          printf("Number of completed tasks: %d\n", completedTasks);
          printf("------------------------------------------------------------------------\n");
          printf("Number of incomplete tasks: %d\n", incompleteTasks);
          printf("------------------------------------------------------------------------\n");

          for (int i = 0; i < length; i++)
          {
              int days = daysRemaining(tasks[i].deadline);

              if (days >= 0)
              {
                  printf("ID : %d\n", tasks[i].id);
                  printf("------------------------------------------------------------------------\n");
                  printf("Days remaining : %d\n", days);
                  printf("------------------------------------------------------------------------\n");
              }
          }
      }

      void tasksDeadlineEndSoon()
      {

          if (length <= 0)
              printf("No Tasks to Display ");

          else
              printf("Task Deadline End Soon : ");

          for (int i = 0; i < length; i++)
          {
              int days = daysRemaining(tasks[i].deadline);

              if (days >= 0 && days <= 3)
              {
                  printf("\n\n");
                  printf("------------------------------------------------------------------------\n");
                  printf("ID: %d\n\n", tasks[i].id);
                  printf("------------------------------------------------------------------------\n");
                  printf("Title: %s\n\n", tasks[i].title);
                  printf("------------------------------------------------------------------------\n");
                  printf("Description: %s\n", tasks[i].description);
                  printf("------------------------------------------------------------------------\n");
                  printf("Deadline: %d-%d-%d\n",
                         tasks[i].deadline.day,
                         tasks[i].deadline.month,
                         tasks[i].deadline.year

                  );
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

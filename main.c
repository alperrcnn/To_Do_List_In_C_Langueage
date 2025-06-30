#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TASKS 100
#define MAX_LENGTH 100
#define FILENAME "tasks.txt"

typedef struct {
    char description[MAX_LENGTH];
    int completed; // 0: hasnt completed, 1: completed
} Task;

void list(Task tasks[], int count) {
    if (count == 0) {
        printf("No task found.\n");
        return;
    }
    printf("     Tasks    \n");
    for (int i = 0; i < count; i++) {
        printf("%d. [%c] %s\n", i + 1, tasks[i].completed ? 'X' : ' ', tasks[i].description);
    }
}

int loadTasks(Task tasks[]) {
    FILE *fp = fopen(FILENAME, "r");
    if (!fp)
        return 0;

    int count = 0;
    while (count < MAX_TASKS && fscanf(fp, "%d %[^\n]", &tasks[count].completed, tasks[count].description) == 2) {
        count++;
    }
    fclose(fp);
    return count;
}

void saveTasks(Task tasks[], int count) {
    FILE *fp = fopen(FILENAME, "w");
    if (!fp) {
        printf("Couldn't save the file!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s\n", tasks[i].completed, tasks[i].description);
    }
    fclose(fp);
}

int main() {
    Task tasks[MAX_TASKS];
    int taskCount = loadTasks(tasks);
    int choice;
    char buffer[MAX_LENGTH];

    while (1) {
        system("cls");  // Clear the screen

        printf("To-Do List Menu:\n\n");
        printf("1. Add new task\n");
        printf("2. List the Tasks\n");
        printf("3. Delete a task\n");
        printf("4. Change the status of the task\n");
        printf("5. Exit\n\n");
        printf("Your Choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Gecersiz giris!\n");
            while(getchar() != '\n'); // buffer temizle
            printf("Devam etmek icin bir tusa basin...");
            getchar();
            continue;
        }

    getchar(); // clean the buffer

        switch (choice) {
            case 1:
                if (taskCount == MAX_TASKS) {
                    printf("No space in the task list!\n");
        }   else {
                    system("cls");
                    printf("New task: ");
                    if (fgets(buffer, MAX_LENGTH, stdin) == NULL) {
                        printf("Error.\n");
                        break;
                    }

                    buffer[strcspn(buffer, "\n")] = 0;
                    strcpy(tasks[taskCount].description, buffer);
                    tasks[taskCount].completed = 0;
                    taskCount++;
                    saveTasks(tasks, taskCount);
                    printf("Task has been added.\n");
                }
                break;

            case 2:
                system("cls");
                list(tasks, taskCount);
                break;

            case 3:
                system("cls");
                if (taskCount == 0) {
                    printf("No task to delete.\n");
            }    else {
                    list(tasks, taskCount);
                    printf("Which task you want to delete?: ");
                    int Delete;
                    if (scanf("%d", &Delete) != 1) {
                        printf("Invalid choice.\n");
                        while(getchar() != '\n');
                        break;
                    }

            getchar();

                    if ( Delete < 1 || Delete > taskCount) {
                        printf("Invalid task number.\n");
                    } else {
                        for (int i = Delete - 1; i < taskCount - 1; i++) {
                            tasks[i] = tasks[i + 1];
                        }
                        taskCount--;
                        saveTasks(tasks, taskCount);
                        printf("Task has been deleted.\n");
                    }
                }
                break;

            case 4:
                system("cls");
                if (taskCount == 0) {
                    printf("No task found.\n");
                } else {
                    list(tasks, taskCount);
                    printf("Choose a task to change their status: ");
                    int idx;

                        if (scanf("%d", &idx) != 1) {
                            printf("Invalid choice.\n");
                            while(getchar() != '\n');
                            break;
                    }

                    getchar();
                    if (idx < 1 || idx > taskCount) {
                        printf("Invalid task number.\n");
                    } else {
                        tasks[idx - 1].completed = !tasks[idx - 1].completed;
                        saveTasks(tasks, taskCount);
                        printf("Task status has been changed.\n");
                    }
                }

                break;

            case 5:
                system("cls");
                printf("Exiting the program...\n");
                return 0;

            default:
                printf("Invalid choice, try something else.\n");
        }
        printf("\nPress any key to get back to menu...");
        getchar();
    }
}

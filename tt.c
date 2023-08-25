#include <stdio.h>
#include <time.h>
#include <string.h>

struct Task {
    char name[100];
    time_t start;
    time_t end;
};

void startTask(struct Task *task, const char *name) {
    strncpy(task->name, name, sizeof(task->name) - 1);
    task->start = time(NULL);
}

void endTask(struct Task *task) {
    task->end = time(NULL);
}

void logTask(struct Task *task) {
    FILE *file = fopen("task_log.txt", "a");
    if (!file) {
        fprintf(stderr, "Couldn't open the file.\n");
        return;
    }
    fprintf(file, "Task: %s\n", task->name);
    fprintf(file, "Start Time: %s", ctime(&task->start));
    fprintf(file, "End Time: %s", ctime(&task->end));
    fprintf(file, "Duration: %ld seconds\n\n", task->end - task->start);
    fclose(file);
}

int main() {
    struct Task myTask;
    char taskName[100];

    printf("Enter the task name: ");
    fgets(taskName, sizeof(taskName), stdin);
    strtok(taskName, "\n"); // Remove newline character

    startTask(&myTask, taskName);

    printf("Press enter when the task is complete...\n");
    getchar();

    endTask(&myTask);
    logTask(&myTask);

    printf("Logged the task.\n");

    return 0;
}

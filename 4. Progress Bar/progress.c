#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

const int BAR_LENGTH = 50;
const int MAX_TASK = 5;

typedef struct
{
    int id;
    int progress;
    int step;
} Task;

void printProgressBar(Task);
void clear_screen();

int main()
{
    Task task[MAX_TASK];
    srand(time(NULL));

    for (int i = 0; i < MAX_TASK; i++)
    {
        task[i].id = i + 1;
        task[i].progress = 0;
        task[i].step = rand() % 5 + 1;
    }

    int incompleteBar = 1;
    while (incompleteBar)
    {
        incompleteBar = 0;

        clear_screen();
        for (int i = 0; i < MAX_TASK; i++)
        {
            task[i].progress += task[i].step;
            if (task[i].progress < 100)
            {
                incompleteBar = 1;
            }
            else if (task[i].progress > 100)
            {
                task[i].progress = 100;
            }
            printProgressBar(task[i]);
        }
        sleep(1);
    }
    printf("All tasks completed!\n");

    return 0;
}

void printProgressBar(Task task)
{
    int bar_to_show = (task.progress * BAR_LENGTH) / 100;
    printf("Task %d: [", task.id);
    for (int i = 0; i < BAR_LENGTH; i++)
    {
        if (i < bar_to_show)
        {
            printf("=");
        }
        else
        {
            printf(" ");
        }
    }
    printf("]");
    printf(" %d%%\n\n", task.progress);
}

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
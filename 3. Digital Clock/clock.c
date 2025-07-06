#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void fillTime(char *, int);
void fillDate(char *);
void clear_screen();
int inputFormatChoice();
int main()
{
    char time[50], date[100];
    int formatChoice = inputFormatChoice();
    while (1)
    {
        fillTime(time, formatChoice);
        fillDate(date);
        clear_screen();
        printf("----------------------------\n");
        printf("Current Time : %s", time);
        printf("\nCurrent Date : %s", date);
        printf("\n----------------------------\n");
        sleep(1);
    }
    return 0;
}

int inputFormatChoice()
{
    int formatChoice;
    printf("----------------------------\n");
    printf("Welcome to the Digital Clock\n");
    printf("Choose the Time Format : \n");
    printf("1. 24 Hour format\n");
    printf("2. 12 Hour format (default)\n");
    printf("Make a Choice (1/2) : ");
    scanf("%d", &formatChoice);
    return formatChoice;
}

void fillTime(char *buffer, int formatChoice)
{
    time_t raw_time;
    struct tm *current_time;

    time(&raw_time);

    current_time = localtime(&raw_time);

    if (formatChoice == 1)
    {
        strftime(buffer, 50, "%H:%M:%S", current_time);
    }
    else
    {
        strftime(buffer, 50, "%I:%M:%S %p", current_time);
    }
}

void fillDate(char *buffer)
{
    time_t raw_date;
    struct tm *current_date;

    time(&raw_date);

    current_date = localtime(&raw_date);

    strftime(buffer, 100, "%A %d/%B/%Y", current_date);
}

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
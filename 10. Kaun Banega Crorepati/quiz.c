#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

#define MAX_QUES_LEN 300
#define MAX_OPTION_LEN 50
volatile int timeout_happened = 0;

const char *COLOR_END = "\033[0m";
const char *COLOR_RED = "\033[31m";
const char *COLOR_GREEN = "\033[32m";
const char *COLOR_YELLOW = "\033[33m";
const char *COLOR_BLUE = "\033[34m";
const char *COLOR_MAGENTA = "\033[35m";
const char *COLOR_PINK = "\033[1;35m";
const char *COLOR_CYAN = "\033[36m";
const char *COLOR_AQUA = "\033[1;36m";

typedef struct
{
    char text[MAX_QUES_LEN];
    char option[4][MAX_OPTION_LEN];
    char correct_option;
    int timeout;
    int prize_money;
} Question;

int read_questions(char *file_name, Question **questions);
void print_formatted_question(Question question);
void play_game(Question *questions, int no_of_questions);
int use_lifeline(Question *questions, int *lifeline);

int main()
{
    printf("-----------------------------------------------\n");
    srand(time(NULL)); // Seed for random number generation
    printf("\t\t%sWelcome to the Kaun Banega Crorepati Quiz!%s\t\t\n", COLOR_PINK, COLOR_END);
    Question *questions;
    int no_of_questions = read_questions("questions.txt", &questions);
    play_game(questions, no_of_questions);
    free(questions);
    return 0;
}
void timeout_handler()
{
    timeout_happened = 1; // Set the flag to indicate timeout
    printf("%s\nTime's up! You didn't answer in time.%s\n", COLOR_RED, COLOR_END);
    fflush(stdout); // Ensure the message is printed immediately
}

int wait_for_input(int timeout_seconds)
{
    time_t start = time(NULL);
    while (difftime(time(NULL), start) < timeout_seconds)
    {
        if (kbhit())
        {
            return getch(); // Return key if pressed
        }
    }
    return -1; // Timeout occurred
}

void play_game(Question *questions, int no_of_questions)
{
    int score = 0;
    int lifeline[] = {1, 1}; // Array to hold lifeline status, 1 means available

    for (int i = 0; i < no_of_questions; i++)
    {
        print_formatted_question(questions[i]);
        char answer;
        int timeout = wait_for_input(questions[i].timeout);
        if (timeout != -1)
        {
            answer = toupper(timeout); // Wait for user input with timeout
        }
        else
        {
            printf("\n%sTime's up! You didn't answer in time.%s\n", COLOR_RED, COLOR_END);
            break; // Exit the loop if time is up
        }
        answer = toupper(answer); // Convert to uppercase for consistency
        if (answer == questions[i].correct_option)
        {
            printf("\n%sCorrect! You win Rs. %d%s\n", COLOR_GREEN, questions[i].prize_money, COLOR_END);
            score += questions[i].prize_money;
            printf("%sYou are ready for the next question of Rs. %d...%s\n", COLOR_PINK, questions[i + 1].prize_money, COLOR_END);
        }
        else if (answer == 'L')
        {
            int value = use_lifeline(&questions[i], lifeline);
            if (value != 2)
            {
                i--;
            }
            continue;
        }
        else
        {
            printf("\n%sWrong answer! The correct answer was %c.%s\n", COLOR_RED, questions[i].correct_option, COLOR_END);
            break;
        }
    }
    printf("%sGame over! Your total score is: Rs. %d%s\n", COLOR_BLUE, score, COLOR_END);
}

int use_lifeline(Question *questions, int *lifeline)
{
    printf("\n%sYou have the following lifelines available:%s\n", COLOR_PINK, COLOR_END);
    if (lifeline[0])
    {
        printf("%s1. 50-50 Lifeline%s\n", COLOR_CYAN, COLOR_END);
    }
    if (lifeline[1])
    {
        printf("%s2. Skip the question%s\n", COLOR_CYAN, COLOR_END);
    }
    printf("%sChoose a lifeline or 0 to return: %s", COLOR_CYAN, COLOR_END);
    char lifeline_number;
    lifeline_number = getch();       // Get user input for lifeline choice
    printf("%c\n", lifeline_number); // Print the pressed key for visibility
    switch (lifeline_number)
    {
    case '1':
        if (lifeline[0])
        {
            lifeline[0] = 0;
            int removed = 0;
            while (removed < 2)
            {
                int num = rand() % 4;
                if ((num + 'A') != questions->correct_option &&
                    questions->option[num][0] != '\0')
                {
                    questions->option[num][0] = '\0';
                    removed++;
                }
            }
            return 1;
        }
        break;
    case '2':
        if (lifeline[1])
        {
            lifeline[1] = 0;
            return 2;
        }
        break;
    default:
        printf("\n%sReturning to the Question.%s", COLOR_PINK, COLOR_END);
        break;
    }
}

void print_formatted_question(Question question)
{
    printf("\n%s%s%s\n", COLOR_YELLOW, question.text, COLOR_END);

    for (int i = 0; i < 4; i++)
    {
        if (question.option[i][0] == '\0')
        {
            continue;
        }
        printf("%s%c. %s%s\n", COLOR_AQUA, 'A' + i, question.option[i], COLOR_END);
    }

    printf("%sHurry up! You have %d seconds to answer this question.%s\n", COLOR_RED, question.timeout, COLOR_END);
    printf("%sEnter your answer (A, B, C, or D) or L for Lifeline: %s", COLOR_CYAN, COLOR_END);
}
int read_questions(char *file_name, Question **questions)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("Unable to open the questions bank.\n");
        exit(0);
    }

    char str[MAX_QUES_LEN];
    int no_of_lines = 0;
    while (fgets(str, MAX_QUES_LEN, file))
    {
        no_of_lines++;
    }

    int no_of_questions = no_of_lines / 8;

    *questions = (Question *)malloc(no_of_questions * sizeof(Question));

    rewind(file);

    for (int i = 0; i < no_of_questions; i++)
    {
        fgets((*questions)[i].text, MAX_QUES_LEN, file);
        (*questions)[i].text[strcspn((*questions)[i].text, "\n")] = 0; // Remove newline

        for (int j = 0; j < 4; j++)
        {
            fgets((*questions)[i].option[j], MAX_OPTION_LEN, file);
            (*questions)[i].option[j][strcspn((*questions)[i].option[j], "\n")] = 0; // Remove newline
        }

        char option[10];
        fgets(option, 10, file);
        (*questions)[i].correct_option = option[0];

        char timeout[10];
        fgets(timeout, 10, file);
        (*questions)[i].timeout = atoi(timeout);

        char prize_money[10];
        fgets(prize_money, 10, file);
        (*questions)[i].prize_money = atoi(prize_money);
    }
    fclose(file);
    return no_of_questions;
}
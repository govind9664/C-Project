#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int random_number;
    int guess;
    int num_of_guesses = 0;
    // int guess_limit = 3;
    printf("Welcome to the World Guessing Number Game\n");
    srand(time(NULL));
    random_number = rand() % 100 + 1;

    do
    {

        printf("\nPlease enter your guess number between 1 and 10: ");
        scanf("%d", &guess);
        num_of_guesses++;

        if (guess > random_number)
        {
            printf("Guess a smaller number.\n");
        }
        else if (guess < random_number)
        {
            printf("Guess a larger number.\n");
        }
        else
        {
            printf("--------------------------------------------------------------------------\n");
            printf("Congratulations !!! You have successfully guessed the number in %d guesses!\n", num_of_guesses);
        }

    } while (random_number != guess);

    printf("\nBye Bye,Thanks for Playing the game.\n");
    printf("\nDeveloped by Govind Rai.\n");
}
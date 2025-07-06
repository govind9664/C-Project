#include <stdio.h>
#include <math.h>

void printMenu();
double division(double, double);
double modulus(int, int);
int main()
{
    int choice;

    double firstNum, secondNum, result;

    while (1)
    {
        printMenu();
        printf("\nEnter your choice : ");
        scanf("%d", &choice);

        if (choice < 0 || choice > 7)
        {
            fprintf(stderr, "Invalid Menu Choice. Please try again!\n");
            continue;
        }

        if (choice == 7)
        {
            break;
        }
        printf("Please enter the first number : ");
        scanf("%lf", &firstNum);
        printf("Now, enter the second number : ");
        scanf("%lf", &secondNum);

        switch (choice)
        {
        case 1:
            result = firstNum + secondNum;
            break;
        case 2:
            result = firstNum - secondNum;
            break;
        case 3:
            result = firstNum * secondNum;
            break;
        case 4:
            result = division(firstNum, secondNum);
            break;
        case 5:
            result = modulus(firstNum, secondNum);
            break;
        case 6:
            result = pow(firstNum, secondNum);
            break;
        default:
            break;
        }
        if (!isnan(result))
        {
            printf("\n----------------------------------------");
            printf("\nResult of opteration is  : %.2lf", result);
        }
    }

    return 0;
}

double division(double a, double b)
{
    if (b == 0)
    {
        fprintf(stderr, "Invalid argument for Division\n");
        return NAN;
    }
    else
    {
        return a / b;
    }
}

double modulus(int a, int b)
{
    if (b == 0)
    {
        fprintf(stderr, "Invalid argument for Modulus\n");
        return NAN;
    }
    else
    {
        return a % b;
    }
}

void printMenu()
{
    printf("\n\n-----------------------------------------");
    printf("\nWelcome to the Simple Calculator\n");
    printf("\nChoose one of the following options : ");
    printf("\n1. Addition");
    printf("\n2. Substraction");
    printf("\n3. Multiplication");
    printf("\n4. Substraction");
    printf("\n5. Modulus");
    printf("\n6. Power");
    printf("\n7. Exit");
}
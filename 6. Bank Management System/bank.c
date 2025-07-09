#include <stdio.h>
#include <string.h>

void printMenu();
void create_account();
void deposite_money();
void withdraw_money();
void check_balance();
void fix_fgets_input(char *);

typedef struct
{
    char name[50];
    int accountNumber;
    float balance;
} Account;

int main()
{
    int choice;
    while (1)
    {
        printMenu();
        printf("Enter your choice : ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            create_account();
            break;
        case 2:
            deposite_money();
            break;
        case 3:
            withdraw_money();
            break;
        case 4:
            check_balance();
            break;
        case 5:
            printf("\nClosing the Bank, Thanks for your visit...");
            return 0;

        default:
            printf("\nInvalid choice!!! Please try again.\n");
            break;
        }
    }

    return 0;
}

void printMenu()
{
    printf("\n\n*********** Bank Management System ***********\n");
    printf("1. Create Account\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Check Balance\n");
    printf("5. Exit\n");
}

void create_account()
{
    Account account;

    FILE *file = fopen("account.dat", "ab+");
    if (file == NULL)
    {
        printf("Unable to open account file!\n");
        return;
    }

    printf("Enter your name : ");
    fgets(account.name, sizeof(account.name), stdin);
    fix_fgets_input(account.name);
    printf("Enter your account number : ");
    scanf("%d", &account.accountNumber);
    account.balance = 0;

    fwrite(&account, sizeof(account), 1, file);
    fclose(file);
    printf("-----------------------------------\n");
    printf("Account Created Successfully...\n");
}
void deposite_money()
{
    FILE *file = fopen("account.dat", "rb+");
    if (file == NULL)
    {
        printf("Unable to open account file!\n");
        return;
    }
    Account acc_read;
    int acc_no;
    float amount;
    printf("Enter your account number : ");
    scanf("%d", &acc_no);
    printf("Enter your amount to deposit : ");
    scanf("%f", &amount);

    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.accountNumber == acc_no)
        {
            acc_read.balance += amount;

            fseek(file, -(long)sizeof(acc_read), SEEK_CUR);
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            printf("-----------------------------------\n");
            printf("Successfully deposited Rs. %.2f \nNow your current balance is Rs. %.2f\n", amount, acc_read.balance);
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("-----------------------------------\n");
    printf("Money could not be deposited as the Account No. %d was not found in the Record.\n", acc_no);
}
void withdraw_money()
{
    FILE *file = fopen("account.dat", "rb+");
    if (file == NULL)
    {
        printf("Unable to open account file!\n");
        return;
    }

    int acc_no;
    float amount;
    Account acc_read;
    printf("Enter your account number : ");
    scanf("%d", &acc_no);
    printf("Enter your amount to withdraw : ");
    scanf("%f", &amount);

    while (fread(&acc_read, sizeof(acc_read), 1, file)) // Read each account from the file until the EOF is reached
    {
        if (acc_read.accountNumber == acc_no)
        {
            if (acc_read.balance >= amount)
            {
                acc_read.balance -= amount;

                fseek(file, -(long)sizeof(acc_read), SEEK_CUR); // Move the file pointer back to the position of the current account
                // and update the account balance
                fwrite(&acc_read, sizeof(acc_read), 1, file);
                printf("-----------------------------------\n");
                printf("Successfully withdrawn Rs. %.2f \nNow your current balance is Rs. %.2f\n", amount, acc_read.balance);
                fclose(file);
                return;
            }
            else
            {
                printf("-----------------------------------\n");
                printf("Insufficient balance to withdraw Rs. %.2f\n", amount);
                fclose(file);
                return;
            }
        }
    }
    fclose(file);
    printf("-----------------------------------\n");
    printf("Money could not be withdrawn as the Account No. %d was not found in the Record.\n", acc_no);
}
void check_balance()
{
    FILE *file = fopen("account.dat", "rb");
    if (file == NULL)
    {
        printf("Unable to open account file!\n");
        return;
    }

    int acc_number;
    Account acc_read;
    printf("Enter your account number : ");
    scanf("%d", &acc_number);

    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.accountNumber == acc_number)
        {
            printf("-----------------------------------\n");
            printf("Your current balance is : Rs. %.2f", acc_read.balance);
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("-----------------------------------\n");
    printf("Account No. %d was not found.\n", acc_number);
}

void fix_fgets_input(char *name)
{
    int index = strcspn(name, "\n");
    name[index] = '\0';
}
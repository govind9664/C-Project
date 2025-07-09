#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

#define MAX_USERS 10

#define CREDENTIAL_LENGTH 30

void register_user();
int login_user(); // Return user index if existing
void fix_fgets_input(char *);
void input_credentials(char *, char *);
void getUserDetails();
void breakStatement();

typedef struct
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
} User;

User users[MAX_USERS];

int user_count = 0;
int main()
{
    int user_index;
    int option;

    while (1)
    {
        printf("---------------------------------------\n");
        printf("Welcome to the User Management System\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Details of Users\n");
        printf("4. Exit\n");
        printf("Select an Option : ");
        scanf("%d", &option);
        getchar(); // Consume extra "\n" from scanf

        switch (option)
        {
        case 1:
            register_user();
            break;
        case 2:
            user_index = login_user();
            if (user_index >= 0)
            {
                printf("\nLogin Successfully ! Hi %s, Welcome  to the Project World\n", users[user_index].username);
            }
            else
            {
                printf("%s %s", users[user_index].username, users[user_index].password);
                printf("\nLogin failed! Incorrect username or password.\n");
            }
            break;
        case 3:
            getUserDetails();
            break;
        case 4:
            printf("\nExiting Program!\n");
            return 0;

        default:
            printf("Invalid option . Please try again!");
            break;
        }
    }

    return 0;
}

void register_user()
{
    if (user_count == MAX_USERS)
    {
        printf("\nMaximum %d user are supported! No more registrations Allowed!!!\n", MAX_USERS);
        return;
    }
    int index = user_count;
    printf("Register a new user\n");
    input_credentials(users[index].username, users[index].password);
    user_count++;
    printf("\nRegistration successful!\n");
    printf("---------------------------------------\n");
}

void input_credentials(char *username, char *password)
{
    printf("Enter username : ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(username);
    printf("Enter Password (masking enable) : ");

    // Generate password
    int i = 0;
    char ch;

    while (1)
    {
        ch = getch();
        // Possible Reason: getch() is Acting Weird in Your Terminal
        //  Depending on your terminal or environment (e.g., Windows Terminal, MSYS2 shell, or Git Bash),
        //   Enter key might send two characters:
        //  1. Carriage Return (\r, ASCII 13)
        //  2. Line Feed (\n, ASCII 10)

        // Handle this problem
        // The first getch() reads 13 (triggering the break),
        // But your loop runs one more time
        // and getch() reads 10 the next time.
        if (ch == 13 || ch == 10) // Handle both \r and \n
        {                         // ASCII value of enter
            password[i] = '\0';
            // breakStatement();
            break;
        }
        else if (ch == 8)
        { // ASCII value of backspace
            if (i > 0)
            {
                printf("\b \b"); // backspace and erase
                i--;
            }
        }
        else
        {
            printf("*");
            password[i] = ch;
            i++;
        }
    }
    // fgets(password, CREDENTIAL_LENGTH, stdin);

    fix_fgets_input(password);
}
void fix_fgets_input(char *username)
{
    int index = strcspn(username, "\n");
    username[index] = '\0';
}

int login_user()
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
    input_credentials(username, password);
    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            return i;
        }
    }
    return -1;
}

void getUserDetails()
{
    printf("User Details\n");
    for (int i = 0; i < user_count; i++)
    {
        printf("%s : %s", users[i].username, users[i].password);
        printf("\n");
    }
}
void breakStatement()
{
    printf("\nBreak statement called\n");
}
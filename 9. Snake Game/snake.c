#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define WIDTH 60
#define HEIGHT 20

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP
};
int tail_length;
int tail_x[100], tail_y[100]; // Arrays to store tail positions

enum Direction current_direction = STOP; // Initial direction
void clear_screen();
void draw();
void setup();
void input();
void game_play();
void hide_cursor();
void gotoxy(int x, int y);

int fruit_x = 10, fruit_y = 12;
int head_x = 15, head_y = 5;
int score = 0;

int main()
{
    srand(time(NULL)); // Seed the random number generator
    setup();
    while (1)
    {
        draw();
        input();
        game_play();
        int sleep_time = 1000 / (score != 0 ? score / 5 : 5); // Adjust the sleep time to control game speed
        Sleep(sleep_time);                                    // Sleep for a short duration to control game speed
    }
    exit(0);
}

void game_play()
{

    // Update the tail positions
    for (int i = tail_length - 1; i > 0; i--)
    {
        tail_x[i] = tail_x[i - 1];
        tail_y[i] = tail_y[i - 1];
    }
    tail_x[0] = head_x; // Update the head position in the tail
    tail_y[0] = head_y;

    // Move the snake
    switch (current_direction)
    {
    case UP:
        head_y--; // Move up
        break;
    case DOWN:
        head_y++; // Move down
        break;
    case LEFT:
        head_x--; // Move left
        break;
    case RIGHT:
        head_x++; // Move right
        break;
    case STOP:
        // Do nothing, game is stopped
        break;
    }

    if (head_x < 0)
    {
        head_x = WIDTH - 1;
    }
    else if (head_x >= WIDTH)
    {
        head_x = 0;
    }
    if (head_y < 0)
    {
        head_y = HEIGHT - 1;
    }
    else if (head_y >= HEIGHT)
    {
        head_y = 0;
    }

    // Check for collision with the tail
    for (int i = 0; i < tail_length; i++)
    {
        if (tail_x[i] == head_x && tail_y[i] == head_y)

        {
            printf("-------------------------------\n");
            printf("Game Over! You ate yourself!\n");
            printf("Your score was: %d\n", score);
            printf("-------------------------------\n");
            exit(0); // Prevent the snake from eating itself
        }
    }

    if (head_x == fruit_x && head_y == fruit_y)
    {
        score += 10;               // Increase score when snake eats the fruit
        tail_length++;             // Increase the length of the snake
        fruit_x = rand() % WIDTH;  // Random new fruit position
        fruit_y = rand() % HEIGHT; // Random new fruit position
    }
}

void input()
{
    if (kbhit())
    {
        char ch = getch(); // Read character without echo
        switch (ch)
        {
        case 'w':
            current_direction = UP;
            break;
        case 's':
            current_direction = DOWN;
            break;
        case 'a':
            current_direction = LEFT;
            break;
        case 'd':
            current_direction = RIGHT;
            break;
        case 'x':
            current_direction = STOP;
            break;
        }
    }
}

void setup()
{
    head_x = WIDTH / 2;  // Center the snake head
    head_y = HEIGHT / 2; // Center the snake head

    fruit_x = rand() % WIDTH;  // Random fruit position
    fruit_y = rand() % HEIGHT; // Random fruit position
    hide_cursor();
}

void draw()
{
    gotoxy(0, 0); // Move cursor to the top-left corner

    printf("---------------Welcome to the Snake Game!---------------\n");
    // Game drawing logic goes here
    for (int i = 0; i < WIDTH + 2; i++)
    {
        printf("#");
    }
    printf("\n");
    for (int i = 0; i < HEIGHT; i++)
    {
        printf("#");
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == head_y && j == head_x)
            {
                printf("O"); // Snake head
            }
            else if (i == fruit_y && j == fruit_x)
            {
                printf("*"); // Fruit
            }
            else
            {
                int tail_found = 0;
                for (int k = 0; k < tail_length; k++)
                {
                    if (tail_x[k] == j && tail_y[k] == i)
                    {
                        printf("o"); // Snake body
                        tail_found = 1;
                        break;
                    }
                }
                if (!tail_found)
                {
                    printf(" "); // Empty space
                }
            }
        }
        printf("#\n");
    }
    for (int i = 0; i < WIDTH + 2; i++)
    {
        printf("#");
    }
    printf("\n");
    printf("Score : %d\n", score);
}
void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void gotoxy(int x, int y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void hide_cursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

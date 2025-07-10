#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 3
#define X 'X'
#define O 'O'
int difficulty_level;
void input_difficulty_level();
void clear_screen();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void play_game();
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);

typedef struct
{
    int playerWon;
    int computerWon;
    int draw;
} Score;

Score score = {.computerWon = 0, .playerWon = 0, .draw = 0};

int main()
{
    srand(time(NULL));
    int choice;
    input_difficulty_level();
    do
    {
        play_game();
        printf("Play again? (1 for yes , 0 for no) : ");
        scanf("%d", &choice);
    } while (choice == 1);

    printf("\nBye Bye , Thanks for playing game.");

    return 0;
}

void play_game()
{
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '},

    };
    char current_player = rand() % 2 == 0 ? X : O;
    // input_difficulty_level();

    print_board(board);

    while (1)
    {
        print_board(board);

        if (current_player == X)
        {
            player_move(board);
            print_board(board);

            if (check_win(board, X))
            {
                score.playerWon++;
                print_board(board);
                printf("\nCongratulation, you have won.!!!\n\n");
                break;
            }
            current_player = O;
        }
        else
        {
            computer_move(board);
            print_board(board);

            if (check_win(board, O))
            {
                score.computerWon++;
                print_board(board);

                printf("\nI won!, But you played well..\n\n");
                break;
            }
            current_player = X;
        }
        if (check_draw(board))
        {
            score.draw++;
            print_board(board);

            printf("\nIts a draw!\n\n");
            break;
        }
    }
}

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
    if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ')
    {
        return 0;
    }
    return 1;
}
void player_move(char board[BOARD_SIZE][BOARD_SIZE])
{
    int count = 0;
    int x = 0, y = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                count++;
                x = i;
                y = j;
            }
        }
    }

    if (count == 1)
    {
        board[x][y] = X;
        return;
    }

    int row, col;
    do
    {
        printf("Player X's turn.\n");
        printf("Enter row and  column (1-3) for X: ");
        scanf("%d", &row);
        scanf("%d", &col);

        row--, col--; // Convert to 0-based index
    } while (!is_valid_move(board, row, col));

    board[row][col] = X;
}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE])
{
    // Play for immediate win
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = O;
                if (check_win(board, O))
                {
                    return; // Computer wins
                }
                board[i][j] = ' '; // Undo move
            }
        }
    }

    // Block player from winning
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = X;
                if (check_win(board, X))
                {
                    board[i][j] = O; // Block player
                    return;
                }
                board[i][j] = ' '; // Undo move
            }
        }
    }

    // God mode
    if (difficulty_level == 2)
    {
        if (board[1][1] == ' ')
        {
            board[1][1] = O; // Take center if available
            return;
        }

        // Play corner if available
        int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
        for (int i = 0; i < 4; i++)
        {
            if (board[corners[i][0]][corners[i][1]] == ' ')
            {
                board[corners[i][0]][corners[i][1]] = O;
                return;
            }
        }
    }

    // Play first available move
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = O;
                return;
            }
        }
    }
}
void input_difficulty_level()
{
    while (1)
    {
        printf("\nWelcome to the Tic Toc Game\n");
        printf("Select Difficulty level: \n");
        printf("1. Human (Standard).\n");
        printf("2. God mode (Impossible to win).\n");
        printf("Enter your choice : ");
        scanf("%d", &difficulty_level);

        if (difficulty_level != 1 && difficulty_level != 2)
        {
            printf("Incorrect choice enter (1/2)\n");
        }
        else
        {
            break;
        }
    }
}

void clear_screen()
{
#ifdef _WIN32
    // For Windows systems, use cls command to clear the console
    system("cls");
#else
    system("clear");
#endif
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    clear_screen();
    printf("-------------------------------------------------\n");
    printf("Score - Player X : %d, Computer : %d, Draws : %d\n", score.playerWon, score.computerWon, score.draw);
    printf("-------------------------------------------------\n");
    printf("Tic Toc Toe: \n");

    for (int i = 0; i < 3; i++)
    {
        if (i != 0)
        {
            printf("---+---+---\n");
        }
        for (int j = 0; j < 3; j++)
        {
            if (j != 0)
            {
                printf(" |");
            }
            printf(" %c", board[i][j]);
        }
        printf("\n");
    }
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return 1;
        }
    }
    for (int j = 0; j < 3; j++)
    {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
        {
            return 1;
        }
    }

    if (board[0][0] == player && board[1][1] == player && board[2][2] == player || board[0][2] == player && board[1][1] == player && board[2][0] == player)
    {
        return 1;
    }
    return 0;
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                return 0;
            }
        }
    }
    return 1;
}

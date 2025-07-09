#include <stdio.h>

int puzzle[9][9] = {
    {3, 0, 0, 0, 2, 0, 0, 7, 0},
    {9, 0, 0, 5, 0, 0, 0, 1, 4},
    {0, 1, 6, 3, 7, 0, 0, 0, 8},
    {2, 0, 0, 8, 0, 0, 0, 0, 1},
    {5, 0, 0, 0, 4, 1, 8, 0, 0},
    {0, 8, 9, 0, 0, 0, 0, 5, 0},
    {0, 0, 5, 0, 1, 0, 2, 8, 0},
    {0, 4, 0, 0, 0, 6, 0, 9, 3},
    {7, 3, 1, 0, 8, 2, 0, 0, 0},
};

void print_puzzle(int puzzle[9][9]);
int check_valid_move(int puzzle[9][9], int row, int col, int num);
int solve_puzzle(int puzzle[9][9], int row, int col);

int main()
{
    printf("\nWelcome to the Sudoku Puzzle Game:\n");
    print_puzzle(puzzle);
    if (solve_puzzle(puzzle, 0, 0))
    {
        printf("Sudoku puzzle solved successfully:\n");
        print_puzzle(puzzle);
    }
    else
    {
        printf("No solution exists for the Sudoku puzzle.\n");
    }
    return 0;
}

void print_puzzle(int puzzle[9][9])
{
    for (int row = 0; row < 9; row++)
    {
        if (row % 3 == 0)
        {
            printf("+-------+-------+-------+\n");
        }
        for (int col = 0; col < 9; col++)
        {
            if (col % 3 == 0)
            {
                printf("| ");
            }
            if (puzzle[row][col] == 0)
            {
                printf(". ");
            }
            else
            {
                printf("%d ", puzzle[row][col]);
            }
        }
        printf("|");
        printf("\n");
    }
    printf("+-------+-------+-------+\n");
}

int check_valid_move(int puzzle[9][9], int row, int col, int num)
{
    // Check if the number is already in the same row, column, or 3x3 subgrid
    for (int i = 0; i < 9; i++)
    {
        if (puzzle[row][i] == num || puzzle[i][col] == num)
        {

            return 0; // Invalid move
        }
    }
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = startRow; i < startRow + 3; i++)
    {
        for (int j = startCol; j < startCol + 3; j++)
        {
            if (puzzle[i][j] == num)
            {
                return 0; // Invalid move
            }
        }
    }
    return 1; // Valid move
}

int solve_puzzle(int puzzle[9][9], int row, int col)
{
    // If we reach the end of the row, move to the next row
    if (row == 9) // Base case
    {
        return 1; // Puzzle solved
    }
    // If we reach the end of the column, move to the next row
    if (col == 9)
    {
        return solve_puzzle(puzzle, row + 1, 0);
    }
    // If the cell is already filled, move to the next column
    if (puzzle[row][col] != 0)
    {
        return solve_puzzle(puzzle, row, col + 1);
    }
    // Try numbers from 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        if (check_valid_move(puzzle, row, col, num))
        {
            puzzle[row][col] = num; // Place the number
            if (solve_puzzle(puzzle, row, col + 1))
            {
                return 1; // Puzzle solved
            }
            puzzle[row][col] = 0; // Backtrack
        }
    }
    return 0; // No solution found
}
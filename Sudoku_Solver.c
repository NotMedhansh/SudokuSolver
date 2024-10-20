#include <stdio.h>
#include <stdbool.h>

#define N 9

// Function to print the Sudoku board
void printBoard(char board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// Function to check if placing num in board[row][col] is valid
bool isValid(char board[N][N], int row, int col, char num) {
    for (int x = 0; x < N; x++) {
        if (board[row][x] == num || board[x][col] == num) {
            return false; // Check row and column
        }
    }

    // Check the 3x3 sub-grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

// Function to solve the Sudoku board
bool solveSudoku(char board[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            // Find an empty space
            if (board[row][col] == '.') {
                for (char num = '1'; num <= '9'; num++) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num; // Place the number

                        // Recursively try to solve the rest of the board
                        if (solveSudoku(board)) {
                            return true; // Solved
                        }

                        // Backtrack if not solved
                        board[row][col] = '.'; // Reset the space
                    }
                }
                return false; // Trigger backtracking
            }
        }
    }
    return true; // Puzzle solved
}

int main() {
    char board[N][N] = {
        { '5', '3', '.', '.', '7', '.', '.', '.', '.' },
        { '6', '.', '.', '1', '9', '5', '.', '.', '.' },
        { '.', '9', '8', '.', '.', '.', '.', '6', '.' },
        { '8', '.', '.', '.', '6', '.', '.', '.', '3' },
        { '4', '.', '.', '8', '.', '3', '.', '.', '1' },
        { '7', '.', '.', '.', '2', '.', '.', '.', '6' },
        { '.', '6', '.', '.', '.', '.', '2', '8', '.' },
        { '.', '.', '.', '4', '1', '9', '.', '.', '5' },
        { '.', '.', '.', '.', '8', '.', '.', '7', '9' }
    };

    printf("Original Sudoku Board:\n");
    printBoard(board);

    if (solveSudoku(board)) {
        printf("\nSolved Sudoku Board:\n");
        printBoard(board);
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}
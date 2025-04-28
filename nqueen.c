#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printSolution(int *board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i] == j)
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

bool isSafe(int *board, int row, int col) {
    for (int i = 0; i < row; i++) {
        // Check same column and diagonals
        if (board[i] == col || 
            board[i] - i == col - row || 
            board[i] + i == col + row)
            return false;
    }
    return true;
}

void solveNQueens(int *board, int row, int n, int *solutionCount) {
    if (row == n) {
        (*solutionCount)++;
        printf("Solution %d:\n", *solutionCount);
        printSolution(board, n);
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            solveNQueens(board, row + 1, n, solutionCount);
            // No need to undo, because we'll overwrite board[row] in next iteration
        }
    }
}

int main() {
    int n;
    printf("Enter the number of queens (n): ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input! Number of queens must be greater than 0.\n");
        return 1;
    }

    int *board = (int *)malloc(n * sizeof(int));
    if (board == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    int solutionCount = 0;
    solveNQueens(board, 0, n, &solutionCount);

    if (solutionCount == 0) {
        printf("No solutions exist for %d queens.\n", n);
    } else {
        printf("Total solutions: %d\n", solutionCount);
    }

    free(board);
    return 0;
}

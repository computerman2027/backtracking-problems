#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool isSafe(int *board, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        if (board[i] == col ||
            board[i] - i == col - row ||
            board[i] + i == col + row)
            return false;
    }
    return true;
}

void solveNQueens(int *board, int row, int n, int *solutionCount, int ***solutions, int *capacity)
{
    if (row == n)
    {
        // Resize solution array if needed
        if (*solutionCount >= *capacity)
        {
            *capacity *= 10;
            *solutions = (int **)realloc(*solutions, (*capacity) * sizeof(int *));
            if (*solutions == NULL)
            {
                fprintf(stderr, "Memory allocation failed during realloc.\n");
                exit(1);
            }
        }

        // Store the solution
        int *sol = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            sol[i] = board[i];

        (*solutions)[*solutionCount] = sol;
        (*solutionCount)++;
        return;
    }

    for (int col = 0; col < n; col++)
    {
        if (isSafe(board, row, col))
        {
            board[row] = col;
            solveNQueens(board, row + 1, n, solutionCount, solutions, capacity);
        }
    }
}

int main()
{
    int n;
    printf("Enter value of n: ");
    scanf("%d", &n);

    int *board = (int *)malloc(n * sizeof(int));

    // Initial capacity for solutions
    int capacity = 100;
    int **solutions = (int **)malloc(capacity * sizeof(int *));
    if (solutions == NULL)
    {
        fprintf(stderr, "Initial memory allocation failed.\n");
        return 1;
    }

    int solCount = 0;
    clock_t s = clock();
    solveNQueens(board, 0, n, &solCount, &solutions, &capacity);
    clock_t e = clock();

    double tt = ((double)(e - s)) / CLOCKS_PER_SEC;

    printf("No of solutions: %d\n", solCount);
    printf("Time taken: %lf seconds\n", tt);

    // Optional: print solutions
    // for (int i = 0; i < solCount; i++)
    // {
    //     printf("Solution %d: ", i + 1);
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%d ", solutions[i][j]);
    //     }
    //     printf("\n");
    // }

    // Cleanup
    // for (int i = 0; i < solCount; i++)
    //     free(solutions[i]);
    // free(solutions);
    // free(board);

    return 0;
}

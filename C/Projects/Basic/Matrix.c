/*
C Program for Matrix Operations Including Transpose, Addition, Subtraction, and Multiplication Using Dynamic Memory Allocation
*/

#include <stdio.h>
#include <stdlib.h>

// Function prototypes for matrix operations
void transpose(double **matrix_1, double **transpose_m, int a, int b);
void sum(double **matrix_1, double **matrix_2, double **sum_m, int a, int b);
void diffrence(double **matrix_1, double **matrix_2, double **diffrence_m, int a, int b);
void product(double **matrix_1, double **matrix_2, double **product_m, int a);
double dotproduct(double **matrix_1, double **matrix_2, int a, int s, int t);

int main()
{
    int n, m; // Variables to store number of rows and columns
    printf("Enter number of rows for the matrices: ");
    scanf("%d", &n);
    printf("Enter number of columns for the matrices: ");
    scanf("%d", &m);

    // Dynamically allocate memory for the matrices
    double **matrix_1 = (double **)malloc(n * sizeof(double *));
    double **matrix_2 = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
    {
        matrix_1[i] = (double *)malloc(m * sizeof(double));
        matrix_2[i] = (double *)malloc(m * sizeof(double));
    }

    // Input the matrix from the user
    printf("Enter the first matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%lf", &matrix_1[i][j]);
        }
    }

    printf("Enter the second matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%lf", &matrix_2[i][j]);
        }
    }

    // Display the main menu
    printf("**********MAIN MENU**********\n");
    printf("1. Transpose of the first matrix\n");
    printf("2. Sum of both matrices\n");
    printf("3. Difference of both matrices\n");
    printf("4. Product of both matrices\n");

    // Ask user to make a selection
    int z;
    printf("Make your selection: ");
    scanf("%d", &z);

    // Perform the selected operation
    if (z == 1)
    {
        // Allocate memory for the transpose matrix
        double **transpose_m = (double **)malloc(m * sizeof(double *));
        for (int i = 0; i < m; i++)
        {
            transpose_m[i] = (double *)malloc(n * sizeof(double));
        }
        transpose(matrix_1, transpose_m, n, m);
    }
    else if (z == 2)
    {
        // Allocate memory for the sum matrix
        double **sum_m = (double **)malloc(n * sizeof(double *));
        for (int i = 0; i < n; i++)
        {
            sum_m[i] = (double *)malloc(m * sizeof(double));
        }
        sum(matrix_1, matrix_2, sum_m, n, m);
    }
    else if (z == 3)
    {
        // Allocate memory for the difference matrix
        double **diffrence_m = (double **)malloc(n * sizeof(double *));
        for (int i = 0; i < n; i++)
        {
            diffrence_m[i] = (double *)malloc(m * sizeof(double));
        }
        diffrence(matrix_1, matrix_2, diffrence_m, n, m);
    }
    else if (z == 4)
    {
        // Check if the matrices are square
        if (n == m)
        {
            // Allocate memory for the product matrix
            double **product_m = (double **)malloc(n * sizeof(double *));
            for (int i = 0; i < n; i++)
            {
                product_m[i] = (double *)malloc(n * sizeof(double));
            }
            product(matrix_1, matrix_2, product_m, n);
        }
        else
        {
            printf("\nMath Error: Matrices must be square for multiplication.\n");
        }
    }
    else
    {
        printf("\nInvalid Input!\n");
    }

    // Free allocated memory for both matrices
    for (int i = 0; i < n; i++)
    {
        free(matrix_1[i]);
        free(matrix_2[i]);
    }
    free(matrix_1);
    free(matrix_2);
    return 0;
}

// Function to compute the transpose of the matrix
void transpose(double **matrix_1, double **transpose_m, int a, int b)
{
    printf("\nTranspose of the matrix is:\n");
    for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < a; j++)
        {
            transpose_m[i][j] = matrix_1[j][i]; // Switching rows and columns
            printf("%.2lf ", transpose_m[i][j]);
        }
        printf("\n");
    }
}

// Function to calculate the sum of two matrices
void sum(double **matrix_1, double **matrix_2, double **sum_m, int a, int b)
{
    printf("\nSum of both matrices is:\n");
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            sum_m[i][j] = matrix_1[i][j] + matrix_2[i][j];
            printf("%.2lf ", sum_m[i][j]);
        }
        printf("\n");
    }
}

// Function to compute the difference of two matrices
void diffrence(double **matrix_1, double **matrix_2, double **diffrence_m, int a, int b)
{
    printf("\nDifference of both matrices is:\n");
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            diffrence_m[i][j] = matrix_1[i][j] - matrix_2[i][j];
            printf("%.2lf ", diffrence_m[i][j]);
        }
        printf("\n");
    }
}

// Function to compute the product of two matrices
void product(double **matrix_1, double **matrix_2, double **product_m, int a)
{
    printf("\nProduct of both matrices is:\n");
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < a; j++)
        {
            product_m[i][j] = dotproduct(matrix_1, matrix_2, a, i, j); // Calculate product with the help of another function
            printf("%.2lf ", product_m[i][j]);
        }
        printf("\n");
    }
}

// Fucnction that help in computing product of the matrices
double dotproduct(double **matrix_1, double **matrix_2, int a, int s, int t)
{
    double summ = 0;
    for (int i = 0; i < a; i++)
    {
        summ += matrix_1[s][i] * matrix_2[i][t]; // Dot product of row s from matrix_1 and column t from matrix_2
    }
    return summ;
}

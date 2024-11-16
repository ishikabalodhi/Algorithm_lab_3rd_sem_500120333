#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 128 // Maximum size of matrices (must be a power of 2)

// Function prototypes
int **allocate_matrix(int n);
void free_matrix(int **matrix, int n);
void traditional_multiply(int **A, int **B, int **C, int n);
void add(int **A, int **B, int **C, int n);
void subtract(int **A, int **B, int **C, int n);
void strassen(int **A, int **B, int **C, int n);

// Traditional matrix multiplication
void traditional_multiply(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Matrix addition
void add(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Matrix subtraction
void subtract(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Strassen's matrix multiplication
void strassen(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    // Create submatrices
    int **A11 = allocate_matrix(k);
    int **A12 = allocate_matrix(k);
    int **A21 = allocate_matrix(k);
    int **A22 = allocate_matrix(k);
    int **B11 = allocate_matrix(k);
    int **B12 = allocate_matrix(k);
    int **B21 = allocate_matrix(k);
    int **B22 = allocate_matrix(k);
    int **M1 = allocate_matrix(k);
    int **M2 = allocate_matrix(k);
    int **M3 = allocate_matrix(k);
    int **M4 = allocate_matrix(k);
    int **M5 = allocate_matrix(k);
    int **M6 = allocate_matrix(k);
    int **M7 = allocate_matrix(k);
    int **C11 = allocate_matrix(k);
    int **C12 = allocate_matrix(k);
    int **C21 = allocate_matrix(k);
    int **C22 = allocate_matrix(k);
    int **temp1 = allocate_matrix(k);
    int **temp2 = allocate_matrix(k);

    // Divide the matrices into quadrants
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Calculate M1 to M7
    add(A11, A22, temp1, k);         // M1 = (A11 + A22)
    add(B11, B22, temp2, k);         // M2 = (B11 + B22)
    strassen(temp1, temp2, M1, k);   // M1 = (A11 + A22)(B11 + B22)

    add(A21, A22, temp1, k);         // M3 = (A21 + A22)
    strassen(temp1, B11, M2, k);     // M2 = (A21 + A22)B11

    subtract(B12, B22, temp2, k);    // M4 = (B12 - B22)
    strassen(A11, temp2, M3, k);     // M3 = A11(B12 - B22)

    subtract(B21, B11, temp2, k);    // M5 = (B21 - B11)
    strassen(A22, temp2, M4, k);     // M4 = A22(B21 - B11)

    add(A11, A12, temp1, k);         // M6 = (A11 + A12)
    strassen(temp1, B22, M5, k);     // M5 = (A11 + A12)B22

    subtract(A21, A11, temp1, k);    // M7 = (A21 - A11)
    add(B11, B12, temp2, k);         // M6 = (B11 + B12)
    strassen(temp1, temp2, M6, k);   // M6 = (A21 - A11)(B11 + B12)

    subtract(A12, A22, temp1, k);    // M7 = (A12 - A22)
    add(B21, B22, temp2, k);         // M7 = (B21 + B22)
    strassen(temp1, temp2, M7, k);   // M7 = (A12 - A22)(B21 + B22)

    // Combine results into C
    add(M1, M4, C11, k);              // C11 = M1 + M4
    subtract(C11, M5, C11, k);        // C11 = C11 - M5
    add(M3, M5, C12, k);              // C12 = M3 + M5
    add(M2, M4, C21, k);              // C21 = M2 + M4
    add(M1, M3, C22, k);              // C22 = M1 + M3

    // Place submatrices back into C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    // Free allocated memory
    free_matrix(A11, k);
    free_matrix(A12, k);
    free_matrix(A21, k);
    free_matrix(A22, k);
    free_matrix(B11, k);
    free_matrix(B12, k);
    free_matrix(B21, k);
    free_matrix(B22, k);
    free_matrix(M1, k);
    free_matrix(M2, k);
    free_matrix(M3, k);
    free_matrix(M4, k);
    free_matrix(M5, k);
    free_matrix(M6, k);
    free_matrix(M7, k);
    free_matrix(C11, k);
    free_matrix(C12, k);
    free_matrix(C21, k);
    free_matrix(C22, k);
    free_matrix(temp1, k);
    free_matrix(temp2, k);
}

// Function to dynamically allocate a 2D matrix
int **allocate_matrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }
    return matrix;
}

// Function to free a dynamically allocated 2D matrix
void free_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Main function
int main() {
    int n;
    printf("Enter the size of the matrices (must be a power of 2, max %d): ", MAX_SIZE);
    scanf("%d", &n);

    // Check if n is a power of 2 and within the limit
    if ((n & (n - 1)) != 0 || n > MAX_SIZE) {
        printf("Error: Size must be a power of 2 and less than or equal to %d.\n", MAX_SIZE);
        return 1;
    }

    int **A = allocate_matrix(n);
    int **B = allocate_matrix(n);
    int **C_traditional = allocate_matrix(n);
    int **C_strassen = allocate_matrix(n);

    // Initialize matrices A and B with random values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10; // Random values between 0-9
            B[i][j] = rand() % 10; // Random values between 0-9
        }
    }

    // Traditional multiplication
    clock_t start = clock();
    traditional_multiply(A, B, C_traditional, n);
    clock_t end = clock();
    double traditional_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Traditional Multiplication Time: %f seconds\n", traditional_time);

    // Strassen's multiplication
    start = clock();
    strassen(A, B, C_strassen, n);
    end = clock();
    double strassen_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Strassen's Multiplication Time: %f seconds\n", strassen_time);

    // Free allocated memory
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C_traditional, n);
    free_matrix(C_strassen, n);

    return 0;
}

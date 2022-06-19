#include <stdio.h>

void matrix_scalar_multiply(int rows, int columns, float matrix[rows][columns], float scalar, float new_matrix[rows][columns]){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            new_matrix[i][j] = scalar * matrix[i][j];
        }
    }
}

void matrix_matrix_multiply(int rows1, int columns1, float matrix1[rows1][columns1], int rows2, int columns2, float matrix2[rows2][columns2], float new_matrix[rows1][columns2]){
    if(columns1 != rows2){
        return;
    }
    for(int i = 0; i < rows1; i++){
        for(int j = 0; j < columns2; j++){
            for(int k = 0; k < columns1; k++){
                new_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void print_matrix(int rows, int columns, float matrix[rows][columns]){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            printf("%0.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    float matrix[4][3] = {
        {1, 5, 9},
        {2, 6, 10}, 
        {3, 7, 11}, 
        {4, 8, 12}   
    };
    print_matrix(4, 3, matrix);
    float new_matrix[4][3];
    matrix_scalar_multiply(4, 3, matrix, 3, new_matrix);
    printf("\n");
    print_matrix(4, 3, new_matrix);
    float new_matrix1[4][2];
    float matrix1[4][3] = {
        {1, -1, 0},
        {0, 2, 3}, 
        {1, -3, 1}, 
        {4, 0, 2}   
    };
    float matrix2[3][2] = {
        {2, 1},
        {-1, 0}, 
        {3, 1},
    };
    printf("\n");
    matrix_matrix_multiply(4, 3, matrix1, 3, 2, matrix2, new_matrix1);
    print_matrix(4, 2, new_matrix1);
    return 0;
}

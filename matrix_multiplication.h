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
    
    for(int i = 0; i < rows1; ++i) {
        for(int j = 0; j < columns2; ++j) {
            new_matrix[i][j] = 0;
        }
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

float matrix_2x2(int abc, int rows_start, int columns_start, int rows_end, int columns_end, float matrix[3][3]){
    return abc * (matrix[rows_start][columns_start] * matrix[rows_end][columns_end] - matrix[rows_start][columns_end] * matrix[rows_end][columns_start]);
}

float matrix_3x3(float matrix[3][3]){
    return matrix_2x2(matrix[0][0], 1, 1, 2, 2, matrix) + matrix_2x2(matrix[0][1], 1, 2, 2, 0, matrix) + matrix_2x2(matrix[0][2], 1, 0, 2, 1, matrix);
}

int mod(int number, int plus){
    return (number + plus) % 4;
}

float create_matrix(int abcd, int rows_start, int columns_start, float matrix[4][4]){
    float new_matrix[3][3];
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            new_matrix[i][j] = matrix[mod(rows_start, i)][mod(columns_start, j)];
        }
    }
    return abcd * matrix_3x3(new_matrix);
}

float determinant_matrix(int rows, int columns, float matrix[rows][columns]){
    if(rows != columns){
        printf("Error\n");
        return 0;
    }
    if(rows == 2){
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    if(rows == 3){
        return matrix_3x3(matrix);
    }
    if(rows == 4){
        return create_matrix(matrix[0][0], 1, 1, matrix) - create_matrix(matrix[0][1], 1, 2, matrix) + create_matrix(matrix[0][2], 1, 3, matrix) - create_matrix(matrix[0][3], 1, 0, matrix);
    }
}

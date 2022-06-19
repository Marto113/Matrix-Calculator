#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "file_operations.h"

int main() {
    int count = 1;

    matrix_t *matrix = matrix_init(3, 4, "matrix1.txt");

    for(int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->columns; j++){
            matrix->elements[i][j] = count++;
        }
    }

    matrix_transpose(matrix);

    write_matrix(matrix);

    return 0;
}
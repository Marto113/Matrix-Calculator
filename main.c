#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "file_operations.h"

int main() {
    int count = 1;

    matrix_t matrix = matrix_init(3, 4, "matrix3");

    for(int i = 0; i < matrix.rows; i++){
        for(int j = 0; j < matrix.columns; j++){
            matrix.elements[i][j] = count++;
        }
    }

    print_matrix(&matrix);

    matrix_transpose(&matrix);

    print_matrix(&matrix);

    write_matrix(&matrix);

    read_matrix(&matrix);

    return 0;
}
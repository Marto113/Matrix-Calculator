#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "file_operations.h"

int main() {
    matrix_t *matrix = matrix_init(3, 3, "matrix1.txt");;
    console_matrix("matrix2.txt");
    return 0;
}
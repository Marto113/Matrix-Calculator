#include <stdio.h>
#include <stdlib.h>

void write_matrix(matrix_t *matrix){
    FILE *file;
    file = fopen(matrix->alias, "w");

    int row = matrix->rows;
    int col = matrix->columns;
    
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            fprintf(file, "%d", matrix->elements[i][j]);
            fprintf(file, " ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void read_matrix(){}

void console_matrix(){}
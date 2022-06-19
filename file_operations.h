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

void read_matrix(matrix_t *matrix){
    FILE *file;
    file = fopen(matrix->alias, "r");

    int num;
    for(int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->columns; j++){
            fscanf(file, "%d", &num);
            matrix->elements[i][j] = num;
            printf("%d ", matrix->elements[i][j]);
        }
        printf("\n");
    }

    fclose(file);
}

void console_matrix(char *name){
    FILE *file;
    file = fopen(name, "w");
    
    int rows, columns;
    scanf("%d %d", rows, columns);
    matrix_t *matrix = matrix_init(rows, columns, name);

    for(int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->columns; j++){
            scanf("%d", &matrix->elements[i][j]);
            fprintf(file, "%d", matrix->elements[i][j]);
            fprintf(file, " ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}


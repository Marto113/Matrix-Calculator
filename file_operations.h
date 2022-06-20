#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_matrix(matrix_t *matrix){ 
    FILE *file;

    char *file_name = calloc(strlen(matrix->alias) + 5, sizeof(char));
    strcpy(file_name, matrix->alias);
    strcat(file_name, ".txt");

    file = fopen(file_name, "w");

    free(file_name);

    int row = matrix->rows;
    int col = matrix->columns;

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            fprintf(file, "%.2f", matrix->elements[i][j]);
            fprintf(file, " ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void read_matrix(matrix_t *matrix){
    FILE *file;

    char *file_name = calloc(strlen(matrix->alias) + 5, sizeof(char));
    strcpy(file_name, matrix->alias);
    strcat(file_name, ".txt");

    puts(file_name);

    file = fopen(file_name, "r");

    free(file_name);

    for(int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->columns; j++){
            fscanf(file, "%f", &matrix->elements[i][j]);
            printf("%.2f ", matrix->elements[i][j]);
        }
        printf("\n");
    }

    fclose(file);
}

void console_matrix(char *name){
    FILE *file;    

    char *file_name = calloc(strlen(name) + 5, sizeof(char));
    strcpy(file_name, name);
    strcat(file_name, ".txt");

    file = fopen(file_name, "w");

    free(file_name);

    int rows, columns;
    scanf("%d %d", &rows, &columns);
    matrix_t matrix = matrix_init(rows, columns, name);

    for(int i = 0; i < matrix.rows; i++){
        for(int j = 0; j < matrix.columns; j++){
            scanf("%f", &matrix.elements[i][j]);
            fprintf(file, "%.2f", matrix.elements[i][j]);
            fprintf(file, " ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}


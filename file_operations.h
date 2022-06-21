#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_matrix(matrix_t matrix){ 
    FILE *file;

    char *file_name = calloc(strlen(matrix.alias) + 5, sizeof(char));
    strcpy(file_name, matrix.alias);
    strcat(file_name, ".txt");

    file = fopen(file_name, "w");

    free(file_name);

    int row = matrix.rows;
    int col = matrix.columns;
    fprintf(file, "%d %d", row, col);
    fprintf(file, "\n");

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            fprintf(file, "%.2f", matrix.elements[i][j]);
            fprintf(file, " ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

matrix_t read_matrix(char *name){
    FILE *file;

    char *file_name = calloc(strlen(name) + 5, sizeof(char));
    strcpy(file_name, name);
    strcat(file_name, ".txt");

    puts(file_name);

    file = fopen(file_name, "r");

    free(file_name);

    int row, col;
    fscanf(file, "%d %d", &row, &col);
    matrix_t matrix = matrix_init(row, col, name);

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            fscanf(file, "%f", &matrix.elements[i][j]);
            printf("%.2f ", matrix.elements[i][j]);
        }
        printf("\n");
    }

    fclose(file);

    return matrix;
}

void console_matrix(char *name){
    FILE *file;    

    char *file_name = calloc(strlen(name) + 5, sizeof(char));
    strcpy(file_name, name);
    strcat(file_name, ".txt");

    file = fopen(file_name, "w");

    free(file_name);

    int row, col;
    scanf("%d %d", &row, &col);
    matrix_t matrix = matrix_init(row, col, name);
    fprintf(file, "%d %d", row, col);
    fprintf(file, "\n");
    
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            scanf("%f", &matrix.elements[i][j]);
            fprintf(file, "%.2f", matrix.elements[i][j]);
            fprintf(file, " ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}


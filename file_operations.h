#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int float_to_int (float a) {
    return * (int*) & a;
}

float int_to_float(int a) {
    return * (float*) & a;
}

float fxor(float a, int b) {
    return int_to_float(float_to_int(a) ^ b);
}

void encrypt(matrix_t matrix, int key){ 
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

    fprintf(file, "%d", key);
    fprintf(file, "\n");

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            fprintf(file, "%f", fxor(matrix.elements[i][j], key));
            fprintf(file, " ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

matrix_t decrypt(char *name){
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

    int key;
    fscanf(file, "%d", &key);

    float num;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            fscanf(file, "%f", &num);
            matrix.elements[i][j] = fxor(num, key);
        }
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

    int key;
    scanf("%d", &key);
    fprintf(file, "%d", key);
    fprintf(file, "\n");
    
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            scanf("%f", &matrix.elements[i][j]);
            fprintf(file, "%f", matrix.elements[i][j]);
            fprintf(file, " ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int* b) {
    int c = *a;
    *a = *b;
    *b = c;
}

typedef struct {
    int rows;
    int columns;
    int **elements;
    char *alias;
}matrix_t;

matrix_t *matrix_init(int rows, int columns, char *name) {
    matrix_t *new_matrix = malloc(sizeof(matrix_t *));

    new_matrix->rows = rows;
    new_matrix->columns = columns;

    new_matrix->alias = malloc(strlen(name));
    strcpy(new_matrix->alias, name);

    new_matrix->elements = malloc(sizeof(int *) * rows);

    for (int i = 0; i < new_matrix->rows; i++) 
        new_matrix->elements[i] = malloc(sizeof(int) * columns);

    return new_matrix;
}

void matrix_copy(matrix_t *dest, matrix_t *src) {
    strcpy(dest->alias, src->alias);
    dest->rows = src->rows;
    dest->columns = src->columns;

    dest->elements = realloc(dest->elements, sizeof(int *) * src->rows);

    for (int i = 0; i < dest->rows; i++) 
        dest->elements[i] = malloc(sizeof(int) * dest->columns);

    for (int i = 0; i < dest->rows; i++)
        for (int j = 0; j < dest->columns; j++) 
            dest->elements[i][j] = src->elements[i][j];
}

void transpose_symetrical(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) 
        for (int j = i; j < matrix->columns; j++)
            swap(&matrix->elements[i][j], &matrix->elements[j][i]);
}

void transpose_unsymetrical(matrix_t *matrix) {
    matrix_t *transposed = matrix_init(matrix->columns, matrix->rows, matrix->alias);

    for (int i = 0; i < transposed->rows; i++)
        for (int j = 0; j < transposed->columns; j++)
            transposed->elements[i][j] = matrix->elements[j][i];

    matrix_copy(matrix, transposed);
    
    free(transposed);
}

void matrix_transpose(matrix_t *matrix) {
    if (matrix->rows == matrix->columns)
        transpose_symetrical(matrix);
    else transpose_unsymetrical(matrix);
}
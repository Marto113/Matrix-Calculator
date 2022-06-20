#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(float *a, float* b) {
    float c = *a;
    *a = *b;
    *b = c;
}

typedef struct {
    int rows;
    int columns;
    float **elements;
    char *alias;
}matrix_t;

matrix_t matrix_init(int rows, int columns, char *name) {
    matrix_t new_matrix;

    new_matrix.rows = rows;
    new_matrix.columns = columns;

    int alias_size = strlen(name) + 1;

    new_matrix.alias = calloc(alias_size, sizeof(char));
    strcpy(new_matrix.alias, name);

    new_matrix.elements = malloc(sizeof(float *) * rows);

    for (int i = 0; i < new_matrix.rows; i++) 
        new_matrix.elements[i] = malloc(sizeof(float) * columns);

    return new_matrix;
}

void matrix_free(matrix_t *matrix) {
    free(matrix->alias);

    for (int i = 0; i < matrix->rows; i++)
        free(matrix->elements[i]);

    free(matrix->elements);

    matrix->rows = 0;
    matrix->columns = 0;
}

void matrix_copy(matrix_t *dest, matrix_t *src) {
    strcpy(dest->alias, src->alias);
    dest->rows = src->rows;
    dest->columns = src->columns;

    dest->elements = realloc(dest->elements, sizeof(float *) * src->rows);

    for (int i = 0; i < dest->rows; i++) 
        dest->elements[i] = malloc(sizeof(float) * dest->columns);

    for (int i = 0; i < dest->rows; i++)
        for (int j = 0; j < dest->columns; j++) 
            dest->elements[i][j] = src->elements[i][j];
}

void matrix_shallowcopy(matrix_t *dest, matrix_t *src) {
    matrix_free(dest);

    *dest = *src;
}

void transpose_symetrical(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) 
        for (int j = i; j < matrix->columns; j++)
            swap(&matrix->elements[i][j], &matrix->elements[j][i]);
}

void transpose_unsymetrical(matrix_t *matrix) {
    matrix_t transposed = matrix_init(matrix->columns, matrix->rows, matrix->alias);

    for (int i = 0; i < transposed.rows; i++)
        for (int j = 0; j < transposed.columns; j++)
            transposed.elements[i][j] = matrix->elements[j][i];
    
    matrix_shallowcopy(matrix, &transposed);
}

void matrix_transpose(matrix_t *matrix) {
    if (matrix->rows == matrix->columns)
        transpose_symetrical(matrix);
    else transpose_unsymetrical(matrix);
}

void print_matrix(matrix_t *matrix) {
    puts(matrix->alias);

    printf("%d %d\n", matrix->rows, matrix->columns);

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++)
            printf("%.2f ", matrix->elements[i][j]);
        printf("\n");
    }
}
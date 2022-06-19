#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int rows;
    int columns;
    int **elements;
    char *alias;
}matrix_t;

matrix_t* matrix_init(int rows, int columns, char *name) {
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


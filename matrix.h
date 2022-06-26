#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
        for (int j = i + 1; j < matrix->columns; j++)
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
    if (matrix->rows == matrix->columns) {
        transpose_symetrical(matrix);
    } else transpose_unsymetrical(matrix);
}

void matrix_divide_scalar(matrix_t *matrix, float scalar) {
    //vikni matrix multiply s 1/scalar kogato kamen si premesti funckiite tuka;
    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->columns; j++) 
            matrix->elements[i][j] /= scalar;
}

//float find_2nd_determinant(float a, float b, float c, float d) {
//    return (a * d) - (b * c);
//}

//float find_3rd_determinant() {
//
//}

//float find_nth_determinant(int rows, int columns, float arr[rows][columns]) {
//    float determinant = 0;
//
//    if (rows == 2) {
//        return find_2nd_determinant();
//    }
//
//    for (int i = 0; i < columns; i++) {
//        if (i % 2 == 0) {
//           determinant += arr[0][i] * find_nth_determinant();
//        } else determinant -= arr[0][i] * find_nth_determinant();
//    }
//}
//
//float find_matrix_determinant(matrix_t matrix) {
//    return find_nth_determinant(matrix.rows, matrix.columns, matrix.elements);
//}

void matrix_of_minors(matrix_t *matrix) {

}

void matrix_cofactor(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) 
        for (int j = 0; j < matrix->columns; j++) 
            if ((i * matrix->columns + j) % 2 != 0) 
                matrix->elements[i][j] *= -1;
}

/*
void matrix_inverse(matrix_t *matrix) {
    if (matrix->columns != matrix->rows) {
        printf("Matrix must be square to have an inverse!\n");
        return ;
    }

    float determinant = find_matrix_determinant(*matrix);

    if (determinant == 0) {
        printf("Determinant is 0 therefore matrix has no inverse.\n");
        return ;
    }

    matrix_of_minors(matrix);

    matrix_cofactor(matrix);
    matrix_transpose(matrix);

    matrix_divide_scalar(matrix, determinant);
}
*/

float find_max(matrix_t matrix) {
    float max = matrix.elements[0][0]; 

    for (int i = 0; i < matrix.rows; i++)
        for (int j = 0; j < matrix.columns; j++)
            if (max < matrix.elements[i][j])
                max = matrix.elements[i][j];

    return (int) max;        
}

void print_matrix(matrix_t matrix) {
    int max_num = (int) log10(find_max(matrix)) + 1;

    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.columns; j++) {
            for (int k = (int) log10(matrix.elements[i][j] + 0.000001); k < max_num; k++) {
                printf(" ");
            }
            printf("%.2f", matrix.elements[i][j]);
        }
        printf("\n");
    }
}
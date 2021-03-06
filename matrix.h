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

float find_max(matrix_t matrix) {
    float max = matrix.elements[0][0]; 

    for (int i = 0; i < matrix.rows; i++)
        for (int j = 0; j < matrix.columns; j++)
            if (max < matrix.elements[i][j])
                max = matrix.elements[i][j];

    return (int) max;        
}

int get_num_len(float num) {
    int count = 0;
    (num < 0) ? num *= -1, count = 1 : num;
    return (num  != 0) ? (int) log10(num) + count : (int) log10(num + 1) + count;
}

void print_matrix(matrix_t matrix) {
    int max_num = (int) log10(find_max(matrix)) + 1;

    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.columns; j++) {
            for (int k = get_num_len(matrix.elements[i][j]); k < max_num; k++) {
                printf(" ");
            }
            printf("%.2f", matrix.elements[i][j]);
        }
        printf("\n");
    }
}

void matrix_scalar_multiply(matrix_t* m, float scalar){
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->columns; j++){
            m->elements[i][j] *= scalar;
        }
    }
}

void matrix_matrix_multiply(matrix_t* m1, matrix_t* m2){
    if(m1->columns != m2->rows){
        return;
    }
    matrix_t new_matrix = matrix_init(m1->rows, m2->columns, m1->alias);
    for(int i = 0; i < m1->rows; ++i) {
        for(int j = 0; j < m2->columns; ++j) {
            new_matrix.elements[i][j] = 0;
        }
    }
    
    for(int i = 0; i < m1->rows; i++){
        for(int j = 0; j < m2->columns; j++){
            for(int k = 0; k < m1->columns; k++){
                new_matrix.elements[i][j] += m1->elements[i][k] * m2->elements[k][j];
            }
        }
    }
    matrix_shallowcopy(m1, &new_matrix);
}

float matrix_2x2(int abc, int rows_start, int columns_start, int rows_end, int columns_end, float **matrix){
    return abc * (matrix[rows_start][columns_start] * matrix[rows_end][columns_end] - matrix[rows_start][columns_end] * matrix[rows_end][columns_start]);
}

float matrix_3x3(float **matrix){
    return matrix_2x2(matrix[0][0], 1, 1, 2, 2, matrix) + matrix_2x2(matrix[0][1], 1, 2, 2, 0, matrix) + matrix_2x2(matrix[0][2], 1, 0, 2, 1, matrix);
}

int mod(int number, int plus){
    return (number + plus) % 4;
}

float create_matrix_3x3(int abcd, int rows_start, int columns_start, float** matrix){
    float **new_matrix = malloc(sizeof(int) * 3);
    for(int i = 0; i < 3; i++){
        new_matrix[i] = malloc(sizeof(float));
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            new_matrix[i][j] = matrix[mod(rows_start, i)][mod(columns_start, j)];
        }
    }
    return abcd * matrix_3x3(new_matrix);
}

float determinant_matrix(matrix_t *m){
    if(m->rows != m->columns){
        printf("Error\n");
        return 0;
    }
    if(m->rows == 2){
        return m->elements[0][0] * m->elements[1][1] - m->elements[0][1] * m->elements[1][0];
    }
    if(m->rows == 3){
        return matrix_3x3(m->elements);
    }
    if(m->rows == 4){
        return create_matrix_3x3(m->elements[0][0], 1, 1, m->elements) - create_matrix_3x3(m->elements[0][1], 1, 2, m->elements) + create_matrix_3x3(m->elements[0][2], 1, 3, m->elements) - create_matrix_3x3(m->elements[0][3], 1, 0, m->elements);
    }
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

void matrix_of_minors(matrix_t *matrix) {
    matrix_t minor = matrix_init(matrix->rows, matrix->columns, matrix->alias);

    

    matrix_shallowcopy(matrix, &minor);
}

void matrix_cofactor(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) 
        for (int j = 0; j < matrix->columns; j++) 
            if ((i * matrix->columns + j) % 2 != 0) 
                matrix->elements[i][j] *= -1;
}

void matrix_inverse(matrix_t *matrix) {
    if (matrix->columns != matrix->rows) {
        printf("Matrix must be square to have an inverse!\n");
        return ;
    }

    float determinant = determinant_matrix(matrix);

    if (determinant == 0) {
        printf("Determinant is 0 therefore matrix has no inverse.\n");
        return ;
    }

    matrix_of_minors(matrix);

    print_matrix(*matrix);

    matrix_cofactor(matrix);
    matrix_transpose(matrix);

    matrix_divide_scalar(matrix, determinant);
}
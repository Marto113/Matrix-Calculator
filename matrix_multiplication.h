#include <stdio.h>

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
    int return_determinant = abcd * matrix_3x3(new_matrix);
    free(new_matrix);
    return return_determinant;
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

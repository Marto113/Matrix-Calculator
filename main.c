#include "matrix.h"
#include "file_operations.h"
#include "hash.h"

void show_options(int _case) {
    if(_case == 1) {
        printf("\n"
               "[0] - Exit\n"
               "[1] - Read from file\n"
               "[2] - Make matrix from console\n"
               "[3] - Write matrix to file\n"
               "[4] - Operations with matrices\n");
    } else {
        printf("\n"
               "[1] - Multiply matrix by scalar\n"
               "[2] - Multiply matrix by matrix\n"
               "[3] - Find determinant of matrix\n"
               "[4] - Divide matrix by scalar\n"
               "[5] - Transpose matrix\n"
               "[6] - Inverse matrix\n"
               "[7] - Print matrix\n");
    }      
}

int check(linked_list_t **hash_table, char *name) {
    //printf("%d\n", hash(name));
    if(hash_table[hash(name)]->matrix.alias == NULL)
        return 0;
    return 1;
}

int main() {
    linked_list_t **hash_table = calloc(HASH_TABLE_LEN, sizeof(matrix_t *));

    matrix_t *curr_matrix;

    int count = 0;
    int c = 1;
    int d = 1;
    float scalar;
    char buff[MAX_LEN];
    char buff2[MAX_LEN];

    ///*
    while (c) {
        show_options(1);

        scanf("%d", &c);

        switch (c) {
            case 1:
                printf("File to read from: ");
                scanf("%s", buff);
                matrix_t new = decrypt(buff);
                hashtable_add(&new, hash_table);
                break;

            case 2:
                scanf("%s", buff);
                console_matrix(buff);
                break;

            case 3:
                scanf("%s", buff);
                if (!check(hash_table, buff)) {
                    puts("No such matrix!");
                    break;
                }
                curr_matrix = &(hash_table[hash(buff)]->matrix);
                encrypt(*curr_matrix, rand() % INT_MAX);
                break;

            case 4:
                show_options(2);
                scanf("%d", &d);
                switch (d) {
                    case 1:
                        scanf("%s %f", buff, &scalar);
                        if (!check(hash_table, buff)) {
                            puts("No such matrix!");
                            break;
                        }
                        curr_matrix = &(hash_table[hash(buff)]->matrix);
                        matrix_scalar_multiply(curr_matrix, scalar);
                        
                        break;

                    case 2:
                        scanf("%s %s", buff, buff2);

                        if (!check(hash_table, buff)) {
                            puts("No such matrix!");
                            break;
                        }

                        if (!check(hash_table, buff2)) {
                            puts("No such multiplyer!");
                            break;
                        }

                        curr_matrix = &(hash_table[hash(buff)]->matrix);
                        matrix_t *multiplyer = &(hash_table[hash(buff2)]->matrix);
                        matrix_matrix_multiply(curr_matrix, multiplyer);
                        break;

                    case 3:
                        scanf("%s", buff);
                        if (!check(hash_table, buff)) {
                            puts("No such matrix!");
                            break;
                        }
                        curr_matrix = &(hash_table[hash(buff)]->matrix);
                        printf("%.2f\n", determinant_matrix(curr_matrix));
                        break;

                    case 4:
                        scanf("%s %f", buff, &scalar);
                        if (!check(hash_table, buff)) {
                            puts("No such matrix!");
                            break;
                        }
                        curr_matrix = &(hash_table[hash(buff)]->matrix);
                        matrix_divide_scalar(curr_matrix, scalar);
                        break;

                    case 5:
                        scanf("%s", buff);
                        if (!check(hash_table, buff)) {
                            puts("No such matrix!");
                            break;
                        }
                        curr_matrix = &(hash_table[hash(buff)]->matrix);
                        matrix_transpose(curr_matrix);
                        break;

                    case 6:
                        scanf("%s", buff);
                        if (!check(hash_table, buff)) {
                            puts("No such matrix!");
                            break;
                        }
                        curr_matrix= &(hash_table[hash(buff)]->matrix);
                        matrix_inverse(curr_matrix);
                        break; 

                    case 7:
                        scanf("%s", buff);
                        if (!check(hash_table, buff)) {
                            puts("No such matrix!");
                            break;
                        }
                        print_matrix(hash_table[hash(buff)]->matrix);
                    break;
                }
                break;
        }
    }
    //*/
    return 0;
}
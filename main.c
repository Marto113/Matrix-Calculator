#include "matrix.h"
#include "file_operations.h"
#include "hash.h"

void show_options(int _case) {
    if(_case == 1) {
        printf("\n"
               "[0] - Exit\n"
               "[1] - Read from file\n"
               "[2] - Make matrix from console\n"
               "[3] - Operations with matrices"
               "\n");
    } else {
        printf("\n"
               "[1] - Multiply matrix by scalar\n"
               "[2] - Multiply matrix by matrix\n"
               "[3] - Find determinant of matrix\n"
               "[4] - Divide matrix by scalar\n"
               "[5] - Transpose matrix\n"
               "[6] - Inverse matrix\n"
               "[7] - Print matrix\n"
               "\n");
    }      
}

char *check(linked_list_t **hash_table, char *name) {
    return hash_table[hash(name)]->matrix.alias;
}

int main() {
    linked_list_t **hash_table = calloc(HASH_TABLE_LEN, sizeof(matrix_t));

    matrix_t *curr_matrix;

    int count = 0;
    int c = 1;
    int d = 1;
    char buff[MAX_LEN];

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
                show_options(2);
                scanf("%d", &d);
                switch (d) {
                    case 1:
                        break;

                    case 2:
                        break;

                    case 3:
                        
                        break;

                    case 4:
                        int scalar;
                        scanf("%s %d", buff, scalar);
                        curr_matrix = &(hash_table[hash(buff)]->matrix);
                        matrix_divide_scalar(curr_matrix, scalar);
                        break;

                    case 5:
                        scanf("%s", buff);
                        curr_matrix = &(hash_table[hash(buff)]->matrix);
                        matrix_transpose(curr_matrix);
                        break;

                    case 6:
                        break; 

                    case 7:
                        scanf("%s", buff);
                        print_matrix(hash_table[hash(buff)]->matrix);
                    break;
                }
                break;
        }
    }
    //*/
    return 0;
}
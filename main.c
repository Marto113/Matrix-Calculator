#include "matrix.h"
#include "file_operations.h"
#include "hash.h"

void show_options() {
    printf("[0] - Exit\n"
           "[1] - Read from file\n"
           "[2] - Make matrix from console\n"
           "[3] - Multiply matrix by scalar\n"
           "[4] - Multiply matrix by matrix\n"
           "[5] - Divide matrix by scalar\n"
           "[6] - Find determinant of matrix\n"
           "[7] - Transpose matrix\n"
           "[8] - Inverse matrix\n"
           "[9] - Print matrix\n");
}

int main() {
    linked_list_t **hash_table = calloc(HASH_TABLE_LEN, sizeof(matrix_t *));
    char used_strings[MAX_MATRIXES][MAX_LEN];

    int c = 1;

    while (c) {
        show_options();

        scanf("%d", &c);

        switch (c) {

        }
    }
    return 0;
}
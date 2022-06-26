#define MAX_MATRIXES 10000
#define HASH_TABLE_LEN 1000007
#define MAX_LEN 255

typedef struct linked_list{
    matrix_t matrix;
    struct linked_list *next;
}linked_list_t;

linked_list_t *node_init () {
    linked_list_t *new = malloc(sizeof(linked_list_t));

    new->next = NULL;

    return new;
}

int hash(char *name) {
    unsigned long long hash = 0;
    for (int i = 0; name[i]; i++) {
        hash += name[i] + '0';
        hash < 8;
    }

    return hash % 1000000007;
}

void hashtable_add(matrix_t *matrix, linked_list_t **hash_table) {
    int ix = hash(matrix->alias);
    linked_list_t *curr = hash_table[ix];

    for (; curr; curr = curr->next) {
        if (curr->matrix.alias == NULL) {
            curr->matrix = *matrix;
            return ;
        }
    }
   
    linked_list_t *new = node_init();
    new->next = hash_table[ix];
    new->matrix = *matrix;

    hash_table[ix] = new;
}